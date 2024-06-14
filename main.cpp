#include <iostream>
#include <fstream> 
#include <string> // Para usar string
#include <cstdlib> // Para usar system()
#include "src/DoubleCircularList.h" // Para usar DoubleCircularList
#include "src/cola.h" // Para usar Cola
#include "src/pila.h" // Para usar Pila
#include "src/DoublyLinkedList.h" // Para usar DoublyLinkedList
#include "src/Avion.h" // Para usar Avion
#include "src/Pasajero.h" // Para usar Pasajero
#include "src/json.h" // Para usar Json 
#include "src/json.cpp" // Para usar Json 
using namespace std; 

DoubleCircularList<Avion> listaAvionesDisponible;
DoubleCircularList<Avion> listaAvionesMantenimiento;
Cola<Pasajero> colaPasajeros;
Pila<Pasajero> equipajePasajeros;
DoublyLinkedList<Pasajero> listaEquipaje;

void menu();
void reportes();
void reporte_aviones();
void reporte_pasajeros();
void reporte_pila_equipaje();
void reporte_lista_doble_pasajeros();
void cargar_aviones();
void cargar_pasajeros();
void cargar_mov();
void consulta();


void menu(){
  cout << "" << endl;
  cout << "╔═════════════════════════════════════╗" << endl;
  cout << "╠═══════════ PRACTICA EDD ════════════╣" << endl;
  cout << "╠═════════════════════════════════════╣" << endl;
  cout << "║           Elija una opcion          ║" << endl;
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


void cargar_aviones() {
  string filename = "ArchivosDeEntrada/aviones.json";
  ifstream ifs(filename, ifstream::binary);
  if (!ifs.is_open()) {
    cerr << "No se pudo abrir el archivo: " << filename << endl;
  }
  Json::Value root;
  Json::CharReaderBuilder builder;
  string errs;
  // Parsear JSON
  bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errs);
  if (!parsingSuccessful) {
    cerr << "Error al parsear el archivo JSON: " << errs << endl;
  }
  ifs.close();
  for (const auto& avion : root) {
    Avion avionNuevo(avion["vuelo"].asString(), avion["numero_de_registro"].asString(), avion["modelo"].asString(),
        avion["fabricante"].asString(), avion["ano_fabricacion"].asInt(), avion["capacidad"].asInt(),
        avion["peso_max_despegue"].asInt(), avion["aerolinea"].asString(), avion["estado"].asString());
    // Agregar el avión por su estado
    if (avionNuevo.getEstado() == "Disponible") {
      listaAvionesDisponible.insert(avionNuevo);
    } else if (avionNuevo.getEstado() == "Mantenimiento") {
      listaAvionesMantenimiento.insert(avionNuevo);
    }
  }
  cout << "║   Aviones cargados exitosamente.    ║" << endl;
  cout << "╚═════════════════════════════════════╝" << endl;
}

void cargar_pasajeros() {
  string filename = "ArchivosDeEntrada/pasajeros.json";
  ifstream ifs(filename, ifstream::binary);
  if (!ifs.is_open()) {
    cerr << "No se pudo abrir el archivo: " << filename << endl;
  }
  Json::Value root;
  Json::CharReaderBuilder builder;
  string errs;
  // Parsear JSON
  bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errs);
  if (!parsingSuccessful) {
    cerr << "Error al parsear el archivo JSON: " << errs << endl;
  }
  ifs.close();
  for (const auto& pasajero : root) {
    if (!pasajero.isMember("equipaje_facturado")) {
      // pasajero sin equipaje
      Pasajero pasajeroNuevo(pasajero["nombre"].asString(), pasajero["nacionalidad"].asString(),
          pasajero["numero_de_pasaporte"].asString(), pasajero["vuelo"].asString(),
          pasajero["asiento"].asString(), pasajero["destino"].asString(),
          pasajero["origen"].asString(), 0);
      colaPasajeros.enqueue(pasajeroNuevo);
    } else {
      // pasajero con equipaje
      Pasajero pasajeroNuevo(pasajero["nombre"].asString(), pasajero["nacionalidad"].asString(),
          pasajero["numero_de_pasaporte"].asString(), pasajero["vuelo"].asString(),
          pasajero["asiento"].asString(), pasajero["destino"].asString(),
          pasajero["origen"].asString(), pasajero["equipaje_facturado"].asInt());
      colaPasajeros.enqueue(pasajeroNuevo);
    }
  }
  cout << "║  Pasajeros cargados exitosamente.   ║" << endl;
  cout << "╚═════════════════════════════════════╝" << endl;
}

