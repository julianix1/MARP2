// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int resolver2(vector<int>& marcado, const vector<vector<int>>& precios) {
    if (productoActual == numProductos) {
        costeMin = min(costeMin, costeActual);
    }
    else {
        for (int i = 0; i < precios.size(); i++) {
            int coste;
            if (marcado[i] != 0 && (coste = costeActual + precios[i][productoActual]) < costeMin) {
                marcado[i]--;
                resolver(marcado, precios, productoActual + 1, numProductos, coste, costeMin);
                marcado[i]++;
            }
        }
    }
}

//Marcado indica cuantas cosas se pueden comprar en ese supermercado.
void resolver(vector<int>& marcado,const vector<vector<int>>& precios, int productoActual, int numProductos,int costeActual ,int& costeMin) {
    if (productoActual == numProductos) {
        costeMin = min(costeMin, costeActual);
    }
    else{
        for (int i = 0; i < precios.size();i++) {
            int coste;
            if (marcado[i] != 0 && (coste = costeActual + precios[i][productoActual]) < costeMin) {
                marcado[i]--;
                resolver(marcado,precios, productoActual +1, numProductos,coste,costeMin);
                marcado[i]++;
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int supermercados, numProductos;

    cin >> supermercados >> numProductos;

    vector<vector<int>> productos(supermercados);
    vector<int> marcado(supermercados, 3);

    for (int i = 0; i < supermercados; i++) {
        vector<int> aux(numProductos);
        for (int j = 0; j < numProductos;j++) {
            cin >> aux[j];
        }

        productos[i] = aux;
    }

    int minCoste = INT_MAX;
    resolver(marcado,productos,0,numProductos,0,minCoste);

    cout << minCoste << "\n";
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
