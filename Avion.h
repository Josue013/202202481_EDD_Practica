#include <iostream>
#include <string>

using namespace std;

class Avion {
public:
    string vuelo;
    string numero_de_registro;
    string modelo;
    string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;
    string aerolinea;
    string estado;

    Avion(string vuelo, string numero_de_registro, string modelo, string fabricante,
          int ano_fabricacion, int capacidad, int peso_max_despegue, string aerolinea, string estado)
        : vuelo(vuelo), numero_de_registro(numero_de_registro), modelo(modelo), fabricante(fabricante),
          ano_fabricacion(ano_fabricacion), capacidad(capacidad), peso_max_despegue(peso_max_despegue),
          aerolinea(aerolinea), estado(estado) {}

    void mostrar() const {
        cout << "-------------------------" << endl;
        cout << "Vuelo: " << vuelo << endl;
        cout << "Numero de Registro: " << numero_de_registro << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Fabricante: " << fabricante << endl;
        cout << "Año de Fabricacion: " << ano_fabricacion << endl;
        cout << "Capacidad: " << capacidad << endl;
        cout << "Peso Maximo de Despegue: " << peso_max_despegue << endl;
        cout << "Aerolinea: " << aerolinea << endl;
        cout << "Estado: " << estado << endl;
        cout << "-------------------------" << endl;
    }
};
