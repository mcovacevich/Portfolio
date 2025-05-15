#include "aed2_mapa.h"

aed2_Mapa::aed2_Mapa() : _mapa() {}

aed2_Mapa::aed2_Mapa(Nat ancho, Nat alto, const set<Coordenada>& elevaciones, const map<Color, Coordenada>& receptaculos) {
    diccTrie<Coordenada> _receptaculos;

    for (const auto& tupla : receptaculos) {
        _receptaculos.insert(tupla.first, tupla.second);
    }

    _mapa = Mapa(ancho, alto, _receptaculos);

    for (auto coordenada : elevaciones) {
        _mapa.agregarPared(coordenada);
    }
}

void aed2_Mapa::agregarRampa(Coordenada c) {
    _mapa.agregarRampa(c);
}

Nat aed2_Mapa::ancho() const {
    return _mapa.ancho();
}

Nat aed2_Mapa::alto() const {
    return _mapa.alto();
}

TipoCasillero aed2_Mapa::tipoCasillero(Coordenada c) const {
    return _mapa.tipoCasillero(c);
}

map<Color, Coordenada> aed2_Mapa::receptaculos() const {
    map<Color, Coordenada> _receptaculos;

    for (const auto& color : _mapa.receptaculos().keys()) {
        _receptaculos[color] = _mapa.receptaculos().at(color);
    }

    return _receptaculos;
}

Coordenada aed2_Mapa::receptaculo(const Color& color){
    return _mapa.receptaculos().at(color);
}

// Esta función sirve para convertir del Mapa implementado por ustedes
// a la clase Mapa de la cátedra
aed2_Mapa::aed2_Mapa(Mapa m){
    _mapa = Mapa(m.ancho(), m.alto(), m.receptaculos());

    for (int x = 0; x < m.ancho(); x++) {
        for (int y = 0; y < m.alto(); y++) {
            Coordenada c(x, y);
            if (m.esPared(c)) {
                _mapa.agregarPared(c);
            }
            else if (m.esRampa(c)) {
                _mapa.agregarRampa(c);
            }
        }
    }
}

// Esta función sirve para convertir del Mapa de la cátedra (aed2_Mapa)
// a la clase Mapa definida por ustedes
Mapa aed2_Mapa::mapa() const {
    return _mapa;
}



