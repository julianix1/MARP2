// Juliann Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "EnterosInf.h"

using namespace std;

struct bombilla {
    int potencia;
    int precio;
};

struct celda {
    EntInf precioMin;
    EntInf potenciaMin;
};

/*
la recursion utilizada es:

funcion: int lucesMasBaratas(i,R); que indica el precio minimo posible usando las i primeras luces donde falta la potencia R para llega a la potencia maxima.

                       | 0 si R <= potenciaMax - potenciaMin
                       | Infinito si i == 0 y R > potenciaMax - potenciaMin
lucesMasBaratas(i,R) = | lucesMasBaratas(i-1,R) si Li > R
                       | min(lucesMasBaratas(i,R-Li.precio) + Li.precio,lucesMasBaratas(i-1,R)) si R > potenciaMAx - potenciaMin
*/

void resolver(vector<bombilla> bombillas, int minPotencia, int maxPotencia, EntInf& costeMin, EntInf& potenciaMin) {
    int n = bombillas.size();
    int M = maxPotencia;

    vector<celda> vec(M + 1, { Infinito,Infinito });
    for (int i = 0; i <= maxPotencia - minPotencia; i++) {
        vec[i] = { 0,maxPotencia - i };
    }

    for (int i = 1; i <= n; i++) {
        for (int j = bombillas[i - 1].potencia; j <= M; j++) {
            if (vec[j - bombillas[i - 1].potencia].precioMin + bombillas[i - 1].precio < vec[j].precioMin) {
                vec[j].precioMin = vec[j - bombillas[i - 1].potencia].precioMin + bombillas[i - 1].precio;
                vec[j].potenciaMin = vec[j - bombillas[i - 1].potencia].potenciaMin;
            }
            else if (vec[j - bombillas[i - 1].potencia].precioMin + bombillas[i - 1].precio == vec[j].precioMin) {
                vec[j].precioMin = vec[j].precioMin;
                vec[j].potenciaMin = min(vec[j].potenciaMin, vec[j - bombillas[i - 1].potencia].potenciaMin);
            }
        }
    }

    potenciaMin = vec[M].potenciaMin;
    costeMin = vec[M].precioMin;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int num, max, min;

    cin >> num >> max >> min;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<bombilla> bombillas(num);

    for (int i = 0; i < num; i++) {
        cin >> bombillas[i].potencia;
    }

    for (int i = 0; i < num; i++) {
        cin >> bombillas[i].precio;
    }

    EntInf costeMin, potenciaMin;
    resolver(bombillas, min, max, costeMin, potenciaMin);

    if (costeMin == Infinito)
        cout << "IMPOSIBLE\n";
    else
        cout << costeMin << " " << potenciaMin << "\n";

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
