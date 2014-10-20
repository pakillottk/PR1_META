/*
 * File:   Utils.h
 * Author: Fasgort
 *
 * Created on 15 de octubre de 2014, 10:35
 */

#ifndef LIMITES_H
#define	LIMITES_H

#include <iostream>
using namespace std;

/**@brief Permite restringir el valor que se le pasa dentro de un rango de valores
 * @param limi Límite inferior
 * @param limis Límite superior
 * @param valor El valor al que se le aplica la restricción
 * @pre 'limi' debe ser menor que 'limis', para que la función tenga sentido
 * @return Devuelve el mismo valor si ya está dentro del rango, u otro valor que se pide si el que se le pasa no está dentro del rango
 */
int LimiteEntero(int limi, int limis, int valor);

/**@brief Permite restringir la longitud de la cadena que se le pasa dentro de un rango de valores
 * @param limi Longitud mínima
 * @param limis Longitud máxima
 * @param valor La cadena a la que se le aplica la restricción
 * @pre 'limi' debe ser menor que 'limis', para que la función tenga sentido
 * @return Devuelve la misma cadena si su longitud ya está dentro del rango, u otra cadena que se pide si la longitud de la cadena no está dentro del rango
 */
string LimiteCadena(unsigned int limi, unsigned int limis, string valor);

/**@brief Pide un dato por teclado, y comprueba que está dentro de un rango, si no lo está devuelve un mensaje y vuelve a pedir que se introduzca otro, y si está en el rango, lo devuelve tal cual
 * @param limi Límite inferior del rango
 * @param limis Límite superior del rango
 * @param mensaje Mensaje que se devuelve si el valor introducido no está en el rango
 * @return Devuelve un valor introducido que esté en el rango
 */
int Limites(int limi, int limis, string mensaje);

/**@brief Función auxiliar que limpia std::stdin, que a veces queda '\n' y da fallos al utilizar 'getline' despues de 'cin'
 * @param stream Variable que almacena '\n', simplemente para eliminarlo de std::stdin
 */
void skipline(std::istream &stream);

#endif	/* LIMITES_H */

