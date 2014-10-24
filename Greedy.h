/*
 * File:   Greedy.h
 * Author: Fasgort
 *
 * Created on 5 de octubre de 2014, 12:40
 */

#ifndef GREEDY_H
#define	GREEDY_H

#include <iostream>
#include <string>
#include <climits>

#include "Metaheuristica.h"
using namespace std;

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo Greedy.
 */
class Greedy : public Metaheuristica {
    public:
        Greedy(const std::string& rutaFichero);
        virtual ~Greedy();

        virtual unsigned long ejecutar();
        static void alg_greedy(unsigned* s, unsigned** f, unsigned** d, unsigned tam);
};

#endif	/* GREEDY_H */

