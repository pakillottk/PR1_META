
#include "Greedy.h"
#include "Principal.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
Greedy::Greedy(const std::string& rutaFichero): Metaheuristica(rutaFichero) {}
Greedy::~Greedy() {}

//METODOS PUBLICOS
//================
unsigned long Greedy::ejecutar() {  
    unsigned long *pFlujo = new unsigned long[tam];
    unsigned long *pDistancia = new unsigned long[tam];
    bool *puUsado = new bool[tam];
    bool *plUsado = new bool[tam];
       

    unsigned long sumaFlujo;
    unsigned long sumaDistancia;

    if(Principal::debug)
        cout << "Calculando potenciales..." << endl;
    
    for (unsigned i = 0; i < tam; i++) {

        sumaFlujo = 0;
        sumaDistancia = 0;

        for (unsigned j = 0; j < tam; j++) {

            sumaFlujo += flujo[i][j];
            sumaDistancia += distancias[i][j];

        }
        
        if(Principal::debug)
            cout << "Potencial de u" << i << ": " << sumaFlujo << endl;
        pFlujo[i] = sumaFlujo;
        
        if(Principal::debug)
            cout << "Potencial de d" << i << ": " << sumaDistancia << endl;
        pDistancia[i] = sumaDistancia;
        
        puUsado[i] = false;
        plUsado[i] = false;

    }

    if(Principal::debug)
        cout << "Potenciales calculados..." << endl;
    
    unsigned long maxFlujo;
    unsigned posMax;
    unsigned long minDistancia;
    unsigned posMin;
    
    
    if(Principal::debug)
        cout << "Calculando solucion..." << endl;
    
  
    for (unsigned i = 0; i < tam; i++) {
        maxFlujo = 0;
        minDistancia = INT_MAX;

        for (unsigned j = 0; j < tam; j++) {

            if (!puUsado[j]) {
                
                if (pFlujo[j] >= maxFlujo) {                   
                    maxFlujo = pFlujo[j];
                    posMax = j;
                }
            }

            if (!plUsado[j]) {
                
                if (pDistancia[j] < minDistancia) {                   
                    minDistancia = pDistancia[j];
                    posMin = j;
                }
            }
        }

        if(Principal::debug)
            cout << "Unidad " << posMax << " asignada a " << posMin << endl;

        puUsado[posMax] = true;
        plUsado[posMin] = true;
        solucion[posMax] = posMin;
    }
    
    
    
    delete [] pFlujo;
    delete [] pDistancia;
    delete [] puUsado;
    delete [] plUsado;
    
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