void cargar_mov() {
  ifstream file("ArchivosDeEntrada/movimientos.txt");
  string line;
  if (file.is_open()) {
    cout << "\nSE HICIERON LOS SIGUIENTES MOVIMIENTOS:" << endl;
    while (getline(file, line)) {
      if (line == "IngresoEquipajes;") {
        Pasajero pasajero = colaPasajeros.dequeue();
        if (pasajero.getEquipajeFacturado() > 0) {
          equipajePasajeros.push(pasajero);
          listaEquipaje.prepend(pasajero);
          cout << "El pasajero " << pasajero.getNombre() << " con pasaporte " << pasajero.getNumeroDePasaporte() << " tiene equipaje facturado." << endl;
          cout << "=======================================================================================" << endl;
        } else if (pasajero.getEquipajeFacturado() == 0){
          listaEquipaje.append(pasajero);
          cout << "El pasajero " << pasajero.getNombre() << " con pasaporte " << pasajero.getNumeroDePasaporte() << " no tiene equipaje facturado." << endl;
          cout << "=======================================================================================" << endl;
        }
      } else if (line.find("MantenimientoAviones,Ingreso,") == 0) {
        string contenido = line.substr(29, line.find(";") - 29);
        Avion* avion = listaAvionesDisponible.buscarPorNumeroDeRegistro(contenido);
        if (avion != nullptr) {
          Avion avionMantenimiento(avion->getVuelo(), avion->getNumeroRegistro(), avion->getModelo(),
          avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
          avion->getPesoMaxDespegue(), avion->getAerolinea(), "Mantenimiento");
          listaAvionesMantenimiento.insert(avionMantenimiento);
          listaAvionesDisponible.eliminarPorNumeroDeRegistro(contenido);
          cout << "El avion con numero de registro " << contenido << " ha ingresado a mantenimiento." << endl;
          cout << "=======================================================================================" << endl;
        } else {
          std::cout << "No se encontro el avion con registro : " << contenido << std::endl;
          cout << "=======================================================================================" << endl;
        }
      } else if (line.find("MantenimientoAviones,Salida,") == 0) {
        string contenido = line.substr(28, line.find(";") - 28);
        Avion* avion = listaAvionesMantenimiento.buscarPorNumeroDeRegistro(contenido);
        if (avion != nullptr) {
          Avion avionMantenimiento(avion->getVuelo(), avion->getNumeroRegistro(), avion->getModelo(),
          avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
          avion->getPesoMaxDespegue(), avion->getAerolinea(), "Disponible");
          listaAvionesDisponible.insert(avionMantenimiento);
          listaAvionesMantenimiento.eliminarPorNumeroDeRegistro(contenido);
          cout << "El avion con numero de registro " << contenido << " ha ingresado a Disponible." << endl;
          cout << "=======================================================================================" << endl;
        } else {
          std::cout << "No se encontro el avion : " << contenido << std::endl;
          cout << "=======================================================================================" << endl;
        }
      } else {
        cout << "Error" << endl;
        cout << "=======================================================================================" << endl;
      }
    }
    cout << endl;
    file.close();
  } else {
    cout << "Ocurrio un error" << endl;
    }
  if (listaEquipaje.getSize() > 1) {
    for (int i = 0; i < listaEquipaje.getSize() - 1; i++) {
      Pasajero pasajeroActual = listaEquipaje.getElement(i);
      Pasajero pasajeroSiguiente = listaEquipaje.getElement(i + 1);
      if (pasajeroActual.getVuelo() == pasajeroSiguiente.getVuelo()) {
        // por orden de asiento
        listaEquipaje.ordenarPorNumeroDeAsiento();
      } else if (pasajeroActual.getVuelo() != pasajeroSiguiente.getVuelo()) {
        // por orden de vuelo
        listaEquipaje.ordenarPorNumeroDeVuelo();
      } 
    }
  }
}

