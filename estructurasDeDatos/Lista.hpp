#include "Lista.h"

Lista::Lista() : _long(0), _head(nullptr), _last(nullptr){}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* temp = _head;
    while (temp != nullptr){
        temp = temp->next;
        delete _head;
        _head = temp;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    int longitud = _long;
    for (int i = 0; i < longitud; i++){
        this->eliminar(0);
    }
    for(int i = 0; i < aCopiar._long;i++){
       this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new(Nodo);
    nuevo->data = elem;
    nuevo->previous = nullptr;
    nuevo->next = _head;
    if (_head != nullptr){
        _head->previous = nuevo;
        _head = nuevo;
    } else {
        _head = nuevo;
        _last = nuevo;
    }
    _long++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new(Nodo);
    nuevo->data = elem;
    nuevo->previous = _last;
    nuevo->next = nullptr;
    if (_last != nullptr){
        _last->next = nuevo;
        _last = nuevo;
    } else {
        _head = nuevo;
        _last = nuevo;
    }
    _long++;
}

void Lista::eliminar(Nat i) {
    if (_long == 1){
        delete _head;
        _head = nullptr;
        _last = nullptr;
        _long--;
    } else {
        Nodo* aEliminar = _head;
        for (int j = 1; j <= i; j++) {
            aEliminar = aEliminar->next;
        }
        if (aEliminar == _last) { // es ultimo nodo
            (aEliminar->previous)->next = nullptr;
            _last = aEliminar->previous;
        } else if (aEliminar == _head) { // es primer nodo
            (aEliminar->next)->previous = nullptr;
            _head = aEliminar->next;
               } else { // esta en el medio
            (aEliminar->previous)->next = aEliminar->next;
            (aEliminar->next)->previous = aEliminar->previous;
        }
        _long--;
        delete aEliminar;
    }
}

int Lista::longitud() const {
    return _long;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo *iesimo = _head;
    for (int j = 1; j <= i; j++) {
        iesimo = iesimo->next;
    }
    return iesimo->data;
}

int& Lista::iesimo(Nat i) {
    Nodo* iesimo = _head;
    for (int j = 1; j <= i; j++){
        iesimo = iesimo->next;
    }
    return iesimo->data;
}

void Lista::mostrar(ostream& o) {
    if (_long == 0){
        o << "" << endl;
    } else {
        Nodo *apunta = _head;
        o << apunta->data << endl;
        for (int i = 1; i < _long; i++){
            apunta = apunta->next;
            o << apunta->data << endl;
        }
    }
}
