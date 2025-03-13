
// Nombre y Apellidos

#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h"

using namespace std;

void resolver(Matriz<int>& mat, int& sol, int& inicio) {
    int n = mat.numcols();

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int uno = 0, dos = 0, tres = 0;

            uno = (j == 0) ? 0 : mat[i - 1][j - 1];
            dos = mat[i - 1][j];
            tres = (j == n - 1) ? 0 : mat[i - 1][j + 1];

            mat[i][j] = mat[i][j] + max(max(uno, dos), tres);
        }
    }

    sol = -1;
    inicio = -1;

    for (int i = 0; i < n; i++) {
        if (mat[n - 1][i] > sol) {
            sol = mat[n - 1][i];
            inicio = i + 1;
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int tam;
    cin >> tam;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> mat(tam, tam);
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cin >> mat[i][j];
        }
    }

    int sol = 0, pos = 0;

    resolver(mat, sol, pos);

    cout << sol << " " << pos << "\n";

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
