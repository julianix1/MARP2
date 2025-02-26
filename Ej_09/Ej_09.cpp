// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

EntInf minCosteCorte(const vector<int> &cortes) {
    int n = cortes.size();
    Matriz<EntInf> matriz(n + 1, n + 1, 0);

    for (int d = 2; d <= n - 1; d++) {
        for (int i = 1; i <= n - d; i++) {
            int j = i + d;
            matriz[i][j] = Infinito;
            for (int k = i+1; k < j;k++) {
                EntInf temp = matriz[i][k] + matriz[k][j] + (cortes[j-1]-cortes[i-1])*2;
                if (matriz[i][j] > temp)
                    matriz[i][j] = temp;
            }
        }
    }

    return matriz[1][n];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int longitud, numCortes;

    cin >> longitud >> numCortes;

    if (longitud == 0 && numCortes == 0)
        return false;

    vector<int> cortes(numCortes + 2);
    cortes[0] = 0;
    cortes[numCortes + 1] = longitud;
    for (int i = 1; i < numCortes + 1; i++) {
        cin >> cortes[i];
    }

    EntInf sol = minCosteCorte(cortes);

    cout << sol << endl;

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
