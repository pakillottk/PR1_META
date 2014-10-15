/* 
 * File:   Resultado.h
 * Author: alumno
 *
 * Created on 8 de octubre de 2014, 12:18
 */

#ifndef RESULTADO_H
#define	RESULTADO_H

class Resultado {
    public:
        unsigned long coste;
        unsigned long tiempo;
        
        Resultado(){}
        Resultado(unsigned _coste, unsigned _tiempo): coste(_coste), tiempo(_tiempo)
        {}    
};

#endif	/* RESULTADO_H */