void reportes() {
  int opcion_reporte;

  cout << endl;
  cout << "╔═════════════════════════════════════╗" << endl;
  cout << "╠═════════════ REPORTES ══════════════╣" << endl;
  cout << "╠═════════════════════════════════════╣" << endl;
  cout << "║ 1. Litas Circulares dobles Aviones  ║" << endl;
  cout << "║ 2. Cola de Registro                 ║" << endl;
  cout << "║ 3. Pila de Equipaje                 ║" << endl;
  cout << "║ 4. Lista de Pasajeros               ║" << endl;
  cout << "║ 5. Regresar                         ║" << endl;
  cout << "╚═════════════════════════════════════╝" << endl;
  cout << endl;


  do {
    cout << "Selecciona una opción: " << endl;
    cin >> opcion_reporte;

    switch (opcion_reporte) {
      case 1:
        reporte_aviones();
        break;
      case 2:
        reporte_pasajeros();
        break;
      case 3:
        reporte_pila_equipaje();
        break;
      case 4:
        reporte_lista_doble_pasajeros();
        break;
      case 5:
        cout << "Regresando al menu principal..." << endl;
        
        return; // Regresar al menú principal
      default:
        cout << "Opción no válida." << endl;
        break;
    }
  } while (opcion_reporte != 5);
}


