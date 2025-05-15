#include <iostream>
#include <vector>

using namespace std;

long INF = 1e9;
int N, M;
vector<vector<pair<int, int>>> G; //(dest, peso)
vector<int> DISTANCIAS;
vector<int> VISITADOS;

int minDist(vector<int> &visitados, vector<int> &distancias) {
    int res = -1;
    for (int i = 0; i < G.size(); i++) {
        if (!visitados[i] && (res == -1 || distancias[i] < distancias[res])) {
            res = i;
        }
    }
    return res;
}

void dijkstra(int src) {
    //Asi nomas, n^2
    VISITADOS = vector<int>(G.size(), false);
    DISTANCIAS = vector<int>(G.size(), INF);
    DISTANCIAS[src] = 0;
    int next = src;
    while (next < INF && next >= 0) {
        VISITADOS[next] = true;
        for (pair<int, int> arista : G[next]) {
            DISTANCIAS[arista.first] = min(DISTANCIAS[arista.first], DISTANCIAS[next] + arista.second);
        }
        next = minDist(VISITADOS, DISTANCIAS);
    }
}

//IDEA: Tengo un grafo donde las celdas son los nodos. Cada una aparece 4 veces, representando
//la cantidad de veces que se tomo un tunel. Hay aristas de peso 1 que van de una celda a la siguiente
//en el mismo nivel que representan avanzar normalmente. Despues, hay aristas de peso 2 que van
//a una celda mas avanzada en el proximo nivel que representan tomar un tunel. Luego de tomar
//3 tuneles, no quedan mas niveles y solo se puede avanzar normalmente. Hay 2 nodos extra.
//Uno representa el lugar donde empieza Pablo y esta conectado con una arista de peso 1
//a la primera celda del primer nivel. El otro ata a la ultima celda de cada nivel con peso 0
//para que se pueda terminar habiendo tomado cualquier cantidad de tuneles.

void salvataje() {
    dijkstra(0);
    cout << DISTANCIAS[G.size()-1] << endl;
}

int main() {
    int c;
    cin >> c;
    while (c > 0) {
        cin >> N >> M;
        //0 es s, (n*4)+1 es t
        G = vector<vector<pair<int, int>>>(N*4 + 2, vector<pair<int, int>>());
        G[0].push_back({1, 1});
        for (int i = 1; i < 5; i++) {
            G[N*i].push_back({N*4 + 1, 0});
        }
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < 4; j++) {
                G[i + N*j].push_back({i+1 + N*j, 1});
            }
        }
        for (int i = 0; i < M; i++) {
            int v, w;
            cin >> v >> w;
            for (int j = 0; j < 3; j++) {
                G[v + N*j].push_back({w + N*(j+1), 2});
            }
        }
        salvataje();
        c--;
    }
    return 0;
}