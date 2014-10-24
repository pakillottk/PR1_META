
#include "Metaheuristica.h"
#include "Principal.h"


//CONSTRUCTORES Y DESTRUCTORES
//===========================

/*
 *      Dada la ruta de un fichero, debidamente formateado, construye
 *      el objeto.
 */
Metaheuristica::Metaheuristica(const std::string& rutaFichero) {
    //Leemos el fichero
    leerFicheroDAT(rutaFichero);

    //Creamos el vector de la solución
    solucion = new unsigned[tam];
}

Metaheuristica::~Metaheuristica() {
    destruyeMatriz(flujo);
    destruyeMatriz(distancias);

    delete [] solucion;
}

//MÉTODOS PROTECTED
//=================
void Metaheuristica::construyeMatriz(unsigned**& m){
    m = new unsigned*[tam];
    for(unsigned i = 0; i < tam; i++){
        m[i] = new unsigned[tam];
    }
}

void Metaheuristica::destruyeMatriz(unsigned**& m){
    for(unsigned i = 0; i < tam; i++) {
            delete [] m[i];
    }

    delete [] m;
}

void Metaheuristica::visualizarMatriz(unsigned**& m) {
    for(unsigned i = 0; i < tam; i++) {
        std::cout << std::endl;
        for(unsigned j = 0; j < tam; j++) {
            std::cout << "[" << m[i][j] << "] ";
        }
    }
}

void Metaheuristica::leerMatriz(unsigned**& m, std::fstream& f){
    unsigned row, col;       //Indices
    row = col = 0;
    std::string linea;  //Línea actual
    std::string valorActual = ""; //Valor a almacenar, en formato texto
    unsigned valor;  //Valor a almacenar, en formato entero.

    //Leemos todos los valores de la matriz
    while(row < tam) {
        getline(f, linea); //Lectura de la línea

        if(Principal::debug) {
            std::cout << "Linea actual: " << linea << std::endl;
            std::cout << "Tam: " << linea.size() << std::endl;
        }

        linea += ' ';
        //Añadimos un espacio en blanco, en caso de que el útlimo carácter de
        //la línea fuera un dato, o parte de él, este no es ignorado y se almacena
        //correctamente. Así podemos leer, de manera más simple, la línea.

        //Iteramos por toda la línea...
        for(unsigned int i = 0; i < linea.size(); i++) {
            if(Principal::debug)
                std::cout << "Caracter " << i << ": " << linea[i] << std::endl;

            //Si no es un espacio en blanco, acumulamos en valorActual
            if(linea[i] != ' ')
                valorActual += linea[i];
            else { //Espacio en blanco
                if(valorActual.size() > 0) { //Hay algo que almacenar
                    //Pasamos de texto a valor entero
                    std::istringstream buffer(valorActual);
                    buffer >> valor;

                    //Reiniciamos el acumulador, valorActual
                    valorActual = "";

                    if(Principal::debug)
                            std::cout << "Guardando " << valor << " en row: " << row << " col: " << col << std::endl;

                    //Almacenamos en la matriz
                    m[row][col] = valor;

                    //Actualizamos los índices
                    col++;
                    if(col == tam){
                        row++;
                        col = 0;
                    }
               }
            }
        }
    }
}

void Metaheuristica::leerFicheroDAT(const std::string& rutaFichero){
    //Variables auxiliares
    std::fstream ficheroEntrada;
    std::string linea;

    ficheroEntrada.open ( rutaFichero.c_str() , std::ios::in);
   //Abrimos el fichero

    if (ficheroEntrada.is_open()) { //Comprobamos apertura correcta

        //Leemos el tamaño
        getline(ficheroEntrada, linea);
        std::istringstream bufferTam(linea);
        bufferTam >> tam;

        if(Principal::debug)
                std::cout << std::endl << "El tamanio es: " << tam << std::endl;

        //Creamos las matrices
        construyeMatriz(flujo);
        construyeMatriz(distancias);

        getline(ficheroEntrada, linea);
        //Leemos, e ignoramos, la línea en blanco

        if(Principal::debug)
                std::cout << "Linea en blanco: " << linea << std::endl;

        leerMatriz(flujo, ficheroEntrada);
        //Rellenamos la matriz de flujo, con los datos del fichero

        if(Principal::debug)
                std::cout << std::endl << "FLUJO LEIDO" << std::endl << std::endl;

        getline(ficheroEntrada, linea);
        //Leemos, e ignoramos, la línea en blanco

        if(Principal::debug)
                std::cout << "Linea en blanco: " << linea << std::endl;

        leerMatriz(distancias, ficheroEntrada);
        //Rellenamos la matriz de distancias, con los datos del fichero

        if(Principal::debug)
                std::cout << std::endl << "DISTANCIAS LEIDAS" << std::endl << std::endl;

        ficheroEntrada.close(); //Cerramos el fichero
    }
    else std::cout << "Fichero inexistente o faltan permisos para abrirlo" << std::endl;
}

unsigned long Metaheuristica::calculaCoste() {
    return calculaCoste(solucion);
}

unsigned long Metaheuristica::calculaCoste(unsigned *p) {
    unsigned long coste = 0;

    for(unsigned i = 0; i < tam; i++)
        for(unsigned j = 0; j < tam; j++){
            coste += flujo[i][j] * distancias[p[i]][p[j]];
        }

    return coste;
}

void Metaheuristica::generarSolucion() {
    generarSolucion(solucion);
}

void Metaheuristica::generarSolucion(unsigned* p) {
    bool* asignados = new bool[tam];

    for(unsigned i = 0; i < tam; i++) {
        asignados[i] = false;
    }

    unsigned valor = 0;
    for(unsigned i = 0; i < tam; i++) {
        do{
            valor = rand()%tam;
        }while(asignados[valor]);

        p[i] = valor;
        asignados[valor] = true;
    }

    delete [] asignados;
}