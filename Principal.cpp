#include "Principal.h"
#include "Timer.h"
using namespace std;

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
    fstream f;
    string ruta;
    
    do {
        std::cout << "Nombre del fichero (sin extension): " << std::flush;
        getline(std::cin >> std::ws, fichero);
        std::cout << std::endl;
        
        ruta = "./DAT/" + fichero + ".dat";
        f.open ( ruta.c_str() , std::ios::in);
        if(!f.is_open())
            cout << "No existe el fichero: " << fichero << ".dat" << endl;
    } while(!f.is_open());
    
    f.close();
}

void Principal::elegirAlgoritmo() {
    unsigned short opcion;
    
    do {
        cout << "Seleccione algoritmo: " << endl;
        cout << "1.Greedy" << endl
             << "2.BL" << endl 
             << "3.BT" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;
    } while (opcion < 1 || opcion > 3);
    
    switch(opcion) {
        case 1:
            tipo = ALG_Greedy;
        break;
        
        case 2:
            tipo = ALG_BL;
        break;
        
        case 3:
            tipo = ALG_BT;
        break;
    }
}

void Principal::elegirSemilla() {
    std::cout << std::endl << "Introduzca la semilla: ";
    std::cin >> semilla;
    std::cout << std::endl;

    srand(semilla);
}

void Principal::construirAlgoritmo() {
    if(metaheuristica)
        delete metaheuristica;

    //Instanciación de la metaheurística
    switch(tipo) {
        case ALG_Greedy:
             //metaheuristica = new Greedy("./DAT/" + fichero + ".dat");
        break;
        
        case ALG_BL:
             metaheuristica = new BL("./DAT/" + fichero + ".dat");
        break;
        
        case ALG_BT:
             metaheuristica = new BT("./DAT/" + fichero + ".dat");
        break;
    }  
}

void Principal::ejecutarAlgoritmo() {
    unsigned long coste;
    
    construirAlgoritmo();
    
    tiempo.start();
    coste = metaheuristica->ejecutar();
    tiempo.stop();
    
    cout << "Coste: " << coste << endl;
    cout << "Tiempo (ms): " << tiempo.getElapsedTimeInMilliSec() << endl;
    cout << endl;
}

string const Principal::tipo_str() {
    switch(tipo) {
        case ALG_Greedy:
            return "Greedy";
        break;
        
        case ALG_BL:
            return "BL";
        break;
        
        case ALG_BT:
            return "BT";
        break;
    }
}

//MÉTODOS PUBLIC
//==============

void Principal::iniciarMenu() {

    unsigned short int opcion;

    do {

        cout << "//////////////////////////////////////////////////////////////////" << endl;
        cout << "///////////////////Metaheuristicas - Practica 1///////////////////" << endl;
        cout << "//////////////////////////////////////////////////////////////////" << endl << endl;

        cout << "Algoritmo: " << tipo_str() << endl;
        cout << "Fichero: " << fichero << ".dat" << endl;
        cout << "Semilla: " << semilla << endl << endl;

        cout << "¿Que desea hacer?" << endl << endl;

        cout << "1. Ejecutar algoritmo" << endl;
        cout << "2. Cambiar algoritmo" << endl;
        cout << "3. Cambiar fichero" << endl;
        cout << "4. Cambiar semilla" << endl;
        cout << "5. Cerrar el programa" << endl << endl;

        do {
            cout << "Opcion: ";
            cin >> opcion;
            skipline(cin);
            cout << endl;
        } while (opcion < 1 || opcion > 5);

        switch (opcion) {
            case 1:
            {
                ejecutarAlgoritmo();
                break;
            }
            case 2:
            {
                elegirAlgoritmo();
                break;
            }
            case 3:
            {
                elegirFichero();
                break;
            }
            case 4:
            {
                elegirSemilla();
                break;
            }
            case 5:
            {
                exit(0);
                break;
            }
        }

    } while (true);
}
