#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#ifndef PREF_RECOM_H
#define PREF_RECOM_H
using namespace std;

void limpiarBuffer1() {
    cin.clear(); // Limpiar el estado de error de cin--
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar todos los caracteres hasta encontrar un salto de linea '\n'
    }


class Preferencias {
private:
    string tipoAlimentacion;
    int edad;
    string estado;
    
public:
    friend class Calculo;       //Clases amigas para acceder a los datos privados.
    friend class SalidaDeDatos;
    Preferencias() : edad(0) {} // Constructor por defecto
    //getters.

    void obtenerPreferencias() {
        cout << "Por favor, ingrese la informacion del animal:" << endl;

        cout << "1. Tipo de alimentacion (vegetariano, carnivoro, omnivoro): ";
        limpiarBuffer1();
        getline(cin, tipoAlimentacion);

        cout << "2. Edad del animal: ";
        while (!(cin >> edad)) {
        cout << "Por favor, ingrese un valor valido para la edad." << endl;
        limpiarBuffer1();
        cout << "2. Edad del animal: "; // Vuelve a solicitar la edad
    }
        cout << "3. Estado del animal (saludable, enfermo, anciano): ";
        limpiarBuffer1();
        getline(cin, estado);
    }
};

class Calculo {
public:
    unordered_map<string, int> realizarCalculos(const Preferencias& preferencias) {
        string tipoAlimentacion = preferencias.tipoAlimentacion;
        string estado = preferencias.estado;
        int edad = preferencias.edad;
        unordered_map<string, int> alimentosNecesarios;

        // Ajustar la cantidad de alimentos en funcion del tipo de alimentación
        if (tipoAlimentacion == "vegetariano") {
            alimentosNecesarios["Frutas"] += 3;
            alimentosNecesarios["Verduras"] += 4;
            alimentosNecesarios["Legumbres"] += 2;
        } else if (tipoAlimentacion == "carnivoro") {
            alimentosNecesarios["Carne"] += 5;
            alimentosNecesarios["Pescado"] += 3;
        } else if (tipoAlimentacion == "omnivoro") {
            alimentosNecesarios["Frutas"] += 2;
            alimentosNecesarios["Verduras"] += 3;
            alimentosNecesarios["Carne"] += 4;
        }

        // Ajustar la cantidad de alimentos en funcion de la edad
        if (edad >= 1 && edad <= 3) {
            ajustarAlimentosPorEdad(alimentosNecesarios, 1.2); // Aumentar la cantidad en un 20%
        } else if (edad >= 7 && edad <= 9) {
            ajustarAlimentosPorEdad(alimentosNecesarios, 0.8); // Reducir la cantidad en un 20%
        }

        // Ajustar la cantidad de alimentos en funcion del estado
        if (estado == "enfermo") {
            ajustarAlimentosPorEstado(alimentosNecesarios, 0.5); // Reducir la cantidad a la mitad
        } else if (estado == "anciano") {
            ajustarAlimentosPorEstado(alimentosNecesarios, 0.8); // Reducir la cantidad en un 20%
        }

        return alimentosNecesarios;
    }

private:

    void ajustarAlimentosPorEdad(unordered_map<string, int>& alimentos, double factor) {
        for (auto& par : alimentos) {
            par.second *= factor;
        }
    }

    void ajustarAlimentosPorEstado(unordered_map<string, int>& alimentos, double factor) {
        for (auto& par : alimentos) {
            par.second *= factor;
        }
    }
};


class SalidaDeDatos {
public:
    
    void imprimirRecomendaciones(const unordered_map<string, int>& alimentosNecesarios, const Preferencias& preferencias) {
        string estado = preferencias.estado;

        cout << "Cantidad de alimentos recomendados para el animal (" << estado << "):" << endl;

        if (estado == "saludable") {
            cout << "- Ofrecer agua fresca diariamente." << endl;
            cout << "- Proporcionar una dieta balanceada segun las preferencias alimentarias." << endl;
        } else if (estado == "enfermo") {
            cout << "- Consultar con el veterinario para una dieta especifica segun la enfermedad." << endl;
            cout << "- Mantener la hidratacion con agua fresca y limpia." << endl;
        } else if (estado == "anciano") {
            cout << "- Considerar una dieta baja en grasas para animales ancianos." << endl;
            cout << "- Ofrecer alimentos que promuevan la salud articular." << endl;
        } else {
            cout << "- Recomendaciones generales para el estado del animal." << endl;
        }

        cout << "Cantidad de alimentos recomendados:" << endl;
        for (const auto& par : alimentosNecesarios) {
            cout << "- " << par.first << ": " << par.second << " unidades diarias" << endl;
        }

        cout << "Presione Enter para continuar...";
        limpiarBuffer1(); // Esperar a que el usuario presione Enter
    }
};




#endif