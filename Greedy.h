/*
 * File:   Greedy.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:40
 */

#ifndef GREEDY_H
#define	GREEDY_H

#include <iostream>
#include <string>

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo Greedy.
 */
class Greedy : public Metaheuristica {
    public:
        Greedy(const std::string& rutaFichero);
        virtual ~Greedy();

        virtual unsigned long ejecutar();
};

#endif	/* GREEDY_H */
