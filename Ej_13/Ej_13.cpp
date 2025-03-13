// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

Matriz<EntInf> resolver(Matriz<int> datos) {
    int n = datos.numcols();
    Matriz<EntInf> res(n+1,n+1,Infinito);
    for (int i = 1; i < n ; i++) {
        res[i][i] = 0;
        res[i][i + 1] = datos[i - 1][i];
    }

    res[n][n] = 0;

    for (int d = 2; d < n; d++) {
        for (int i = 1; i <= n-d; i++) {
            int j = d + i;

            res[i][j] = datos[i - 1][j - 1];

            for (int k = i; k < j; k++) {
                res[i][j] = min(res[i][j], res[i][k] + res[k][j]);
            }

            res[j][i] = res[i][j];
        }
    }

    return res;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int n; 

    cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> entrada(n, n);

    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> entrada[i][j];
        }
    }

    Matriz<EntInf> sol = resolver(entrada);

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n;j++) {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }

    // escribir sol

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
