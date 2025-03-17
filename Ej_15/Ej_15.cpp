// Juilán Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct carro {
    int anchura;
    vector<int> afinidad;
};

void resolver(vector<bool>& marcado, const vector<carro>& carros, const vector<int>& caminos, int numCaminos, int caminoActual, int afinidadActual, int& afinidadMaxima) {
    if (numCaminos == caminoActual) {
        afinidadMaxima = max(afinidadMaxima, afinidadActual);
    }
    else {
        for (int i = 0; i < carros.size();i++) {
            if (!marcado[i]) {
                marcado[i] = true;
                resolver(marcado, carros, caminos, numCaminos, caminoActual+1, afinidadActual+carros[i].afinidad[caminoActual], afinidadMaxima);
                marcado[i] = false;
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int n, m;

    cin >> n >> m;

    vector<carro> carros(n);
    vector<int> caminos(m);
    vector<bool> marcado(n);

    for (int i = 0; i < n; i++) {
        cin >> carros[i].anchura;
    }

    for (int i = 0; i < m; i++) {
        cin >> caminos[i];
    }

    for (int i = 0; i < n; i++) {
        vector<int> aux(m);
        for (int j = 0; j < m; j++) {
            cin >> aux[j];
        }
        carros[i].afinidad = aux;
    }

    int afinidadMaxima = -1;
    resolver(marcado, carros, caminos, m,0,0,afinidadMaxima);

    cout << afinidadMaxima << "\n";
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}