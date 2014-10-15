
#include "Principal.h"

//VARIABLES ESTÁTICAS
//===================
bool Principal::debug = false;

//CONSTRUCTORES Y DESTRUCTORES
//===========================
Principal::Principal(): metaheuristica(0) {
    //Activación del modo debug
    activarDebug();

    //Definición del fichero
    elegirFichero();

    //Elección de algoritmo
    elegirAlgoritmo();

    //Elección de semilla
    elegirSemilla();
}

Principal::~Principal() {
    if(metaheuristica)
        delete metaheuristica;
}

//MÉTODOS PROTECTED
//=================
void Principal::activarDebug(){
     char d;

     do {
        std::cout << "El modo debug mostrara, por pantalla, informacion adicional"
                  << " sobre la ejecucion"<< std::endl <<"del programa..."
                  << std::endl << "Desea activar el modo debug?"
                  << " (s/n): ";
        std::cin >> d;
        std::cout << std::endl;
    }while(d != 's' && d != 'n');

    if(d == 's')
        Principal::debug = true;
}

void Principal::elegirFichero() {
    std::cout << "Nombre del fichero (sin extension): " << std::flush;
    getline(std::cin >> std::ws, fichero);
    std::cout << std::endl;
}

void Principal::elegirAlgoritmo() {
    if(metaheuristica)
        delete metaheuristica;

    //Instanciación de la metaheurística
    metaheuristica = new BL("./DAT/" + fichero + ".dat");
}

void Principal::elegirSemilla() {
    std::cout << std::endl << "Introduzca la semilla: ";
    std::cin >> semilla;

    srand(semilla);
}

unsigned long Principal::ejecutarAlgoritmo() {
    return metaheuristica->ejecutar();
}
