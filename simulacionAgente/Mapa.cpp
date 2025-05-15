#include "Mapa.h"

Mapa::Mapa() : _alto(0), _ancho(0), _colores(), _relieve(), _receptaculosPorPos() {}

Mapa::Mapa(Nat ancho, Nat alto, const diccTrie<Coordenada>& colores) :
        _ancho(ancho), _alto(alto),
        _colores(colores), _receptaculosPorPos(alto, vector<Color>(ancho,"")),
        _relieve(alto, vector<TipoCasillero>(ancho, PISO))
{
    for (const Color& o : _colores.keys()){
        Coordenada pos = _colores.at(o);
        _receptaculosPorPos[pos.first][pos.second] = o;
    }
}

void Mapa::agregarPared(const Coordenada& p) {
    _relieve[p.first][p.second] = ELEVACION;
}

void Mapa::agregarRampa(const Coordenada& p) {
    _relieve[p.first][p.second] = RAMPA;
}

const Nat& Mapa::ancho() const {
    return _ancho;
}

const Nat& Mapa::alto() const {
    return _alto;
}

const diccTrie<Coordenada>& Mapa::receptaculos() const {
    return _colores;
}

const vector<vector<Color>>& Mapa::receptaculosPorPos() const {
    return _receptaculosPorPos;
}

bool Mapa::esPared(const Coordenada& p) const {
    return _relieve[p.first][p.second] == ELEVACION;
}

bool Mapa::esRampa(const Coordenada& p) const {
    return _relieve[p.first][p.second] == RAMPA;
}

bool Mapa::esPiso(const Coordenada& p) const {
    return _relieve[p.first][p.second] == PISO;
}

TipoCasillero Mapa::tipoCasillero(const Coordenada& p) const {
    return _relieve[p.first][p.second];
}
