/*
 * File:   Principal.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:26
 */

#ifndef PRINCIPAL_H
#define	PRINCIPAL_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Utils.h"
#include "Timer.h"
#include "Metaheuristica.h"
#include "Greedy.h"
#include "BL.h"
#include "BT.h"

enum Tipo_Algoritmo {ALG_Greedy, ALG_BL, ALG_BT};
//Enumeración que define los tres algoritmos empleados en la aplicación


/*
 *      Clase principal de la aplicación.
 *      Contiene los datos de control principales
 *      y la instancia del objeto encargado de realizar
 *      la metaheurística...
 *
 */
class Principal {
    protected:
        Metaheuristica* metaheuristica;
        Tipo_Algoritmo tipo;
        std::string fichero;
        unsigned semilla; //Semilla para los generadores pseudoaleatorios       
        
        void construirAlgoritmo();
        void activarDebug();        
        void elegirFichero();
        void elegirAlgoritmo();
        void elegirSemilla();
        void ejecutarAlgoritmo();
        void guardarResultados(unsigned long costeObtenido, unsigned tiempo);
        //Vuelca los resultados de ejecutar el algoritmo a un fichero
        //con mismo nombre del fichero evaluado
        
        string const tipo_str();

    public:
        static bool debug; //Activa o desactiva el modo debug

        Principal();
        virtual ~Principal();
        void iniciarMenu();
};

#endif	/* PRINCIPAL_H */

