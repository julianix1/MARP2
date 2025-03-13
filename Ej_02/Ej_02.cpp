// Julian reguera peñalosa

#include <iostream>
#include <fstream>
#include <vector>

#include "EnterosInf.h"

using namespace std;

//Algoritmo de programación dinamica que recibe las secciones de la diana y la puntuación objetivo
EntInf min_dardos(vector<int> const& secciones, int O, vector<int>& sol) {
    int n = secciones.size();

    vector<EntInf> vec(O + 1, Infinito);
    vec[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = secciones[i - 1]; j <= O; j++) {
            vec[j] = min(vec[j], vec[j - secciones[i - 1]] + 1);
        }
    }

    if (vec[O] != Infinito) {
        int i = n - 1, j = O;

        while (j > 0) {
            if (secciones[i] <= j && vec[j] == vec[j - secciones[i]] + 1) {
                sol.push_back(secciones[i]);
                j = j - secciones[i];
            }
            else {
                i--;
            }
        }
    }

    return vec[O];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int numSecciones, objetivo;

    cin >> objetivo >> numSecciones;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> secciones(numSecciones);
    for (int i = 0; i < numSecciones; i++) {
        cin >> secciones[i];
    }
    vector<int> solOptima;

    EntInf sol = min_dardos(secciones, objetivo, solOptima);

    if (sol == Infinito)
        cout << "Imposible\n";
    else {
        cout << sol << ": ";
        for (int i = 0; i < solOptima.size(); i++) {
            cout << solOptima[i] << " ";
        }
        cout << "\n";
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
