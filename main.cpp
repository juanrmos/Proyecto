#include <iostream>
#include <string>
#include "InventarioProductos.h"
#include "InventarioAnimales.h"
#include "pref_recom.h"

using namespace std;

const int capacidadMaximaObjetos = 100;
const int capacidadMaximaAnimales = 100;



int main()
{
    InventarioP inventario;
    InventarioA inventarioAni;
    Preferencias miAnimal;
    vector<MovimientoBase*> historialMovimientos;  // Historial de movimientos


    int opcion;
    unordered_map<string, int> alimentosNecesarios; // Inicializar aquí

    do
    {
        // Limpiar la pantalla
        system("cls");
        cout << colorCian;
        cout << "============================================================" << endl;
        cout << colorMagenta << negrita << "|                        MENU PRINCIPAL                    |" << resetColor << endl;
        cout << colorCian;
        cout << "============================================================" << endl;
        cout << resetColor << endl;
        cout << colorAmarillo<< negrita << "|  [1]. MENU DE PRODUCTOS                                  |"  << endl;
        cout << "|  [2]. Mostrar inventario de animales                     |" << endl;
        cout << "|  [3]. Agregar animal                                     |" << endl;
        cout << "|  [4]. Quitar animal                                      |" << endl;
        cout << "|  [7]. Obtener preferencias y recomendar alimentos        |" << endl;
        cout << "|  [8]. Mostrar historial de movimientos                   |" << endl;
        cout << "|  [0]. Salir                                              |" << endl;
        cout << "============================================================" << endl;
        cout << resetColor << endl;
        cout << colorBlanco; // Cambiar el color
        cout << "Seleccione una opcion: ";
        cout << resetColor; // Resetear el color

        if (!(cin >> opcion))
        {
            cout << "Por favor, ingrese un valor valido para la opcion." << endl;
            limpiarBuffer();
            continue;
        }

        switch (opcion)
        {
        case 1:
            InterfazUsuario::ejecutarInventario(inventario);;
            break;
        case 2:
                inventarioAni.mostrarInventarioAnimales();
                break;
            case 3:
                inventarioAni.agregarAnimal();
                historialMovimientos.push_back(new MovimientoAnimal("Agregar Animal", "Animal agregado"));  // Registrar el movimiento
                break;
            case 4:
                inventarioAni.quitarAnimal();
                historialMovimientos.push_back(new MovimientoAnimal("Quitar Animal", "Animal quitado"));  // Registrar el movimiento
                break;
        case 7:
            miAnimal.obtenerPreferencias(); // Obtener las preferencias del animal
            Calculo calculo;
            alimentosNecesarios = calculo.realizarCalculos(miAnimal); // Realizar los calculos
            SalidaDeDatos salidaDeDatos;
            salidaDeDatos.imprimirRecomendaciones(alimentosNecesarios, miAnimal); // Imprimir las recomendaciones
            break;
        case 8:
                mostrarHistorial(historialMovimientos);
                break;
        case 0:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion no valida. Intentelo de nuevo." << endl;
            break;
        }
        cout << "-----------------------------" << endl;
        cout << "Presione Enter para continuar...";
        limpiarBuffer();
        cin.ignore();
    } while (opcion != 0);
    // Liberar la memoria de los objetos en el historial
    for (const auto& movimiento : historialMovimientos) {
        delete movimiento;
    }

    
    inventarioAni.guardarInventarioEnArchivo();

    return 0;
}
