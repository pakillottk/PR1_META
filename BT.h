/*
 * File:   BT.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:49
 */

#ifndef BT_H
#define	BT_H

#include <iostream>
#include <string>
#include <list>
#include <utility>
#include "Principal.h"
#include "Metaheuristica.h"
#include "Greedy.h"
#include "Config_BT.h"
using namespace std;

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo de Búsqueda Tabú.
 */
class BT : public Metaheuristica {
    protected:
        unsigned max_evaluaciones;
        unsigned vecinos;
        unsigned reinicio;       
        unsigned** frec; //Memoria a largo plazo
        unsigned** mem_tabu; //Memoria a corto plazo
        unsigned tabuActivo; //Determina cuantas iteraciones es tabú
                             //un movimiento
        unsigned tabuTam;    //Tamaño lista tabú
        list<pair<unsigned, unsigned> > movimientos;
        
        void llamarGreedy(unsigned* p, unsigned** f, unsigned** d, unsigned n);
        
        bool esTabu(unsigned*& p, unsigned i, unsigned j);
        //Indica si un movimiento es tabu activo o no
        
        bool actualizar(unsigned*& p, unsigned i, unsigned j);
        //Intercambia la posición i por la j y actualiza las estructuras
        //tabu. Devuelve true si la solución global ha mejorado. False, en
        //caso contrario.
        
        void actualizaListaTabu();
        
        void reiniciar(unsigned*& p);
        
        void reiniciarListaTabu();
        
        void marcarTabu(unsigned*& p, unsigned i, unsigned j);
        
        void intercambiar(unsigned*& p, unsigned i, unsigned j);
        //Intercambia la posición i por la j.

        long mejoraCambio(unsigned*& p, unsigned i, unsigned j);
        //Devuelve la mejora obtenida al intercambiar i por j

        unsigned costeParcial(unsigned*& p, unsigned i);
        //Dada una permutación y una posición, calcula el coste
        //asignado a esa posición
        
    public:
        BT(const std::string& rutaFichero, Config_BT config, bool vecinos_prop = false,
           bool reinicios_prop = false, bool tabuActivo_prop = false);
        virtual ~BT();

        virtual unsigned long ejecutar();
};


#endif	/* BT_H */

