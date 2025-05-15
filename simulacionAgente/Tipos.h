#ifndef TIPOS_H
#define TIPOS_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "string_map.h"

using namespace std;

using Nat = unsigned int;

using Coordenada = pair<Nat, Nat>;

using Color = string;

// Renombro string_map del taller 4 a diccTrie usado en TP
template<typename T>
using diccTrie = string_map<T>;

enum Direccion {
    ARRIBA, ABAJO, IZQUIERDA, DERECHA
};

enum TipoCasillero {
    PISO, RAMPA, ELEVACION
};

#endif // TIPOS_H
