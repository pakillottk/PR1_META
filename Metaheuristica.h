/*
 * File:   Metaheuristica.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:27
 */

#ifndef METAHEURISTICA_H
#define	METAHEURISTICA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

/*
 *      Clase base para definir los algoritmos para las metaheurísticas.
 *
 *      Contiene definidos los atributos y métodos genéricos, así como un
 *      método virtual que nos permitirá, mediante el polimorfismo, almacenar,
 *      en un atributo de tipo Metaheurística, un objeto que implemente un
 *      algoritmo concreto y mantener su funcionalidad característica.
 *
 */
class Metaheuristica{
    protected:
        unsigned** flujo;       //Matriz de flujo
        unsigned** distancias;  //Matriz de distancias
        unsigned* solucion;     //Solución actual
        unsigned tam;           //Tamaño del problema

        void construyeMatriz(unsigned**& m);    //Construye matriz de tam*tam
        void destruyeMatriz(unsigned**& m);     //Destruye matriz de tam*tam
        void visualizarMatriz(unsigned**& m);   //Visualiza matriz de tam*tam

        void leerMatriz(unsigned**& m, std::fstream& f);
        //Lee una matriz tam*tam, desde fichero

        void leerFicheroDAT(const std::string& rutaFichero);
        //Establece el estado del objeto, desde un fichero. Crea y rellena
        //las matrices y establece el tamaño.

        unsigned long calculaCoste();
        //Calcula el coste de la solución actual. Según la función objetivo
        //definida en el enunciado del problema.

        unsigned long calculaCoste(unsigned* p);
        //Calcula el coste de la permutación dada. Según la función objetivo
        //definida en el enunciado del problema.

        void generarSolucion();
        //Genera una permutación aleatoria en
        //solución
        
       void generarSolucion(unsigned* p); 
       //Genera una permutación aleatoria en p
      
    public:
        Metaheuristica(const std::string& rutaFichero);
        virtual ~Metaheuristica();

        virtual unsigned long ejecutar() { return 0; }
        //Ejecuta el algoritmo. En este caso, es una clase genérica, por lo que
        //no ejecuta nada. Los objetos que heredarán de este, contendrán en este
        //método la funcionalidad correspondiente.
};

#endif	/* METAHEURISTICA_H */

