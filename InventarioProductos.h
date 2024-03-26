#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>

using namespace std;

// Definir los códigos de color
const string colorRojo = "\033[31m";
const string colorVerde = "\033[32m";
const string colorAmarillo = "\033[33m";
const string colorAzul = "\033[34m";
const string colorMagenta = "\033[35m";
const string colorCian = "\033[36m";
const string colorBlanco = "\033[37m";
const string colorNegro = "\033[30m";

// Definir los códigos de color
const string colorGrisClaro = "\033[37m";
const string colorCianClaro = "\033[96m";
const string colorMagentaClaro = "\033[95m";
const string colorAmarilloClaro = "\033[93m";
const string colorVerdeClaro = "\033[92m";

const string negrita = "\033[1m";
const string subrayado = "\033[4m";
const string resetColor = "\033[0m"; // Resetear a los colores por defecto
//
void limpiarPantalla() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

//
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Producto { 
public:
    string nombre;
    int cantidad;

    Producto(string nombre, int cantidad) : nombre(nombre), cantidad(cantidad) {}
};

class GestorDeArchivo {         //historial
public:

    static void guardarInventarioEnArchivo(const vector<Producto>& inventarioProductos) {
        try {                                                                   //Excepcion
            ofstream archivo("inventario_Productos.txt", ios::out | ios::trunc); //Se crea una archivo txt.
            if (!archivo.is_open()) {
                cerr << "Error: No se pudo abrir el archivo para guardar el inventario." << endl;
                return; // Salimos de la función si no se puede abrir el archivo.
            }
            for (const Producto& producto : inventarioProductos) {
                archivo << "Nombre: " << producto.nombre << ", Cantidad: " << producto.cantidad << endl;
            }
            archivo.close();
            cout << "Inventario guardado en 'inventario_Productos.txt'." << endl;
        } catch (const std::exception& e) {
            cerr << "Se ha producido un error al guardar el inventario: " << e.what() << endl;
        }
    }

};

class InventarioP { //clase contenedora | agregacion.

    friend class InterfazUsuario; // Permitir acceso a InterfazUsuario

private:
    vector<Producto> inventarioProductos;

public:
    void agregarProducto(const string& nombre, int cantidad) {
        auto it = find_if(inventarioProductos.begin(), inventarioProductos.end(), [&nombre](const Producto& prod) { return prod.nombre == nombre; });
        if (it != inventarioProductos.end()) {
            it->cantidad += cantidad;
        } else {
            inventarioProductos.emplace_back(nombre, cantidad);
        }
    }

    bool quitarProducto(const string& nombre, int cantidad) {
        for (auto it = inventarioProductos.begin(); it != inventarioProductos.end(); ++it) {
            if (it->nombre == nombre && cantidad <= it->cantidad) {
                it->cantidad -= cantidad;
                if (it->cantidad <= 0) {
                    inventarioProductos.erase(it);
                }
                return true; // Producto quitado
            }
        }
        return false; // Producto no encontrado
    }

    void mostrarInventario() const {
        cout << "Inventario actual de productos:" << endl;
        for (const Producto &producto : inventarioProductos) {
            cout << "Nombre: " << producto.nombre << ", Cantidad: " << producto.cantidad << endl;
        }
        cout << "-----------------------------" << endl;
        
    }

    friend void GestorDeArchivo::guardarInventarioEnArchivo(const vector<Producto>& inventarioProductos);
};
class InterfazUsuario {
public:
    static void ejecutarInventario(InventarioP& inventario) {
        bool salir = false;
        while (!salir) {
            limpiarPantalla();
            cout << colorRojo << negrita << "         INVENTARIO DE PRODUCTOS          "<< resetColor << endl;
            cout <<colorVerdeClaro << endl;
            cout << "[a]. Mostrar inventario" << endl;
            cout << "[b]. Agregar producto" << endl;
            cout << "[c]. Quitar producto" << endl;
            cout << "[d]. Salir" << endl;
            cout << "Seleccione una opcion: ";
            char opcion;
            cin >> opcion;
            cout<< resetColor;
            switch (opcion) {
                case 'a':
                    inventario.mostrarInventario();
                    limpiarBuffer();
                    cout << "Presione Enter para continuar...";
                    cin.get(); // Espera a que el usuario presione Enter
                    limpiarPantalla(); // Limpia la pantalla después de mostrar el inventario
                    break;
                case 'b':
                    agregarProducto(inventario);
                    limpiarPantalla();
                    break;
                case 'c':
                    quitarProducto(inventario);
                    limpiarPantalla();
                    break;
                case 'd':                   
                    GestorDeArchivo::guardarInventarioEnArchivo(inventario.inventarioProductos);
                    salir = true;
                    limpiarPantalla();

                    break;
                default:
                    cout << "Opcion no valida. Por favor, seleccione una opcion valida.";
                    cout << "Presione Enter para continuar...";
                    cin.get(); // Espera a que el usuario presione Enter
                    limpiarPantalla();
                    break;
            }
            limpiarBuffer();
        }

    }

private:
    static void agregarProducto(InventarioP& inventario) {
        string nombre;
        int cantidad;

        cout << "Ingrese el nombre del producto: ";
        limpiarBuffer();
        getline(cin, nombre);

        cout << "Ingrese la cantidad: ";
        while (!(cin >> cantidad)) {
            cout << "Por favor, ingrese un valor valido para la cantidad." << endl;
            limpiarBuffer();
        }

        inventario.agregarProducto(nombre, cantidad);
        limpiarBuffer();
        
    }

    static void quitarProducto(InventarioP& inventario) {
        string nombre;
        int cantidad;

        cout << "Ingrese el nombre del producto que desea quitar: ";
        limpiarBuffer();
        getline(cin, nombre);

        cout << "Ingrese la cantidad que desea quitar: ";
        while (!(cin >> cantidad)) {
            cout << "Cantidad no valida para quitar. Intentelo nuevamente: ";
            limpiarBuffer();
        }

        if (!inventario.quitarProducto(nombre, cantidad)) {
            cout << "El producto no esta en el inventario o la cantidad es mayor a la existente." << endl;
        }
        limpiarBuffer();

    }
};
