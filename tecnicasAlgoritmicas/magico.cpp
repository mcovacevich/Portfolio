#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N;
vector<vector<int>> sumas;
int magic;


void ag_values(vector<vector<int>> &tab, int i, int j, int k){
    sumas[0][i] += k;
    sumas[1][j] += k;
    if(i == j) sumas[2][0] += k;
    if(i + j == tab.size()-1) sumas[3][0] += k;
}

void er_values(vector<vector<int>> &tab, int i, int j, int k){
    sumas[0][i] -= k;
    sumas[1][j] -= k;
    if(i == j) sumas[2][0] -= k;
    if(i + j == tab.size()-1) sumas[3][0] -= k;
}

bool sumanMagico(vector<vector<int>> &tab, int magic){

        int sumaDiag = 0;
        int sumaAnti = 0;

        for(int i = 0; i < tab.size(); i++){
        int sumaF = 0;
        int sumaC = 0;

        sumaDiag += tab[i][i]; 
        sumaAnti += tab[tab.size()-1 - i][i];        

        for(int j = 0; j < tab[0].size(); j++){
            sumaF += tab[i][j];
            sumaC += tab[j][i]; 
        }

        if(sumaF != magic || sumaC != magic) return false; 
    }

    if(sumaDiag != magic || sumaAnti != magic) return false;
    return true;
}

bool esMagico(vector<vector<int>> &tab){

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < tab.size(); j++){
            if(sumas[i][j] != magic) return false;
        }
    }
    if(sumas[2][0] != magic) return false;
    if(sumas[3][0] != magic) return false;
    
    return true;

}

bool supera(vector<vector<int>> &tab, int i, int j){

    return (sumas[0][i] > magic || sumas[1][j] > magic || sumas[2][0] > magic || sumas[3][0] > magic);

}

set<int> valor_posible(vector<vector<int>> &tab, int i, int j){
    set<int> valores;
    for(vector<int> fila : tab){
        for(int valor : fila){
            valores.insert(valor);
        }
    }

    set<int> res;
    for(int k = 1; k <= N*N; k++){
        if(!valores.count(k)){
            ag_values(tab,i, j, k);
            if(!supera(tab, i, j)){
            res.insert(k);
            er_values(tab,i, j, k);
            }else{
                er_values(tab, i, j, k);
                return res;
            }
        }
    }

    return res;
}

int magico(vector<vector<int>> &tab, int i, int j){
    if(i == N) {
        if(esMagico(tab)){
            cout << "encontre uno: " << endl;
            for(int k = 0; k < N; k++){
                for(int l = 0; l < N; l++){
                    cout << tab[k][l] << " ";
                }
            cout << endl << "-" << endl;
            }
            return 1;
        } else {
            return 0;
        } 

    }

    int sig_j = j == tab.size() - 1 ? 0 : j+1;
    int sig_i = sig_j == 0 ? i + 1 : i;
    
    int suma = 0;
    
    for(int k : valor_posible(tab, i, j)){
        tab[i][j] = k;
        ag_values(tab,i, j, k);
        suma += magico(tab, sig_i, sig_j);
        tab[i][j] = 0;
        er_values(tab,i, j, k); 
    }

    return suma;
}

int main(){

    cin >> N;
    vector<vector<int>> tab;
    vector<int> suma(N,0);
    tab.resize(N, vector<int>(N));
    cout << "N es: " << N << endl;
    for(int i = 0; i < 4; i++){
        sumas.push_back(suma);
    }
    magic = (N*N*N + N)/2;
    int cantidad = 0;
    cantidad = magico(tab,0,0);
    cout << cantidad << endl;

    return 0;
}