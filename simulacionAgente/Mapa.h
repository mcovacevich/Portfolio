#ifndef TP3_ALGO2LANDIA_MAPA_H
#define TP3_ALGO2LANDIA_MAPA_H

#include "Tipos.h"

class Mapa {
public:
    Mapa();
    Mapa(Nat ancho, Nat alto, const diccTrie<Coordenada>& colores);

    void agregarPared(const Coordenada&);
    void agregarRampa(const Coordenada&);

    const Nat& ancho() const;
    const Nat& alto() const;

    const diccTrie<Coordenada>& receptaculos() const;
    const vector<vector<Color>>& receptaculosPorPos() const;

    bool esPared(const Coordenada&) const;
    bool esRampa(const Coordenada&) const;
    bool esPiso(const Coordenada&) const;

    TipoCasillero tipoCasillero(const Coordenada &) const;

private:
    Nat _ancho;
    Nat _alto;
    diccTrie<Coordenada> _colores;
    vector<vector<TipoCasillero>> _relieve;
    vector<vector<Color>> _receptaculosPorPos;
};

#endif //TP3_ALGO2LANDIA_MAPA_H
