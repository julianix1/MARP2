// Julián Reguera Peñalosa

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

struct cuerda {
    int longitud;
    int precio;
};

struct nodo {
    EntInf costeMin;
    long long int combinaciones;
    EntInf cuerdasMin;
};

/*
Hemos usado 3 recursiones distintas una para cada cosa que se pide

int minCoste(i,j):indica el coste minimo para llegar a una cuerda de longitud j con las i primeras cuerdas
int minCuerdas(i,j): indica el minimo de cuerdas a usar para llegar a una cuerda de longitud j con las i primeras cuerdas
int numOpciones(i,j): indica el numero de combinacones posibles para llegar a una cuerda de longitud j con las i primeras cuerdas

                    | Infinito si j > 0 y i <= 0
                    | 0 si j == 0
int minCoste(i,j) = | minCoste(i-1,j) si j > Ci.longitud
                    | min(minCoste(i-1,j-Ci.longitud) + Ci.coste, minCoste(i-1,j)) si j <= Ci.longitud y i > 0

                      | Infinito si j > 0 y i <= 0
                      | 0 si j == 0
int minCuerdas(i,j) = | minCoste(i-1,j) si j > Ci.longitud y i > 0
                      | min(minCoste(i-1,j-Ci.longitud) + Ci.coste, minCoste(i-1,j)) si j <= Ci.longitud y i > 0

                       | 1 si j == 0;
                       | 0 si j > 0 y i <= 0
int numOpciones(i,j) = | numOpciones(i-1,j) + numOpciones(i-1,j-Ci.longitud) si j <= Ci.longitud y i > 0
                       | numOpciones(i-1,j) si j<= Ci.longitud y i > 0
*/

nodo cuerda_cometa(vector<cuerda> const& M, int L) {
    int n = M.size();

    vector<nodo> cuerdas(L + 1, { Infinito,0,Infinito });
    cuerdas[0].costeMin = 0;
    cuerdas[0].cuerdasMin = 0;
    cuerdas[0].combinaciones = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = L; j >= M[i - 1].longitud; j--) {
            cuerdas[j].combinaciones = cuerdas[j].combinaciones + cuerdas[j - M[i - 1].longitud].combinaciones;
            cuerdas[j].cuerdasMin = min(cuerdas[j].cuerdasMin, cuerdas[j - M[i - 1].longitud].cuerdasMin + 1);
            cuerdas[j].costeMin = min(cuerdas[j].costeMin, cuerdas[j - M[i - 1].longitud].costeMin + M[i - 1].precio);
        }
    }

    return cuerdas[L];
}

bool resuelveCaso() {

    int numCuerdas, longObjetivo;

    cin >> numCuerdas >> longObjetivo;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<cuerda> cuerdas(numCuerdas);

    for (int i = 0; i < numCuerdas; i++) {
        cin >> cuerdas[i].longitud;
        cin >> cuerdas[i].precio;
    }

    nodo sol = cuerda_cometa(cuerdas, longObjetivo);

    if (sol.combinaciones == 0)
        cout << "NO\n";
    else {
        cout << "SI ";
        cout << sol.combinaciones << " " << sol.cuerdasMin << " " << sol.costeMin << "\n";
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
