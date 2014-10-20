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

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo Greedy.
 */
class Greedy : public Metaheuristica {
public:
    Greedy(const std::string& rutaFichero);
    virtual ~Greedy();

    virtual unsigned long ejecutar() {

        unsigned *pFlujo = new unsigned[tam];
        unsigned *pDistancia = new unsigned[tam];
        bool *puUsado = new bool[tam];
        bool *plUsado = new bool[tam];
        unsigned solucion[tam];

        unsigned sumaFlujo;
        unsigned sumaDistancia;

        for (int i = 0; i < tam; ++i) {

            sumaFlujo = 0;
            sumaDistancia = 0;

            for (int j = 0; j < tam; ++j) {

                sumaFlujo += flujo[i][j];
                sumaDistancia += distancias[i][j];

            }

            pFlujo[i] = sumaFlujo;
            pDistancia[i] = sumaDistancia;
            puUsado[i] = false;
            plUsado[i] = false;

        }

        for (int i = 0; i < tam; ++i) {

            int maxFlujo = INT_MIN;
            int posMax;
            int minDistancia = INT_MAX;
            int posMin;

            for (int j = 0; j < tam; ++j) {

                if (!puUsado[j]) {

                    if (pFlujo[j] > maxFlujo) {
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
            
            puUsado[posMax] = true;
            plUsado[posMin] = true;
            solucion[posMin] = posMax;

        }
        
        delete [] pFlujo;
        delete [] pDistancia;
        delete [] puUsado;
        delete [] plUsado;
        
        return calculaCoste(solucion);

    }

};

#endif	/* GREEDY_H */

