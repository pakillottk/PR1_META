#include "Utils.h"

int LimiteEntero(int limi, int limis, int valor) {

    if (valor >= limi && valor <= limis)
        return valor;

    do {
        cout << "El valor introducido debe ser entre " << limi << " y " << limis << ": ";
        cin >> valor;
        skipline(cin);
    } while (valor < limi || valor > limis);

    return valor;
}

string LimiteCadena(unsigned int limi, unsigned int limis, string valor) {

    if (valor.length() >= limi && valor.length() <= limis)
        return valor;

    do {
        cout << "El valor introducido debe tener una longitud entre " << limi << " y " << limis << " caracteres: ";
        getline(cin, valor);
    } while (valor.length() < limi || valor.length() > limis);

    return valor;
}

int Limites(int limi, int limis, string mensaje) {

    int dato;

    do {

        cout << mensaje;
        cin >> dato;
        skipline(cin);

    } while (dato < limi || dato > limis);

    return dato;
}

void skipline(std::istream &stream) {
    string dummy;
    getline(stream, dummy);
}
