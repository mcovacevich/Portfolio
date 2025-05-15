#include "Simulacion.h"

#include <utility>

Simulacion::Simulacion() :
        _mapa(), _objetos(), _colorPorPos(),
        _diccObjetivos(), _objetivosDisponibles(),
        _posAgente(make_pair(0,0)),
        _cantObjetivosCumplidos(0), _cantMovimientos(0) {}

Simulacion::Simulacion(const Mapa& mapa, Coordenada posicion, const diccTrie<Coordenada>& objetos) :
        _mapa(mapa), _objetos(objetos), _colorPorPos(mapa.ancho(),vector<Color>(mapa.alto(),"")),
        _diccObjetivos(), _objetivosDisponibles(),
        _posAgente(posicion),
        _cantObjetivosCumplidos(0), _cantMovimientos(0)
{
    for (const Color& o : _objetos.keys()){
        Coordenada pos = _objetos.at(o);
        _colorPorPos[pos.first][pos.second] = o;
    }
}

/**
 * Ejecuta un movimiento del agente
 * @param d
 */
void Simulacion::mover(const Direccion d) {
    Coordenada sigPos = siguientePosicion(_posAgente, d);
    // ¿la posición destino es válida?
    if (esPosicionValida(_mapa, sigPos)) {
        // ¿puede moverse a través del relieve?
        if (!(_mapa.esPared(sigPos) && _mapa.esPiso(_posAgente))) {
            // ¿hay objeto?
            if (!hayObjeto(sigPos)) {
                _posAgente = sigPos;
            } else {
                Coordenada sigDeSig = siguientePosicion(sigPos, d);
                // ¿la posición destino para el objeto es válida?
                if (esPosicionValida(_mapa, sigDeSig)) {
                    // ¿puede moverse a través del relieve?
                    if (!hayObjeto(sigDeSig) && !(_mapa.esPared(sigDeSig) && _mapa.esPiso(sigPos))) {
                        // Movemos al agente
                        _posAgente = sigPos;
                        // Movemos el objeto
                        Color objeto = _colorPorPos[sigPos.first][sigPos.second];
                        _colorPorPos[sigPos.first][sigPos.second] = "";
                        _colorPorPos[sigDeSig.first][sigDeSig.second] = objeto;
                        _objetos.at(objeto) = sigDeSig;
                        // ¿hay un receptáculo en la posición destino?
                        Color receptaculo = _mapa.receptaculosPorPos()[sigDeSig.first][sigDeSig.second];
                        if (!receptaculo.empty()) {
                            // Si hay un objetivo pendiente
                            if (_diccObjetivos.count(objeto) == 1 && _diccObjetivos.at(objeto).count(receptaculo) == 1) {
                                // Eliminamos el objetivo
                                auto itObjetivo = _diccObjetivos.at(objeto).at(receptaculo);
                                _diccObjetivos.at(objeto).erase(receptaculo);
                                if (_diccObjetivos.at(objeto).empty()){
                                    _diccObjetivos.erase(objeto);
                                }
                                _objetivosDisponibles.erase(itObjetivo);
                                // Incrementamos objetivos cumplidos
                                _cantObjetivosCumplidos++;
                            }
                        }
                    }
                }
            }
        }
        _cantMovimientos++;
    }
}

/**
 * Agrega un objetivo a la simulación.
 * Complejidad log(n) + |c| en la cantidad de objetivos y el tamaño de los strings
 * @param obj es copiado, no hay aliasing.
 */
void Simulacion::agregarObjetivo(Objetivo obj) {
    if (posicionObjeto(obj.objeto()) == mapa().receptaculos().at(obj.receptaculo())){
        _cantObjetivosCumplidos++;
    } else {
        set<Objetivo>::iterator itConj;
        itConj = _objetivosDisponibles.insert(obj).first;
        _diccObjetivos[obj.objeto()][obj.receptaculo()] = itConj;
    }
}

const Mapa& Simulacion::mapa() const {
    return _mapa;
}

Coordenada Simulacion::posicionJugador() const {
    return _posAgente;
}

int Simulacion::cantMovimientos() const {
    return _cantMovimientos;
}

set<Objetivo> Simulacion::objetivosDisponibles() const {
    return _objetivosDisponibles;
}

int Simulacion::cantObjetivosRealizados() const {
    return _cantObjetivosCumplidos;
}

list<Color> Simulacion::coloresObjetos() const {
    return _objetos.keys();
}

Coordenada Simulacion::posicionObjeto(const Color& objeto) const {
    return _objetos.at(objeto);
}

bool Simulacion::hayObjeto(const Coordenada& pos) const {
    return !_colorPorPos[pos.first][pos.second].empty();
}

Coordenada siguientePosicion(Coordenada c, Direccion d) {
    if (d == ARRIBA)
        return make_pair(c.first , c.second + 1);
    if (d == ABAJO)
        return make_pair(c.first, c.second - 1);
    if (d == DERECHA)
        return make_pair(c.first + 1, c.second);
    if (d == IZQUIERDA)
        return make_pair(c.first - 1, c.second);

    // No deberíamos llegar acá
    assert(false);
}

/**
 * Retorna true sii la posición se encuentra en el rango del mapa
 * todo: Esto podría ser un método de la clase Mapa
 */
bool esPosicionValida(const Mapa &mapa, Coordenada c) {
    return (0 <= c.first && c.first < mapa.ancho()) && (0 <= c.second && c.second < mapa.alto());
}
