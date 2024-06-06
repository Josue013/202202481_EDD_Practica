#include <iostream>
#include <fstream>
#include "ListaDoble.h"
#include "Avion.h"
#include "Pasajero.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void menu(){
    cout << "" << endl;
    cout << "╔═════════════════════════════════════╗" << endl;
    cout << "╠═══════════ PRACTICA EDD ════════════╣" << endl;
    cout << "╠═════════════════════════════════════╣" << endl;
    cout << "║          Elija una opcion           ║" << endl;
    cout << "╠═════════════════════════════════════╣" << endl;
    cout << "║ 1. Carga de aviones                 ║" << endl;
    cout << "║ 2. Carga de pasajeros               ║" << endl;
    cout << "║ 3. Carga de movimientos             ║" << endl;
    cout << "║ 4. Consultar pasajero               ║" << endl;
    cout << "║ 5. Visualizar reportes              ║" << endl;
    cout << "║ 6. Salir                            ║" << endl;
    cout << "╚═════════════════════════════════════╝" << endl;
    cout << "" << endl;
    cout << "Ingrese la opcion deseada:" << endl;
    
}

void cargarYMostrarAviones(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;

        for (auto& elemento : j) {
            Avion avion(elemento["vuelo"], elemento["numero_de_registro"], elemento["modelo"], elemento["fabricante"],
                        elemento["ano_fabricacion"], elemento["capacidad"], elemento["peso_max_despegue"],
                        elemento["aerolinea"], elemento["estado"]);
            avion.mostrar();
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << filename << endl;
    }
}

void cargarYMostrarPasajeros(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;

        for (auto& elemento : j) {
            Pasajero pasajero(elemento["nombre"], elemento["nacionalidad"], elemento["numero_de_pasaporte"],
                              elemento["vuelo"], elemento["asiento"], elemento["destino"], elemento["origen"],
                              elemento["equipaje_facturado"]);
            pasajero.mostrar();
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << filename << endl;
    }
}



int main(){
    ListaDoble lista;
    int opcion;
    do{
        menu();
        cin >> opcion;
        switch(opcion){
            case 1:
                cout << "Carga de aviones" << endl;
                cargarYMostrarAviones("ArchivosDeEntrada/aviones.json");
                break;
            case 2:
                cout << "Carga de pasajeros" << endl;
                cargarYMostrarPasajeros("ArchivosDeEntrada/pasajeros.json");
                break;
            case 3:
                cout << "Carga de movimientos" << endl;
                break;
            case 4:
                cout << "Consultar pasajero" << endl;
                break;
            case 5:
                cout << "Visualizar reportes" << endl;
                break;
            case 6:
                cout << "Saliendo..." << endl;
                exit(0);
                
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while(opcion != 6);
    return 0;
}