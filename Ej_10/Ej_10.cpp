// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

typedef struct pelicula {
    int inicio;
    int duracion;
};

bool operator<(const pelicula& p1, const pelicula& p2) {
    return p1.inicio < p2.inicio;
}

int resolver(const vector<pelicula>& peliculas,vector<int> &sol) {
    int n = peliculas.size();
    sol = vector<int>(n+1);
    sol[n] = 0;

    for (int i = n-1; i >= 0; i--) {
        int horasCogiendo = peliculas[i].duracion;
        int fin = peliculas[i].inicio + peliculas[i].duracion +10;
        int j = i+1;

        while (j < n && peliculas[j].inicio < fin) {
            j++;
        }

        horasCogiendo += sol[j];
        sol[i] = max(horasCogiendo, sol[i+1]);
    }

    return sol[0];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int numPelis;
    

    cin >> numPelis;

    if (numPelis == 0)
        return false;

    vector<pelicula> peliculas(numPelis);
    vector<int> solucion;

    for (int i = 0; i < numPelis;i++) {
        char basura;
        int aux;
        cin >> aux;
        peliculas[i].inicio = aux * 60;
        cin >> basura;
        cin >> aux;
        peliculas[i].inicio += aux;
        cin >> peliculas[i].duracion;
    }

    sort(peliculas.begin(), peliculas.end());

    int sol = resolver(peliculas,solucion);

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
