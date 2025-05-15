
#ifndef TP3_ALGO2LANDIA_SIMULACION_H
#define TP3_ALGO2LANDIA_SIMULACION_H

#include "Mapa.h"
#include "Objetivo.h"
#include <iterator>

class Simulacion {

public:
    Simulacion();

    Simulacion(const Mapa& mapa, Coordenada posicion, const diccTrie<Coordenada>& objetos);

    void mover(Direccion);

    void agregarObjetivo(Objetivo);

    const Mapa& mapa() const;

    Coordenada posicionJugador() const;

    int cantMovimientos() const;

    set<Objetivo> objetivosDisponibles() const;

    int cantObjetivosRealizados() const;

    list<Color> coloresObjetos() const;

    Coordenada posicionObjeto(const Color&) const;

    bool hayObjeto(const Coordenada& pos) const;

private:
    Mapa _mapa;

    diccTrie<Coordenada> _objetos;
    vector<vector<Color>> _colorPorPos;

    diccTrie<diccTrie<set<Objetivo>::iterator>> _diccObjetivos;
    set<Objetivo> _objetivosDisponibles;

    Coordenada _posAgente;

    int _cantObjetivosCumplidos;
    int _cantMovimientos;
};

Coordenada siguientePosicion(Coordenada, Direccion);

bool esPosicionValida(const Mapa &mapa, Coordenada c);

#endif //TP3_ALGO2LANDIA_SIMULACION_H
