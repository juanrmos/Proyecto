#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

// Declaracion anticipada de la clase InventarioA
class InventarioA;

// Clase Animal
class Animal {
private:
    string estado; // Atributo estado

public:
    string especie;
    int cantidad;

    Animal(string especie, int cantidad) : especie(especie), cantidad(cantidad) {}
    void setEstado(const string& nuevoEstado) {
        estado = nuevoEstado;
    }

        string getEstado() const {
        return estado;
    }
    // Funcion amiga para solicitar el estado del animal
    friend void solicitarEstado(Animal& animal);

    // Funcion amiga para acceder al estado del animal
    friend string obtenerEstado(const Animal& animal);
};

// Clase Inventario
class InventarioA {
private:
    vector<Animal> inventarioAnimales;

public:
    void mostrarInventarioAnimales() {
        cout << "Inventario actual de animales:" << endl;
        for (const Animal& animal : inventarioAnimales) {
            cout << "Especie: " << animal.especie << "  Cantidad: " << animal.cantidad
                << "  Estado: " << obtenerEstado(animal) << endl;
        }
        cout << "-----------------------------" << endl;
        cout << "Presione Enter para continuar..."<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Asume que ya se limpio el buffer anteriormente.
    }

    void agregarAnimal() {
    string especie;
    string estado;
    int cantidad;

    cout << "Ingrese la especie del animal: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer antes de leer la especie.
    getline(cin, especie);

    cout << "Ingrese el estado del animal: ";
    getline(cin, estado);

    cout << "Ingrese la cantidad: ";
    while (!(cin >> cantidad)) {
        cout << "Por favor, ingrese un valor valido para la cantidad." << endl;
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    // Verificar si el animal ya existe en el inventario con la misma especie y estado
    for (Animal& animal : inventarioAnimales) {
        if (animal.especie == especie && animal.getEstado() == estado) {
            animal.cantidad += cantidad; // Actualizar la cantidad del animal existente
            cout << "Cantidad actualizada para el animal existente en el inventario." << endl;
            return;
        }
    }

    // Si el animal no existe con la misma especie y estado, agregar un nuevo animal al inventario
    Animal nuevoAnimal(especie, cantidad);
    nuevoAnimal.setEstado(estado); // Establecer el estado del nuevo animal
    inventarioAnimales.push_back(nuevoAnimal);
    cout << "Animal agregado al inventario." << endl;
}

    void quitarAnimal() {
    if (inventarioAnimales.empty()) {
        cout << "El inventario de animales está vacio." << endl;
        return;
    }

    string especie;
    string estado;
    cout << "Ingrese la especie del animal que desea quitar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, especie);

    cout << "Ingrese el estado del animal que desea quitar: ";
    getline(cin, estado);

    for (auto it = inventarioAnimales.begin(); it != inventarioAnimales.end(); ) {
        if (it->especie == especie && it->getEstado() == estado) {
            int cantidadQuitada;
            cout << "Ingrese la cantidad que desea quitar: ";
            while (!(cin >> cantidadQuitada)) {
                cout << "Por favor, ingrese un valor valido para la cantidad." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }

            if (cantidadQuitada > 0 && cantidadQuitada <= it->cantidad) {
                it->cantidad -= cantidadQuitada;
                if (it->cantidad == 0) {
                    it = inventarioAnimales.erase(it);
                } else {
                    ++it;
                }
                cout << "Animal actualizado o quitado del inventario." << endl;
            } else {
                cout << "Cantidad no valida para quitar." << endl;
                ++it;
            }
            return; // Sal de la funcion despues de manejar el animal especificado.
        } else {
            ++it;
        }
    }
    cout << "El animal no esta en el inventario." << endl;
}


    void guardarInventarioEnArchivo() {
        ofstream archivo("inventario_animales.txt", ios::out);
        if (archivo.is_open()) {
            for (const Animal& animal : inventarioAnimales) {
                archivo << "Especie: " << animal.especie << ", Cantidad: " << animal.cantidad << ", Estado: " << obtenerEstado(animal) << "\n";
            }
            archivo.close();
            cout << "Inventario guardado en 'inventario_animales.txt'." << endl;
        } else {
            cout << "No se pudo abrir el archivo para guardar el inventario." << endl;
        }
    }

    // Funcion amiga para solicitar el estado del animal
    friend void solicitarEstado(Animal& animal);

    // Funcion amiga para acceder al estado del animal
    friend string obtenerEstado(const Animal& animal);
};

// Definicion de la funcion para solicitar el estado del animal
void solicitarEstado(Animal& animal) {
    cout << "Ingrese el estado del animal (saludable, enfermo, herido, etc.): ";
    cin >> animal.estado;
}

// Definicion de la funcion para obtener el estado del animal
string obtenerEstado(const Animal& animal) {
    return animal.estado;
}
//



// Clase base para representar un movimiento
class MovimientoBase {
public:
    virtual string getTipo() const = 0;
    virtual string getDescripcion() const = 0;
    virtual ~MovimientoBase() {} // Destructor virtual para la clase base
};

// Clase para representar un movimiento de objeto
class MovimientoObjeto : public MovimientoBase {
private:
    string tipo;  // Tipo de movimiento (agregar o quitar)
    string descripcion;  // Descripcion del movimiento (nombre del objeto y cantidad)

public:
    MovimientoObjeto(const string& tipo, const string& descripcion) : tipo(tipo), descripcion(descripcion) {}

    virtual string getTipo() const override {
        return tipo;
    }

    virtual string getDescripcion() const override {
        return descripcion;
    }
};

// Clase para representar un movimiento de animal
class MovimientoAnimal : public MovimientoBase {
private:
    string tipo;  // Tipo de movimiento (agregar o quitar)
    string descripcion;  // Descripcion del movimiento (nombre del animal y cantidad)

public:
    MovimientoAnimal(const string& tipo, const string& descripcion) : tipo(tipo), descripcion(descripcion) {}

    virtual string getTipo() const override {
        return tipo;
    }

    virtual string getDescripcion() const override {
        return descripcion;
    }
};

// Funcion para mostrar el historial de movimientos
void mostrarHistorial(const vector<MovimientoBase*>& historial) {
    cout << "Historial de movimientos realizados:" << endl;
    for (const auto& movimiento : historial) {
        cout << "- " << movimiento->getTipo() << ": " << movimiento->getDescripcion() << endl;
    }
    cout << "-----------------------------" << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();   
    cin.get(); 
}