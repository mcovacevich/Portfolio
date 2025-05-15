#include <iostream>
#include <vector>

using namespace std;

int INF = 130;

vector<vector<char>> tablero;
vector<vector<bool>> visitadas;
int c;
int N;
int M;
int menor_long;
int mayor_long;

bool puedoIzq(int i, int j, bool izq){
    return j-1 >= 0 && izq && !visitadas[i][j-1] && tablero[i][j-1] != '#';
}

bool puedoAr(int i, int j, bool ar){ 
    return i-1 >= 0 && ar && !visitadas[i-1][j] && tablero[i-1][j] != '#';
}

bool puedoDer(int i, int j, bool der){
    return j+1 < M && der && !visitadas[i][j+1] && tablero[i][j+1] != '#';
}

bool puedoAb(int i, int j, bool ab){
    return i+1 < N && ab && !visitadas[i+1][j] && tablero[i+1][j] != '#';
}

int sendero(int i, int j, int casillas, bool izq, bool ar, bool der, bool ab){
    if(i == N-1 && j== M-1){
        if(casillas < menor_long) menor_long = casillas;
        if(casillas > mayor_long) mayor_long = casillas;
        return casillas;
    }

    int res = INF;
    visitadas[i][j] = true;

    if(puedoDer(i, j, der)){
        if(tablero[i][j+1] == 'I'){
            res = min(res, sendero(i, j+1, casillas + 1, false, false, true, false));
        } else if(tablero[i][j+1] == 'L'){
            res = min(res, sendero(i, j+1, casillas + 1, false, true, false, true));
        } else{ // '+'
            res = min(res, sendero(i, j+1, casillas + 1, false, true, true, true));
        }
    }

    if(puedoAb(i, j, ab)){
        if(tablero[i+1][j] == 'I'){
            res = min(res, sendero(i+1, j, casillas + 1, false, false, false, true));
        } else if(tablero[i+1][j] == 'L'){
            res = min(res, sendero(i+1, j, casillas + 1, true, false, true, false));
        } else{ // '+'
            res = min(res, sendero(i+1, j, casillas + 1, true, false, true, true));
        }
    }

    if(puedoIzq(i, j, izq)){
        if(tablero[i][j-1] == 'I'){
            res = min(res, sendero(i, j-1, casillas + 1, true, false, false, false));
        } else if(tablero[i][j-1] == 'L'){
            res = min(res, sendero(i, j-1, casillas + 1, false, true, false, true));
        } else{ // '+'
            res = min(res, sendero(i, j-1, casillas + 1, true, true, false, true));
        }
    }

    if(puedoAr(i, j, ar)){
        if(tablero[i-1][j] == 'I'){
            res = min(res, sendero(i-1, j, casillas + 1, false, true, false, false));
        } else if(tablero[i-1][j] == 'L'){
            res = min(res, sendero(i-1, j, casillas + 1, true, false, true, false));
        } else{ // '+'
            res = min(res, sendero(i-1, j, casillas + 1, true, true, true, false));
        }
    }

    visitadas[i][j] = false;

    return res;
}


int main(){
    char pieza;
    cin >> c;
    vector<vector<int>> resultados(c, vector<int>(2,-1));

    for(int k = 0; k < c; k++){
        cin >> N >> M;
        vector<vector<bool>> tmp(N, vector<bool>(M, false));
        visitadas = tmp;
        menor_long = INF;
        mayor_long = -INF;
        tablero.clear();

        for(int i = 0; i < N; i++){
            vector<char> v;
            for(int j = 0; j < M; j++) {
                cin >> pieza;
                v.push_back(pieza);
            }
            tablero.push_back(v);
        }

        int res = sendero(0, 0, 0, false, false, true, true);


        if(menor_long != INF){
            resultados[k][0] = menor_long;
            resultados[k][1] = mayor_long;
        }
    }

    for(int k = 0; k < c; k++){
        if(resultados[k][0] != -1){
            cout << "POSIBLE" << " " << resultados[k][0] << " " << resultados[k][1] << endl;
        } else {
            cout << "IMPOSIBLE" << endl;
        }
    }

    return 0;
}