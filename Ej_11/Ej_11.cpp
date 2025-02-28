//Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "EnterosInf.h"

using namespace std;

typedef struct tipoMoneda {
    int valor;
    int cantidad;
};

bool operator <(const tipoMoneda& m1, const tipoMoneda& m2) {
    return m1.valor < m2.valor;
}

EntInf resolver(const vector<tipoMoneda>& monedas, int cantidad) {
    vector<EntInf> anterior(cantidad+1, Infinito);
    vector<EntInf> actual(cantidad+1);
    actual[0] = 0;
    anterior[0] = 0;

    for (int i = 0; i < monedas.size(); i++ ) {
        for (int j = 1; j <= cantidad; j++) {
            tipoMoneda moneda = monedas[i];
            int cantMax = min(j/moneda.valor, moneda.cantidad);
            actual[j] = Infinito;
            for (int e = 0; e <= cantMax; e++) {
                EntInf aux = anterior[j - e * moneda.valor] + e;
                actual[j] = min(aux, actual[j]);
            }
        }
        anterior = actual;
    }

    return actual[cantidad];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int numMonedas,cantidad;
    cin >> numMonedas;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<tipoMoneda> monedas(numMonedas);

    for (int i = 0; i < numMonedas;i++) {
        cin >> monedas[i].valor;
    }

    for (int i = 0; i < numMonedas; i++) {
        cin >> monedas[i].cantidad;
    }

    cin >> cantidad;

    sort(monedas.begin(), monedas.end());

    EntInf sol = resolver(monedas,cantidad);

    if (sol == Infinito) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << sol << "\n";
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
