//Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include "Matriz.h"

using namespace std;

int recursion(Matriz<int>& mat, int i, int j, const string& cadena1, const string& cadena2) {
    int res = mat[i][j];
    if (res == -1) {
        if (i >= cadena1.size() || j >= cadena2.size()) res = 0;
        else if (cadena1[i] == cadena2[j]) {
            res = recursion(mat, i + 1, j + 1, cadena1, cadena2) + 1;
        }
        else {
            res = max(recursion(mat, i + 1, j, cadena1, cadena2), recursion(mat, i, j + 1, cadena1, cadena2));
        }
        mat[i][j] = res;
    }

    return res;
}

void reconstruir(const Matriz<int>& mat, int i, int j, const string& palabra1, const string& palabra2,string& reconstruccion) {
    if (mat[i][j] == 0) return;
    else if (palabra1[i] == palabra2[j]) {
        reconstruccion.push_back(palabra1[i]);
        reconstruir(mat, i+1, j+1, palabra1, palabra2, reconstruccion);
    }
    else {
        if (mat[i + 1][j] > mat[i][j + 1]) reconstruir(mat, i+1,j,palabra1, palabra2, reconstruccion);
        else reconstruir(mat, i , j + 1, palabra1, palabra2, reconstruccion);
    }
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    string palabra1, palabra2, reconstruccion;

    cin >> palabra1 >> palabra2;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> mat(palabra1.size() + 1, palabra2.size() + 1, -1);

    int sol = recursion(mat,0,0,palabra1,palabra2);
    reconstruir(mat, 0, 0, palabra1, palabra2, reconstruccion);
    cout << reconstruccion << "\n";

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
