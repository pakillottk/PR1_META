
#include "BT.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
BT::BT(const std::string& rutaFichero): Metaheuristica(rutaFichero) {
    tabuActivo = tam*0.10;
    tabuTam = tam/2;
    
    construyeMatriz(frec); 
    construyeMatriz(mem_tabu);
    
    for(unsigned i = 0; i < tam; i++)
        for(unsigned j = 0; j < tam; j++) {
            frec[i][j] = mem_tabu[i][j] =  0;
        }
}

BT::~BT() {
    destruyeMatriz(frec);
    destruyeMatriz(mem_tabu);    
}

//METODOS PUBLIC
//==============
unsigned long BT::ejecutar() {
    if(Principal::debug)
        cout << "Generando solucion..." << endl;
    
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
        cout << "Copiando solucion en permutacion auxiliar..." << endl;
    
    unsigned* p = new unsigned[tam];
    for(unsigned i = 0; i < tam; i++) {
        p[i] = solucion[i];
    }
    
    unsigned evaluaciones = 0;
    unsigned sinMejora = 0;
    
    unsigned i;
    unsigned j;
    unsigned vecino;
    long costeMinimo;
    pair<unsigned, unsigned> mejorMovimiento;
    long costeActual;
    unsigned libres;
    
    if(Principal::debug)
        cout << "Iniciando busqueda tabu..." << endl;
    
    while(evaluaciones < 10000) {
        if(Principal::debug)
            cout << "EVALUACION: " << evaluaciones << endl;
        
        if(sinMejora == 10){
            if(Principal::debug)
                cout << "10 evaluaciones sin mejorar, reiniciando..." << endl;
            
            reiniciar(p);
            sinMejora = 0;
            
            if(Principal::debug)
                cout << "Busqueda reiniciada..." << endl;
        }
        
        if(Principal::debug)
            cout << "Actualizando lista tabu..." << endl;
        
        actualizaListaTabu();
        
        bool* generados = new bool[tam];
        for(unsigned k = 0; k < tam; k++) {
            generados[k] = false;
        }
        
        libres = tam;
        vecino = 0;
        costeMinimo = 9999999;
        
        if(Principal::debug)
            cout << "Generando vecinos..." << endl;
        
        while(vecino < 30) {           
            do{
                if(libres == 0)
                    break;
                
                i = rand()%tam;
                do {
                  j = rand()%tam;
                }while(j == i);
           }while(generados[i] && generados[j]);          
            
            if(!generados[i]) {
                generados[i] = true;
                libres--;
            }
            if(!generados[j]) {
                generados[j] = true;
                libres--;
            }
            
            if(!esTabu(p, i, j)) {
                costeActual = mejoraCambio(p, i, j);
                if(costeActual < costeMinimo) {
                    costeMinimo = costeActual;
                    mejorMovimiento.first = i;
                    mejorMovimiento.second = j;
                }
            }
            
            vecino++;
        }       
        
        if(Principal::debug) {
            cout << "Actualizando con mejor movimiento..." << endl;
            cout << "Intercambiar: " << mejorMovimiento.first 
                 << " por " << mejorMovimiento.second << endl;
        }
        
        if(actualizar(p, mejorMovimiento.first, mejorMovimiento.second)) {
            if(Principal::debug)
                cout << "Solucion global mejorada..." << endl; 
            
            sinMejora = 0;
        } else {            
            ++sinMejora;
        }
        
        delete [] generados;
        evaluaciones++;
    }
    
    if(Principal::debug)
        cout << "Fin de la busqueda..." << endl;
    
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
    
    delete [] p;            
    return calculaCoste();
}

//METODOS PROTECTED
//=================

void BT::intercambiar(unsigned*& p, unsigned i, unsigned j) {
    unsigned aux = p[i];
    p[i] = p[j];
    p[j] = aux;
}

long BT::mejoraCambio(unsigned*& p, unsigned i, unsigned j) {
    long int prev_coste = 0, n_coste = 0;

    prev_coste += costeParcial(p, i);
    prev_coste += costeParcial(p, j);

    intercambiar(p, i, j);

    n_coste += costeParcial(p, i);
    n_coste += costeParcial(p, j);

    intercambiar(p, i, j);

    return n_coste - prev_coste;
}

