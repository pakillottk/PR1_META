
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

}

void Principal::construirAlgoritmo() {
    if(metaheuristica)
        delete metaheuristica;

    //Instanciación de la metaheurística
    switch(tipo) {
        case ALG_Greedy:
         //   metaheuristica = new Greedy("./DAT/" + fichero + ".dat");
        break;

        case ALG_BL:
            metaheuristica = new BL("./DAT/" + fichero + ".dat");
        break;

        case ALG_BT:
          //  metaheuristica = new BT("./DAT/" + fichero + ".dat");
        break;
    }

}

void Principal::elegirSemilla() {
    std::cout << std::endl << "Introduzca la semilla: ";
    std::cin >> semilla;

    srand(semilla);
}

void Principal::ejecutarAlgoritmo() {
    construirAlgoritmo();

    //empiezo a medir
    unsigned long coste = metaheuristica->ejecutar();
    //termina medicion
}

std::string Principal::tipo_str() {
    switch(tipo) {
        case ALG_Greedy:
            return "Greedy";
        break;

        case ALG_BL:
            return "Busqueda Local";
        break;

        case ALG_BT:
            return "Busqueda Tabu";
        break;
    }
}
