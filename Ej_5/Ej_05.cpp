// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>

#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

struct tesoro {
    int p; //tiempo de recogida
    int o; //oro
};

EntInf resolver(const vector<tesoro> &tesoros,int oxigen, vector<int> &sol) {
    int n = tesoros.size();
    Matriz<EntInf> mat(n+1,oxigen+1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= oxigen; j++) {
            if (j < tesoros[i - 1].p)
                mat[i][j] = mat[i - 1][j];
            else {
                mat[i][j] = max(mat[i-1][j], mat[i-1][j-tesoros[i-1].p] + tesoros[i-1].o);
            }
        }
    }

    if (mat[n][oxigen] != 0) {
        int i = n, j = oxigen; 
        while (i > 0 && j > 0) {
            if (j >= tesoros[i-1].p && mat[i][j] == mat[i - 1][j - tesoros[i - 1].p] + tesoros[i - 1].o) {
                sol.push_back(i-1);
                j = j - tesoros[i - 1].p;
                i--;
            }
            else
                i--;
        }
    }

    return mat[n][oxigen];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int bombona, numCofres;

    cin >> bombona >> numCofres;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<tesoro> cofres(numCofres);

    for (int i = 0; i < numCofres; i++) {
        int profundidad;
        cin >> profundidad >> cofres[i].o;
        cofres[i].p = 3 * profundidad;
    }
    vector<int> recogidos;
    EntInf sol = resolver(cofres, bombona,recogidos);

    cout << sol << "\n";
    cout << recogidos.size() << "\n";
    for (int i = recogidos.size()-1; i >= 0 ; i--) {
        tesoro aux = cofres[recogidos[i]];
        cout << aux.p / 3 << " " << aux.o << "\n";
    }
    cout << "---\n";


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
