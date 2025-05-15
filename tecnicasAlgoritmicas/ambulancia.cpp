#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> tab;
vector<list<pair<int, int>>> G;
int h; // nodo hospital
int p; // nodo paciente
vector<bool> visitados;
vector<int> distancia;

void mostrarAristas(){
    for(int u = 0; u < G.size(); u++){
        for(pair<int, int> v : G[u]){
            cout << u << "," << v.first << "," << v.second << " ";
        }
    }
    cout << endl;
}

void resetBFS(){
    fill(visitados.begin(), visitados.end(), false);
    fill(distancia.begin(), distancia.end(), -1);
}

void bfs(int raiz, int tiempo_ini, int destino){
    visitados[raiz] = true;
    distancia[raiz] = 0;

    queue<int> q;
    q.push(raiz);

    while(!q.empty()){
        int v = q.front(); q.pop();
        for (auto u : G[v]){
            if(!visitados[u.first]){
                if(tiempo_ini + distancia[v] + 1 < u.second || u.second == 0){
                    visitados[u.first] = true;
                    distancia[u.first] = distancia[v] + 1;
                    q.push(u.first);
                    if(u.first == destino)
                        return;
                }
            }
        }
    }
}


bool enRango(int i, int j){
    return i >= 0 && i < N && j >= 0 && j < M;
}

//los nodos van del 0 al (M*N) - 1
void armarGrafo(pair<int, int> hospital, pair<int, int> paciente){
    int nodo = -1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            nodo++;
            if(enRango(i-1, j))
                G[nodo].push_back({nodo - M, tab[i-1][j]});      

            if(enRango(i+1, j))
                G[nodo].push_back({nodo + M, tab[i+1][j]});     

            if(enRango(i, j-1))
                G[nodo].push_back({nodo - 1, tab[i][j-1]}); 

            if(enRango(i, j+1))
                G[nodo].push_back({nodo + 1, tab[i][j+1]});

        }
    }
}

void ambulancia(pair<int, int> hospital, pair<int, int> paciente){
    h = hospital.first*M + hospital.second;
    p = paciente.first*M + paciente.second;

    armarGrafo(hospital, paciente);

    bfs(h, 0, p);

    int dist_p = distancia[p];
    if(dist_p == -1){
        cout << "IMPOSIBLE" << endl;
    } else {
        resetBFS();
        bfs(p, dist_p, h);

        int dist_h = distancia[h];
        if(dist_h == -1){
            cout << "IMPOSIBLE" << endl;
        } else {
            cout << dist_p << " " << dist_p + dist_h << endl;
        }
    }
}


int main(){
    int c;
    cin >> c;

    for(int k = 0; k < c; k++){
        cin >> N >> M;
        tab = vector<vector<int>>(N, vector<int>(M));
        G = vector<list<pair<int, int>>>(N*M, list<pair<int, int>>());
        visitados = vector<bool>(N*M, false);
        distancia = vector<int>(N*M, -1);

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                cin >> tab[i][j];
            }
        }

        pair<int, int> hospital;
        pair<int, int> paciente;
        cin >> hospital.first >> hospital.second >> paciente.first >> paciente.second;


        ambulancia(hospital, paciente);
    }
    return 0;
}
