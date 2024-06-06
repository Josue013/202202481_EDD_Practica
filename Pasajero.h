#include <iostream>
#include <string>

using namespace std;

class Pasajero {
public:
    string nombre;
    string nacionalidad;
    string numero_de_pasaporte;
    string vuelo;
    string asiento;
    string destino;
    string origen;
    int equipaje_facturado;

    Pasajero(string nombre, string nacionalidad, string numero_de_pasaporte, string vuelo, string asiento,
             string destino, string origen, int equipaje_facturado)
        : nombre(nombre), nacionalidad(nacionalidad), numero_de_pasaporte(numero_de_pasaporte), vuelo(vuelo),
          asiento(asiento), destino(destino), origen(origen), equipaje_facturado(equipaje_facturado) {}

    void mostrar() const {
        cout << "-------------------------" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Nacionalidad: " << nacionalidad << endl;
        cout << "Numero de Pasaporte: " << numero_de_pasaporte << endl;
        cout << "Vuelo: " << vuelo << endl;
        cout << "Asiento: " << asiento << endl;
        cout << "Destino: " << destino << endl;
        cout << "Origen: " << origen << endl;
        cout << "Equipaje Facturado: " << equipaje_facturado << endl;
        cout << "-------------------------" << endl;
    }
};
