#include "string_map.h"

template <typename T>
string_map<T>::string_map() : _raiz(new Nodo()), _size(0) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.
    *this = aCopiar;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& aCopiar) {
    if (this == &aCopiar) {
        return *this;
    }

    clear();

    for (string key : aCopiar.keys()) {
        insert(key, aCopiar.at(key));
    }

    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    clear();
    delete _raiz;
    _raiz = nullptr;
}

template <typename T>
T& string_map<T>::operator[](const string& key){
    if (count(key) == 0) {
        insert(key, T());
    }
    return at(key);
}

template<typename T>
void string_map<T>::insert(const string &key, T definicion) {
    bool existe = true;

    // Buscamos nodo (o creamos al vuelo)
    Nodo* nodo = _raiz;
    for (char c : key) {
        int i = int(c);
        if (nodo->siguientes[i] == nullptr) {
            nodo->siguientes[i] = new Nodo();
            existe = false;
        }
        nodo = nodo->siguientes[i];
    }

    existe &= (nodo->definicion != nullptr);

    if (existe) {
        *(nodo->definicion) = definicion; // Copia
    }
    else {
        nodo->definicion = new T(definicion); // Crea y copia
        _size += 1;
        _keys.push_back(key);
        nodo->it = prev(_keys.end());
    }
}

template <typename T>
int string_map<T>::count(const string& key) const{
    bool existe = true;

    // Buscamos nodo
    Nodo* nodo = _raiz;
    for (char c : key) {
        int i = int(c);
        if (nodo->siguientes[i] == nullptr) {
            existe = false;
            break;
        }
        nodo = nodo->siguientes[i];
    }

    existe &= (nodo->definicion != nullptr);

    return existe ? 1 : 0;
}

template <typename T>
const T& string_map<T>::at(const string& key) const {
    assert(count(key) > 0);

    // Buscamos nodo
    Nodo* nodo = _raiz;
    for (char c : key) {
        int i = int(c);
        nodo = nodo->siguientes[i];
    }

    return *(nodo->definicion);
}

template <typename T>
T& string_map<T>::at(const string& key) {
    assert(count(key) > 0);

    // Buscamos nodo
    Nodo* nodo = _raiz;
    for (char c : key) {
        int i = int(c);
        nodo = nodo->siguientes[i];
    }

    return *(nodo->definicion);
}

template <typename T>
void string_map<T>::erase(const string& key) {
    assert(count(key) > 0);

    // Buscamos nodo y cola para eliminar
    Nodo* nodo = _raiz;
    Nodo* tail = nullptr;
    int l = 1;
    for (char c : key) {
        int i = int(c);
        nodo = nodo->siguientes[i];

        if (tail == nullptr) {
            if ((l < key.size() && nodo->definicion == nullptr && nodo->ramas() == 1) || (l == key.size() && nodo->ramas() == 0)) {
                tail = nodo;
            }
        }
        else {
            if ((l < key.size() && (nodo->definicion != nullptr || nodo->ramas() > 1)) || (l == key.size() && nodo->ramas() > 0)) {
                tail = nullptr;
            }
        }

        l++;
    }

    // Eliminamos referencia a la definicion
    delete nodo->definicion;
    nodo->definicion = nullptr;

    // Eliminar clave en keys
    _keys.erase(nodo->it);

    if (tail != nullptr) {
        // Eliminamos referencia a la cola
        nodo = _raiz;
        for (char c : key) {
            int i = int(c);

            if (nodo->siguientes[i] == tail) {
                nodo->siguientes[i] = nullptr;
                break;
            }

            nodo = nodo->siguientes[i];
        }

        // Eliminamos cola
        nodo = tail;
        while (nodo != nullptr) {
            Nodo* temp = nodo;

            int i = 0;
            while (i < nodo->siguientes.size() && nodo->siguientes[i] == nullptr) {
                i++;
            }

            if (i < nodo->siguientes.size()) {
                nodo = nodo->siguientes[i];
            }
            else {
                nodo = nullptr;
            }

            delete temp;
        }
    }

    _size -= 1;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}

template<typename T>
const list<string>& string_map<T>::keys() const {
    return _keys;
}

template<typename T>
void string_map<T>::clear() {
    while (!_keys.empty()) {
        string key = _keys.front();
        erase(key);
    }
}

template<typename T>
int string_map<T>::Nodo::ramas() const {
    int c = 0;
    for (int i = 0; i < siguientes.size(); i++) {
        c += (siguientes[i] != nullptr) ? 1 : 0;
    }
    return c;
}
