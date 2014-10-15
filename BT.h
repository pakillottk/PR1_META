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

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo de Búsqueda Tabú.
 */
class BT : public Metaheuristica {
    protected:
        unsigned** frec; //Memoria a largo plazo
        unsgined** mem_tabu; //Memoria a corto plazo

    public:
        BT(const std::string& rutaFichero);
        virtual ~BT();

        virtual unsigned long ejecutar();
};


#endif	/* BT_H */