unsigned BT::costeParcial(unsigned*& p, unsigned i) {
    unsigned long coste = 0;

    for(unsigned j = 0; j < tam; j++) {
        coste += flujo[i][j] * distancias[p[i]][p[j]];
    }

    return coste;
}

bool BT::esTabu(unsigned*& p, unsigned i, unsigned j) { 
    bool tabu = false;     
    
    if(mejoraCambio(solucion, i, j) < 0) {
        return tabu;
    }    
    
    tabu = mem_tabu[i][p[j]] > 0 || mem_tabu[j][p[i]] > 0; 
    
    return tabu;
}

bool BT::actualizar(unsigned*& p, unsigned i, unsigned j) {   
    bool globalMejorada = false;
    unsigned costeParcial_p = 0;
    unsigned costeParcial_sol = 0;
    
    intercambiar(p, i,j);
    
    if(solucion != p) {     
      costeParcial_p += costeParcial(p, i);
      costeParcial_p += costeParcial(p, j);
      
      costeParcial_sol += costeParcial(solucion, i);
      costeParcial_sol += costeParcial(solucion, j);
      
      if(costeParcial_p < costeParcial_sol) {
          intercambiar(solucion, i, j);
          globalMejorada = true;
      }
    }
    
    frec[i][p[i]]++;
    frec[j][p[j]]++;
    
    marcarTabu(p, i, j);  
    
    return globalMejorada;
}

void BT::marcarTabu(unsigned*& p, unsigned i, unsigned j) {    
    mem_tabu[i][p[i]] = tabuActivo;
    mem_tabu[j][p[j]] = tabuActivo;
    
    pair<unsigned, unsigned> p_i(i, p[i]);
    pair<unsigned, unsigned> p_j(j,p[j]);
    pair<unsigned,unsigned> to_del;
    
    while(movimientos.size() > (tabuTam*2)-2) {
        to_del = movimientos.back();
        mem_tabu[to_del.first][to_del.second] = 0;
        movimientos.pop_back();
    }   
    
    movimientos.push_front(p_i);
    movimientos.push_front(p_j);
}

void BT::actualizaListaTabu() {
    unsigned n_value;
    list<pair<unsigned, unsigned> >::iterator it;
    
    for(it = movimientos.begin(); it != movimientos.end(); it++) {    
        n_value = --mem_tabu[(*it).first][(*it).second];            
                  
        if(n_value == 0) {
            it = movimientos.erase(it);
            it--;
        }
    }       
}

void BT::reiniciarListaTabu() {    
    list<pair<unsigned, unsigned> >::iterator it;   
    unsigned i = 0;
    for(it = movimientos.begin(); it != movimientos.end(); it++) {       
        mem_tabu[(*it).first][(*it).second] = 0;         
    }    
    
    movimientos.clear();
}

void BT::reiniciar(unsigned*& p) {
    unsigned random = rand() % 100;
    unsigned random_t = rand() % 100;
    unsigned menosFrecuente;
    unsigned minFrecuencia;
    
    bool* asignados = new bool[tam];
    for(unsigned k = 0; k < tam; k++) {
        asignados[k] = false;
    }
    
    if(random < 50) { //usar memoria a largo plazo  
        if(Principal::debug)
                cout << "Reinicio a solucion poco frecuente..." << endl; 
        
        for(unsigned i = 0; i < tam; i++) {
            minFrecuencia = 9999;
            
            for(unsigned j = 0; j < tam; j++) {               
                if(frec[i][j] < minFrecuencia && !asignados[j]) {                    
                    minFrecuencia = frec[i][j];
                    menosFrecuente = j;
                }
            }
            
            solucion[i] = menosFrecuente;
            asignados[menosFrecuente] = true;
        }
    } else {
        if(Principal::debug)
            cout << "Solucion aleatoria..." << endl; 
        if(random < 75) { //generar solucion aleatoria
            generarSolucion();
        } else { //desde mejor global
            if(Principal::debug)
                cout << "Partiendo de mejor global..." << endl; 
        }
    }
    
    delete [] asignados;
    
    if(Principal::debug)
        cout << "Copiando a permutacion auxiliar..." << endl; 
    
    for(unsigned k = 0; k < tam; k++) {
        p[k] = solucion[k];
    }
    
    if(random_t < 50) {
        tabuTam += (tabuTam/2);
    } else {
        tabuTam -= (tabuTam/2);
    }
    
    reiniciarListaTabu();  
}