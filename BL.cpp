
#include "BL.h"
#include "Principal.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
BL::BL(const std::string& rutaFichero): Metaheuristica(rutaFichero){
    dlb = new bool[tam];
    for(unsigned i = 0; i < tam; i++)
        dlb[i] = false;
}

BL::~BL(){
    delete [] dlb;
}

//MÉTODOS PROTECTED
//=================

//Implementación del algoritmo de búsqueda local
unsigned long BL::ejecutar() {
    if(Principal::debug)
        std::cout << "Generando solucion..." << std::endl;

    //Comenzamos generando una solución aleatoria...
   generarSolucion();

   if(Principal::debug) {
        std::cout << "SOLUCION INICIAL";
        for(unsigned i = 0; i < tam; i++) {
            if(!i%tam)
                std::cout << std::endl;
            std::cout << solucion[i] << " ";
        }

        std::cout << std::endl;
        std::cout << "Coste inicial: " << calculaCoste()
                  << std::endl;
    }

   if(Principal::debug)
    std::cout << "Iniciando busqueda local..." << std::endl;

    //Procedemos a iterar por el espacio de búsqueda
    unsigned evaluaciones = 0; //Contador de evaluaciones
    bool mejora; //Flag para indicar si hemos encontrado mejora en el entorno
    bool finBusqueda = false; //Flag que indicará si la búsqueda debe terminar, por
                              //no encontrar mejoría en todo el entorno

    while(evaluaciones < 10000) {
        //Generamos y evaluamos los vecinos
        for(unsigned i = 0; i < tam; i++) {
            if(!dlb[i]) { //Si la posición está marcada en dlb, ignoramos
                mejora = false;

                for(unsigned j = 0; j < tam; j++) {
                    if(i==j)
                        continue;

                    if(mejoraCambio(solucion, i, j)) { //Si el vecino mejora, actualizamos
                        if(Principal::debug)
                            std::cout << "Intercambio " << i << " a " << j
                                     << " mejora, actualizando..." << std::endl;

                        dlb[i] = false;
                        dlb[j] = false;
                        mejora = true;

                        intercambiar(solucion, i,j);
                        break;
                    }
                }

                if(!mejora) { //No se encontró mejora para la posición i, actualizamos dlb
                    if(Principal::debug)
                        std::cout << i << " no mejora, actualizando dlb..."
                                  << std::endl;
                    dlb[i] = true;

                    if(i == tam-1) { //Terminamos de explorar y no hay mejoras, fin de la búsqueda
                        if(Principal::debug)
                            std::cout << "Sin mejora en el entorno, fin de la busqueda..."
                                      << std::endl;

                        finBusqueda = true;
                    }
                } else {
                    break;
                }
            }
        }    
        
        evaluaciones++;
        
        if(finBusqueda)
            break;
    }

    if(Principal::debug) {
        std::cout << "SOLUCION";
        for(unsigned i = 0; i < tam; i++) {
            if(!i%tam)
                std::cout << std::endl;
            std::cout << solucion[i] << " ";
        }

        std::cout << std::endl;
        std::cout << "Coste: " << calculaCoste()
                  << std::endl;
    }

    return calculaCoste();
}

void BL::intercambiar(unsigned*& p, unsigned i, unsigned j) {
    unsigned aux = p[i];
    p[i] = p[j];
    p[j] = aux;
}

bool BL::mejoraCambio(unsigned*& p, unsigned i, unsigned j) {
    long int prev_coste = 0, n_coste = 0;

    prev_coste += costeParcial(p, i);
    prev_coste += costeParcial(p, j);

    intercambiar(p, i, j);

    n_coste += costeParcial(p, i);
    n_coste += costeParcial(p, j);

    intercambiar(p, i, j);

    return n_coste < prev_coste;
}

unsigned BL::costeParcial(unsigned*& p, unsigned i) {
    unsigned long coste = 0;

    for(unsigned j = 0; j < tam; j++) {
        coste += flujo[i][j] * distancias[p[i]][p[j]];
    }

    return coste;
}
