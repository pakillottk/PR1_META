
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
             metaheuristica = new Greedy("./DAT/" + fichero + ".dat");
        break;
        
        case ALG_BL:
             metaheuristica = new BL("./DAT/" + fichero + ".dat");
        break;
        
        case ALG_BT:
            Config_BT config_bt;
            bool vecinos_prop;
            bool reinicios_prop;
            bool tabuActivo_prop;
            configurarBT(config_bt, vecinos_prop, reinicios_prop, tabuActivo_prop);
            
            metaheuristica = new BT("./DAT/" + fichero + ".dat", 
                                    config_bt, vecinos_prop, reinicios_prop,
                                    tabuActivo_prop);
        break;
    }  
}

void Principal::configurarBT(Config_BT& config, bool& vecinos_prop, 
                             bool& reinicios_prop, bool& tabuActivo_prop) 
{
    char v;
    int opcion = 0;
    
    do {
        cout << "Seleccione opcion:" << endl;
        cout << "1.Usar configuracion estandar:" << endl;
        cout << "   Max. Evaluaciones: 10000" << endl;
        cout << "   Vecinos: 30" << endl;
        cout << "   Reinicio en: 10 sin mejorar" << endl;
        cout << "   Tabu activo: proporcional a tam" << endl;
        cout << endl;
        
        cout << "2.Usar configuracion recomendada:" << endl;
        cout << "   Max. Evaluaciones: 30000" << endl;
        cout << "   Vecinos: proporcional a tam" << endl;
        cout << "   Reinicio en: proporcional a tam" << endl;
        cout << "   Tabu activo: proporcional a tam" << endl;
        cout << endl;
        cout << "3.Usar configuracion personalizada:" << endl;
        cout << endl;
        
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;
    } while (opcion < 1 || opcion > 3);
    
    switch(opcion) {
        case 1:
        {
            config.max_evaluaciones = 10000;
            config.vecinos = 30;
            config.reinicio = 10;
            vecinos_prop = false;
            reinicios_prop = false;
            tabuActivo_prop = true;
            break;
        }
        
        case 2:
        {
            config.max_evaluaciones = 30000;           
            vecinos_prop = true;
            reinicios_prop = true;
            tabuActivo_prop = true;
            break;
        }
        
        case 3: 
        {
            config.max_evaluaciones = 0;
            do {
                cout << "Maximo de evaluaciones (minimo 10000): ";
                cin >> config.max_evaluaciones;
                cout << endl;
            } while (config.max_evaluaciones < 10000);

            do {
                cout << "Generacion de vecinos proporcional a tam (s/n): ";
                cin >> v;  
                cout << endl;
            } while(v != 's' && v != 'n');

            if(v =='s') {
                vecinos_prop = true;
            } else {
                vecinos_prop = false;
                config.vecinos = 0;
                do{
                    cout << "Numero de vecinos (minimo 30): ";
                    cin >> config.vecinos;
                    cout << endl;
                } while (config.vecinos < 30);
            }

            do {
                cout << "Iteraciones hasta reinicio proporcional a tam (s/n): ";
                cin >> v;  
                cout << endl;
            } while(v != 's' && v != 'n');

            if(v =='s') {
                reinicios_prop = true;
            } else {
                reinicios_prop = false;
                config.reinicio = 0;
                do{
                    cout << "Iteraciones hasta reinicio (minimo 10): ";
                    cin >> config.reinicio;
                    cout << endl;
                } while (config.reinicio < 10);
            }

            do {
                cout << "Iteraciones que un mov. es tabu proporcional a tam (s/n): ";
                cin >> v;  
                cout << endl;
            } while(v != 's' && v != 'n');

            if(v =='s') {
                tabuActivo_prop = true;
            } else {
                tabuActivo_prop = false;
                config.tabuActivo = 0;
                do{
                    cout << "Iteraciones que un mov es Tabu (minimo 5): ";
                    cin >> config.tabuActivo;
                    cout << endl;
                } while (config.tabuActivo < 10);
            }
            break;
        }
    }
}

void Principal::ejecutarAlgoritmo() {
    unsigned long coste;
    double tiempo;
    Timer timer;
    
    construirAlgoritmo();
    
    timer.start();
    coste = metaheuristica->ejecutar();
    timer.stop();    
   
    tiempo = timer.getElapsedTimeInMilliSec();
 
    cout << "Coste: " << coste << endl;  
   
    cout << "Tiempo (ms): " << tiempo << endl;
    
    cout << endl;
    
    cout << "Guardando resultados..." << endl;
    guardarResultados(coste, tiempo);
    cout << "Resultados almacenados" << endl;
    cout << endl;
}

void Principal::guardarResultados(unsigned long costeObtenido, unsigned tiempo) {
    fstream f;
    string ruta = "./RESULTADOS/" + fichero + ".txt";
    
    f.open(ruta.c_str(), ios::out | ios::app);
    
    f << "Algoritmo: " << tipo_str() << "\r\n";
    f << "Semilla: " << semilla << "\r\n";
    f << "Coste: " << costeObtenido << "\r\n";   
    
    f << "Tiempo (ms): " << tiempo  << "\r\n"; 
    f << "\r\n";
    f.close();
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
