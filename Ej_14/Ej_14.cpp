// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;


void resolver(vector<bool>& marcado, int numTareas, int tareaActual, const vector<vector<int>>& empleados, int coste, int& minimo) {
    if (tareaActual == numTareas) {
        minimo = min(minimo,coste);
    }
    else if(coste < minimo) {
        for (int i = 0; i < empleados.size(); i++) {
            if (!marcado[i]) {
                marcado[i] = true;
                resolver(marcado, numTareas, tareaActual + 1, empleados, coste+empleados[i][tareaActual], minimo);
                marcado[i] = false;
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int n;

    cin >> n;

    if (n==0)
        return false;

    vector<vector<int>> empleados(n);
    vector<bool> marcado(n, false);

    for (int i = 0; i < n; i++) {
        vector<int> empleado(n);
        for (int j = 0; j < n;j++) {
            cin >> empleado[j];
        }
        empleados[i] = empleado;
    }

    int min = INT_MAX;

    resolver(marcado,n,0,empleados,0,min);

    cout << min << "\n";

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
