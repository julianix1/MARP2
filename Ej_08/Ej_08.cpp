//Julián Reguera peñalosa

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

EntInf gradoSeparacion(const Matriz<EntInf>& C) {
    EntInf max = 0;

    for (int i = 0; i < C.numfils(); i++) {
        for (int j = 0; j < C.numcols(); j++) {
            if (C[i][j] > max) max = C[i][j];
        }
    }

    return max;
}

void resolver(int Tam,const Matriz<EntInf> &G, Matriz<EntInf> &C) {
    C = G;

    for (int k = 0; k < Tam; ++k) {
        for (int i = 0; i < Tam; ++i) {
            for (int j = 0; j < i; ++j) {
                EntInf temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    C[j][i] = temp;
                }
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
    unordered_map<string, int> posiciones;
    int numPersonas, numEnlaces;

    cin >> numPersonas >> numEnlaces;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> G(numPersonas,numPersonas, Infinito);
    Matriz<EntInf> C(numPersonas, numPersonas, Infinito);
    vector<string> nombre;

    for (int i = 0; i < numEnlaces; i++) {
        string aux1, aux2;

        cin >> aux1 >> aux2;
        
        if (!posiciones.count(aux1)) {
            posiciones.insert({ aux1,nombre.size()});
            nombre.push_back(aux1);
        }

        if (!posiciones.count(aux2)) {
            posiciones.insert({ aux2,nombre.size() });
            nombre.push_back(aux2);
        }

        int x = posiciones.at(aux1);
        int y = posiciones.at(aux2);

        G[x][y] = 1;
        G[y][x] = 1;
    }

    for (int i = 0; i < numPersonas; i++) {
        G[i][i] = 0;
    }

    resolver(numPersonas,G,C);
    EntInf res = gradoSeparacion(C);

    if (res == Infinito) cout << "DESCONECTADA\n";
    else cout << res << "\n";

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
