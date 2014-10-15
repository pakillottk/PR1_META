/*
 * File:   main.cpp
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:26
 */

#include <cstdlib>
#include <iostream>
#include "Principal.h"
#include "Resultado.h"
using namespace std;

int main(void) {
   Principal principal;
   //principal.iniciarMenu();

   unsigned long coste = principal.ejecutarAlgoritmo();
   cout << "COSTE SOLUCION: " << coste << endl;

   return 0;
}

