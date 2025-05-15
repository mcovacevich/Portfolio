#include "string_map.h"

template<class T>
string_map<T>::Nodo::Nodo(): siguientes(256,nullptr), definicion(nullptr), iterador(nullptr){}

template<class T>
string_map<T>::Nodo::Nodo(const T def): siguientes(256,nullptr), definicion(def), iterador(nullptr){}


template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
    list<string> keys;
    claves = keys;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; }

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for(string s : this->claves){
        erase(s);
    }
    for(string s : d.claves){
        T significado = d.at(s);
        this->insert(make_pair(s,significado));
    }
    return *this;

}

template <typename T>
string_map<T>::~string_map() {
    if (raiz != nullptr) {

        for(typename list<string>::iterator it = claves.begin(); it != claves.end(); it++){
                string clave = *it;
                this->eraseV2(clave);
        }
//        for (string s : claves) {
//            erase(s);
//        }
        if (raiz->definicion != nullptr) {
            delete raiz->definicion;
        }
        delete raiz;
    }
}


template <typename T>
T& string_map<T>::operator[](const string& clave){
   
}

template<class T>
void string_map<T>::insert(const pair<string, T>& par){
    if (_size == 0){
        raiz = new Nodo();
    }
    Nodo* actual = raiz;
    int indice = 0;

    while (indice < par.first.size()){
        if(actual->siguientes[int(par.first[indice])] != nullptr) {
            actual = actual->siguientes[int(par.first[indice])];
        } else {
            actual->siguientes[int(par.first[indice])] = new Nodo();
            actual = actual->siguientes[int(par.first[indice])];
        }
        indice++;
    }
    if (actual->definicion == nullptr) {
        T *defino = new T(par.second);
        actual->definicion = defino;
        actual->iterador = claves.insert(claves.end(), par.first);
        _size++;
    } else {
        *(actual->definicion) = par.second;
    }
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if (raiz == nullptr){
        return 0;
    }
    Nodo* actual = raiz;
    int indice = 0;

    while (indice < clave.size()){
        int posicion = int(clave[indice]);
        if (actual->siguientes[posicion] == nullptr){
            return 0;
        } else {
            actual = actual->siguientes[posicion];
        }
        indice++;
    }
    if (actual->definicion != nullptr){
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    int indice = 0;
    Nodo* actual = raiz;
    while(indice < clave.size()){
        int ind = int(clave[indice]);
        actual = actual->siguientes[ind];
        indice++;
    }
    return *actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    int indice = 0;
    Nodo* actual = raiz;
    while(indice < clave.size()){
        int ind = int(clave[indice]);
        actual = actual->siguientes[ind];
        indice++;
    }
    return *actual->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    if (clave == ""){
        delete raiz->definicion;
        raiz->definicion = nullptr;
        claves.erase(raiz->iterador);
    }
    Nodo* ultimoNodo = raiz;
    int ultimoIndice = 0;
    Nodo* actual = raiz;
    int indice = 0;
    while(indice < clave.size()) {
        int hijos = 0;
        for (int i = 0; i < actual->siguientes.size(); i++){
            if (actual->siguientes[i] != nullptr){
                hijos++;
            }
        }
        if (hijos > 1 || actual->definicion != nullptr){
            ultimoNodo = actual;
            ultimoIndice = indice;
        }
        int posicion = int(clave[indice]);
        actual = actual->siguientes[posicion];
        indice++;
    }
    delete actual->definicion;
    actual->definicion = nullptr;
    claves.erase(actual->iterador);

    int hijos = 0;
    for (int i = 0; i < actual->siguientes.size(); i++){
        if (actual->siguientes[i] != nullptr){
            hijos++;
        }
    }
    if (hijos == 0){
        Nodo* siguiente = ultimoNodo->siguientes[int(clave[ultimoIndice])];
        ultimoNodo->siguientes[int(clave[ultimoIndice])] = nullptr;
        ultimoNodo = siguiente;
        ultimoIndice++;

        while (ultimoIndice < clave.size()){
            siguiente = ultimoNodo->siguientes[int(clave[ultimoIndice])];
            delete ultimoNodo->definicion;
            delete ultimoNodo;
            ultimoNodo = siguiente;
            ultimoIndice++;
        }
        delete ultimoNodo;
    }

    _size--;
}

template <typename T>
void string_map<T>::eraseV2(const string& clave) {
    if (clave == ""){
        delete raiz->definicion;
        raiz->definicion = nullptr;
        claves.erase(raiz->iterador);
    }
    Nodo* ultimoNodo = raiz;
    int ultimoIndice = 0;
    Nodo* actual = raiz;
    int indice = 0;
    while(indice < clave.size()) {
        int hijos = 0;
        for (int i = 0; i < actual->siguientes.size(); i++){
            if (actual->siguientes[i] != nullptr){
                hijos++;
            }
        }
        if (hijos > 1 || actual->definicion != nullptr){
            ultimoNodo = actual;
            ultimoIndice = indice;
        }
        int posicion = int(clave[indice]);
        actual = actual->siguientes[posicion];
        indice++;
    }
    delete actual->definicion;
    actual->definicion = nullptr;

    int hijos = 0;
    for (int i = 0; i < actual->siguientes.size(); i++){
        if (actual->siguientes[i] != nullptr){
            hijos++;
        }
    }
    if (hijos == 0){
        Nodo* siguiente = ultimoNodo->siguientes[int(clave[ultimoIndice])];
        ultimoNodo->siguientes[int(clave[ultimoIndice])] = nullptr;
        ultimoNodo = siguiente;
        ultimoIndice++;

        while (ultimoIndice < clave.size()){
            siguiente = ultimoNodo->siguientes[int(clave[ultimoIndice])];
            delete ultimoNodo->definicion;
            delete ultimoNodo;
            ultimoNodo = siguiente;
            ultimoIndice++;
        }
        delete ultimoNodo;
    }

    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}
