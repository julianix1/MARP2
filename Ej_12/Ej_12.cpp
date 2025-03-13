// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
using namespace std;

int resolver(const vector<int>& cubos) {
    int n = cubos.size();
    Matriz<int> mat(n+1,n+1,0);

    for (int i = 1; i <= n; i++)
        mat[i][i] = cubos[i - 1];

    for (int d = 1; d < n; d++) {
        for (int i = 1; i <= n - d;i++) {
            int j = i + d;
            int derecho, izquierdo;

            if (j - i > 1) {
                if (cubos[i] > cubos[j - 1])
                    derecho = cubos[i - 1] + mat[i + 2][j];
                else derecho = cubos[i - 1] + mat[i + 1][j - 1];
            }
            else
                derecho = cubos[i - 1];

            if (j - i > 1) {
                if (cubos[i-1] > cubos[j-2])
                    izquierdo = cubos[j - 1] + mat[i + 1][j-1];
                else izquierdo = cubos[j - 1] + mat[i][j - 2];
            }
            else
                izquierdo = cubos[j - 1];

            mat[i][j] = max(derecho, izquierdo);
        }
    }

    return mat[1][n];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int n;
    cin >> n;

    if (n == 0)
        return false;

    vector<int> numeros(n);

    for (int i = 0; i < n; i++) {
        cin >> numeros[i];
    }

    int sol = resolver(numeros);

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
