
// Nombre y Apellidos

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

EntInf recursion(Matriz<EntInf>& mat, int i, int j, const string& cadena) {
    EntInf res = mat[i][j];
    if (res == Infinito) {
        if (i >= j) res = 0;
        else if (cadena[i] == cadena[j]) {
            res = recursion(mat, i + 1, j - 1, cadena);
        }
        else {
            res = min(recursion(mat, i + 1, j, cadena) + 1, recursion(mat, i, j - 1, cadena) + 1);
        }
        mat[i][j] = res;
    }

    return res;
}

void reconstruir(string const& orig, Matriz<EntInf> const& palabra,
    int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(orig[i]);
    else if (orig[i] == orig[j]) {
        sol.push_back(orig[i]);
        reconstruir(orig, palabra, i + 1, j - 1, sol);
        sol.push_back(orig[j]);
    }
    else if (palabra[i][j] == palabra[i + 1][j] + 1) {
        sol.push_back(orig[i]);
        reconstruir(orig, palabra, i + 1, j, sol);
        sol.push_back(orig[i]);
    }
    else {
        sol.push_back(orig[j]);
        reconstruir(orig, palabra, i, j - 1, sol);
        sol.push_back(orig[j]);
    }
}

EntInf resolver(string const& palabra, string& res) {
    const int M = palabra.size();
    Matriz<EntInf> mat(M, M, Infinito);
    EntInf resultado = recursion(mat, 0, M - 1, palabra);
    reconstruir(palabra, mat, 0, M - 1, res);

    return resultado;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    string entrada, salida;
    cin >> entrada;

    if (!std::cin)  // fin de la entrada
        return false;

    EntInf sol = resolver(entrada, salida);

    if (sol == Infinito) cout << "sin solucion\n";
    else cout << sol << " " << salida << "\n";

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