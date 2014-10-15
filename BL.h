/*
 * File:   BL.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:44
 */

#ifndef BL_H
#define	BL_H

#include <iostream>
#include <string>
#include <bitset>

#include "Metaheuristica.h"

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo de Búsqueda Local.
 */
class BL : public Metaheuristica {
    protected:
        bool* dlb; //Vector binario, don't look bits

        void intercambiar(unsigned*& p, unsigned i, unsigned j);
        //Intercambia la posición i por la j.

        bool mejoraCambio(unsigned*& p, unsigned i, unsigned j);
        //Devuelve true, si intercambiar ambas posiciones mejora.
        //Devuelve false, en caso contrario.

        unsigned costeParcial(unsigned*& p, unsigned i);
        //Dada una permutación y una posición, calcula el coste
        //asignado a esa posición
    public:
        BL(const std::string& rutaFichero);
        virtual ~BL();

        virtual unsigned long ejecutar();
};

#endif	/* BL_H */