void reporte_aviones() {
  std::ofstream archivo("Reportes/grafo_aviones.dot");
  if (!archivo) {
    std::cerr << "Error al abrir el archivo" << std::endl;
    return;
  }

  archivo << "digraph Aviones {\n";
  archivo << "layout=circo;\n";
  archivo << "rankdir=LR;\n"; // Para que las flechas vayan de izquierda a derecha
  archivo << "node [fontname=\"Courier New\"];\n";
  archivo << "node [shape=component, style=filled, color=blue, fillcolor=\"#65babf\"];\n";


  // Recorre la lista de aviones disponibles y los imprime en el archivo .dot
  if (listaAvionesDisponible.getSize() > 0) {
    for (int i = 0; i < listaAvionesDisponible.getSize(); i++) {
      try {
        Avion avion = listaAvionesDisponible.getElement(i);
        archivo << "  \"D" << avion.getNumeroRegistro() << "\" [label=\"" 
            << "Vuelo: " << avion.getVuelo() << "\\n"
            << "Registro: " << avion.getNumeroRegistro() << "\\n" 
            << "Estado: " << avion.getEstado() << "\", shape=box, color=black];\n";
        
        int siguienteIndex = (i + 1) % listaAvionesDisponible.getSize();
        int anteriorIndex = (i - 1 + listaAvionesDisponible.getSize()) % listaAvionesDisponible.getSize();

        Avion avionSiguiente = listaAvionesDisponible.getElement(siguienteIndex);
        Avion avionAnterior = listaAvionesDisponible.getElement(anteriorIndex);

        archivo << "  \"D" << avion.getNumeroRegistro() << "\" -> \"D" << avionSiguiente.getNumeroRegistro() << "\";\n";
        archivo << "  \"D" << avion.getNumeroRegistro() << "\" -> \"D" << avionAnterior.getNumeroRegistro() << "\";\n";
      } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
  }

  // Recorre la lista de aviones en mantenimiento y los imprime en el archivo .dot
  if (listaAvionesMantenimiento.getSize() > 0) {
    for (int i = 0; i < listaAvionesMantenimiento.getSize(); i++) {
      try {
        Avion avion = listaAvionesMantenimiento.getElement(i);
        archivo << "  \"M" << avion.getNumeroRegistro() << "\" [label=\"" 
            << "Vuelo: " << avion.getVuelo() << "\\n"
            << "Registro: " << avion.getNumeroRegistro() << "\\n" 
            << "Estado: " << avion.getEstado() << "\", shape=box, color=red, fillcolor=\"#ffcccb\"];\n";

        int siguienteIndex = (i + 1) % listaAvionesMantenimiento.getSize();
        int anteriorIndex = (i - 1 + listaAvionesMantenimiento.getSize()) % listaAvionesMantenimiento.getSize();

        Avion avionSiguiente = listaAvionesMantenimiento.getElement(siguienteIndex);
        Avion avionAnterior = listaAvionesMantenimiento.getElement(anteriorIndex);

        archivo << "  \"M" << avion.getNumeroRegistro() << "\" -> \"M" << avionSiguiente.getNumeroRegistro() << "\";\n";
        archivo << "  \"M" << avion.getNumeroRegistro() << "\" -> \"M" << avionAnterior.getNumeroRegistro() << "\";\n";
      } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
  }

  archivo << "}\n";
  archivo.close();

  // Genera la imagen utilizando Graphviz
  int result = system("dot -Tpng Reportes/grafo_aviones.dot -o Reportes/grafo_aviones.png");
  if (result == -1) {
    std::cerr << "Error ejecutando el comando dot" << std::endl;
    std::exit(EXIT_FAILURE);
    return;
  }
  std::cout << "Grafica de aviones generada exitosamente." << std::endl;
}

void reporte_pasajeros() {
  std::ofstream file("Reportes/cola_pasajeros.dot");
  
  if (!file) {
    std::cerr << "Error al abrir el archivo de salida" << std::endl;
    return;
  }
  
  file << "digraph cola {" << std::endl;
  file << "node [fontname=\"Courier New\"];" << std::endl;
  file << "node [shape=component, style=filled, color=blue, fillcolor=\"#65babf\"];" << std::endl;
  file << "\"Node 0\" [shape=folder, color=black, fillcolor=\"#d43440\" label=\"Cola De Pasajeros\"];" << std::endl;

  for (int i = 0; i < colaPasajeros.getSize(); i++) {
    Pasajero pasajero = colaPasajeros.getElement(i);
    file << "\"Node " << i + 1 << "\" [label=\"Nombre: " << pasajero.getNombre() << "\\n"
      << "Nacionalidad: " << pasajero.getNacionalidad() << "\\n"
      << "Numero de Pasaporte: " << pasajero.getNumeroDePasaporte() << "\\n"
      << "Vuelo: " << pasajero.getVuelo() << "\\n"
      << "Asiento: " << pasajero.getAsiento() << "\\n"
      << "Destino: " << pasajero.getDestino() << "\\n"
      << "Origen: " << pasajero.getOrigen() << "\\n"
      << "Equipaje Facturado: " << pasajero.getEquipajeFacturado() << "\"];" << std::endl;
    if (i > 0) {
      file << "\"Node " << i << "\" -> \"Node " << i + 1 << "\";" << std::endl;
    }
  }
  file << "}" << std::endl;
  file.close();

  // Genera la imagen utilizando Graphviz
  system("dot -Tpng Reportes/cola_pasajeros.dot -o Reportes/cola_pasajeros.png");

  std::cout << "Reporte de cola de pasajeros generado exitosamente." << std::endl;
}


void reporte_pila_equipaje() {
  std::ofstream file("Reportes/pila_equipaje.dot");
  
  if (!file) {
    std::cerr << "Error al abrir el archivo de salida" << std::endl;
    return;
  }
  
  file << "digraph pila {" << std::endl;
  file << "node [fontname=\"Courier New\"];" << std::endl;
  file << "node [shape=component, style=filled, color=blue, fillcolor=\"#65babf\"];" << std::endl;
  file << "\"Node 0\" [shape=folder, color=black, fillcolor=\"#d43440\" label=\"Pila De Equipaje\"];" << std::endl;

  Pila<Pasajero> aux = equipajePasajeros;
  int i = 1;
  
  while (!aux.isEmpty()) {
    Pasajero pasajero = aux.topPila();
    file << "\"Node " << i << "\" [label=\"Nombre: " << pasajero.getNombre() << "\\n"
      << "No. de Pasaporte: " << pasajero.getNumeroDePasaporte() << "\\n"
      << "Equipaje Facturado: " << pasajero.getEquipajeFacturado() << "\"];" << std::endl;
    if (i > 1) {
      file << "\"Node " << i - 1 << "\" -> \"Node " << i << "\";" << std::endl;
    }
    aux.pop();
    i++;
  }
  
  file << "}" << std::endl;
  file.close();

  // Genera la imagen utilizando Graphviz
int result = system("dot -Tpng Reportes/pila_equipaje.dot -o Reportes/pila_equipaje.png");
if (result != 0) {
    std::cerr << "Error al generar el gráfico con Graphviz. Código de error: " << result << std::endl;
    return;
}

std::cout << "Reporte de pila de equipaje generado exitosamente." << std::endl;
}



void reporte_lista_doble_pasajeros() {
  std::ofstream file("Reportes/reporte_lista_doble_pasajeros.dot");

  if (!file) {
    std::cerr << "Error al abrir el archivo de salida" << std::endl;
    return;
  }

  file << "digraph lista_doble {" << std::endl;
  file << "node [fontname=\"Courier New\"];" << std::endl;
  file << "node [shape=component, style=filled, color=blue, fillcolor=\"#65babf\"];" << std::endl;
  file << "\"Node 0\" [shape=folder, color=black, fillcolor=\"#d43440\" label=\"Lista Doble De Pasajeros\"];" << std::endl;

  for (int i = 0; i < listaEquipaje.getSize(); i++) {
    Pasajero pasajero = listaEquipaje.getElement(i);
    file << "\"Node " << i + 1 << "\" [label=\"Nombre: " << pasajero.getNombre() << "\\n"
      << "Numero de Pasaporte: " << pasajero.getNumeroDePasaporte() << "\\n"
      << "Vuelo: " << pasajero.getVuelo() << "\\n"
      << "Asiento: " << pasajero.getAsiento() << "\"];" << std::endl;


    if (i > 0) {
      file << "\"Node " << i << "\" -> \"Node " << i + 1 << "\";" << std::endl;
      file << "\"Node " << i + 1 << "\" -> \"Node " << i << "\";" << std::endl;
    }
  }
  file << "}" << std::endl;
  file.close();

  // Genera la imagen utilizando Graphviz
  int result = system("dot -Tpng Reportes/reporte_lista_doble_pasajeros.dot -o Reportes/reporte_lista_doble_pasajeros.png");
  if (result != 0) {
    std::cerr << "Error al generar el gráfico con Graphviz. Código de error: " << result << std::endl;
    return;
  }

  std::cout << "Reporte de lista doble de pasajeros generado exitosamente." << std::endl;
}

void consulta() {
  cout << "INGRESE EL No. DE PASAPORTE DEL PASAJERO: ";
  string numPas;
  cin >> numPas;

  if (numPas.empty()) {
        cerr << "El número de pasaporte no puede estar vacío." << endl;
        return;
  }
  Pasajero pasajero = listaEquipaje.buscarPorNumeroDePasaporte(numPas);
  
    cout << "========================================" << endl;
    cout << "INFO DEL PASAJERO\n" << endl;
    cout << "NOMBRE: " << pasajero.getNombre() << endl;
    cout << "NACIONALIDAD: " << pasajero.getNacionalidad() << endl;
    cout << "NO. DE PASAPORTE: " << pasajero.getNumeroDePasaporte() << endl;
    cout << "VUELO: " << pasajero.getVuelo() << endl;
    cout << "ASIENTO: " << pasajero.getAsiento() << endl;
    cout << "DESTINO: " << pasajero.getDestino() << endl;
    cout << "ORIGEN: " << pasajero.getOrigen() << endl;
    cout << "EQUIPAJE FACTURADO: " << pasajero.getEquipajeFacturado() << endl;
    cout << "========================================" << endl;
}

int main(){
  int opcion;
  do{
    menu();
    cin >> opcion;
    switch(opcion){
      case 1:
        cout << "╔═════════════════════════════════════╗" << endl;
        cout << "║         Carga de aviones            ║" << endl;
        cout << "╠═════════════════════════════════════╣" << endl;
        cargar_aviones();
        break;
      case 2:
        cout << "╔═════════════════════════════════════╗" << endl;
        cout << "║        Carga de pasajeros           ║" << endl;
        cout << "╠═════════════════════════════════════╣" << endl;
        cargar_pasajeros();
        break;
      case 3:
        cout << "╔═════════════════════════════════════╗" << endl;
        cout << "║        Carga de movimientos         ║" << endl;
        cout << "╚═════════════════════════════════════╝" << endl;
        cargar_mov();
        break;
      case 4:
        cout << "╔═════════════════════════════════════╗" << endl;
        cout << "║         Consultar pasajero          ║" << endl;
        cout << "╚═════════════════════════════════════╝" << endl;
        cout << "" << endl;
        consulta();
        break;
      case 5:
        cout << "╔═════════════════════════════════════╗" << endl;
        cout << "║         Visualizar reportes         ║" << endl;
        cout << "╚═════════════════════════════════════╝" << endl;
        cout << "" << endl;
        reportes();
        break;
      case 6:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opcion no valida" << endl;
        break;
    }
  }while(opcion != 6);
  return 0;
}