
#include "BT.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
BT::BT(const std::string& rutaFichero): Metaheuristica(rutaFichero) {
    tabuActivo = 5;
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

//MÉTODOS PUBLIC
//==============
unsigned long BT::ejecutar() {
    generarSolucion();
    
    unsigned* p = new unsigned[tam];
    for(unsigned i = 0; i < tam; i++) {
        p[i] = solucion[i];
    }
    
    unsigned evaluaciones = 0;
    unsigned sinMejora = 0;
    
    while(evaluaciones < 10000) {
        if(sinMejora == 10){
            reiniciar(p);
        }
        
        actualizaListaTabu();
        
        bool* generados = new bool[tam];
        for(unsigned k = 0; k < tam; k++) {
            generados[k] = false;
        }
        
        unsigned i;
        unsigned j;
        unsigned vecino = 0;
        long costeMinimo = 9999999;
        pair<unsigned, unsigned> mejorMovimiento;
        long costeActual;
        
        while(vecino < 30) {           
            do{
                i = rand()%tam;
                do {
                  j = rand()%tam;
                }while(j == i);
            }while(esTabu(p, i, j) || (generados[i] && generados[j]));          
            
            generados[i] = generados[j] = true;
            
            costeActual = mejoraCambio(p, i, j);
            if(costeActual < costeMinimo) {
                costeMinimo = costeActual;
                mejorMovimiento.first = i;
                mejorMovimiento.second = j;
            }
            
            vecino++;
        }
        
        
        
        if(actualizar(p, mejorMovimiento.first, mejorMovimiento.second)) {
            sinMejora = 0;
        } else {
            ++sinMejora;
        }
        
        delete [] generados;
        evaluaciones++;
    }
    
    delete [] p;            
    return calculaCoste();
}

//MÉTODOS PROTECTED
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
    
    if(solucion != p) {
      unsigned costeParcial_p;
      unsigned costeParcial_sol;
      
      costeParcial_p += costeParcial(p, i);
      costeParcial_p += costeParcial(p, j);
      
      costeParcial_sol += costeParcial(solucion, i);
      costeParcial_sol += costeParcial(solucion, j);
      
      if(costeParcial_p < costeParcial_sol) {
          intercambiar(solucion, i, j);
          globalMejorada = true;
      }
    }
    
    intercambiar(p, i,j);
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
    
    if(movimientos.size() == tabuTam) {        
        pair<unsigned,unsigned> to_del = movimientos.back();
        mem_tabu[to_del.first][to_del.second] = 0;       
        movimientos.pop_back();        
        
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
    for(it = movimientos.begin(); it != movimientos.end(); it++) {    
        mem_tabu[(*it).first][(*it).second] = 0;         
    }    
    
    movimientos.clear();
}

void BT::reiniciar(unsigned*& p) {
    unsigned random = rand() % 100;
    unsigned random_t = rand() % 100;
    
    if(random < 50) { //usar memoria a largo plazo
        unsigned menosFrecuente;
        unsigned minFrecuencia;
        for(unsigned i = 0; i < tam; i++) {
            minFrecuencia = 9999;
            
            for(unsigned j = 0; j < tam; j++) {
                if(frec[i][j] < minFrecuencia) {
                    minFrecuencia = frec[i][j];
                    menosFrecuente = j;
                }
            }
            
            solucion[i] = menosFrecuente;
        }
    } else {
        if(random < 75) { //generar solucion aleatoria
            generarSolucion();
        }
    }
    
    for(unsigned i = 0; i < tam; i++) {
        p[i] = solucion[i];
    }
    
    if(random_t < 50) {
        tabuTam += tabuTam/2;
    } else {
        tabuTam -= tabuTam/2;
    }
    
    reiniciarListaTabu();
}

