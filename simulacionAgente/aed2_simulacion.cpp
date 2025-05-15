#include "aed2_simulacion.h"

aed2_Simulacion::aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio) {
    diccTrie<Coordenada> _objetos;

    for (const auto& tupla : objetos) {
        _objetos.insert(tupla.first, tupla.second);
    }

    _sim = Simulacion(mapa.mapa(), inicio, _objetos);
}

void aed2_Simulacion::mover(Direccion d) {
    _sim.mover(d);
}

void aed2_Simulacion::agregarObjetivo(Objetivo obj) {
    _sim.agregarObjetivo(obj);
}

aed2_Mapa aed2_Simulacion::mapa() const {
    return aed2_Mapa(_sim.mapa());
}

map<Color, Coordenada> aed2_Simulacion::posObjetos() const {
    map<Color, Coordenada> _objetos;

    for (const auto& color : _sim.coloresObjetos()) {
        _objetos[color] = _sim.posicionObjeto(color);
    }

    return _objetos;
}

Coordenada aed2_Simulacion::posAgente() const {
    return _sim.posicionJugador();
}

list<Objetivo> aed2_Simulacion::objetivosDisponibles() const {
    list<Objetivo> _objetivosDisponibles;

    for (const auto& objetivo : _sim.objetivosDisponibles()) {
        _objetivosDisponibles.push_back(objetivo);
    }

    return _objetivosDisponibles;
}

Nat aed2_Simulacion::movimientos() const {
    return _sim.cantMovimientos();
}

Nat aed2_Simulacion::objetivosResueltos() const {
    return _sim.cantObjetivosRealizados();
}
