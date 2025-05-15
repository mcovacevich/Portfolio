#include "principales.h"
#include <algorithm>


bool posicionValida(pair<tablero,int> const &p)
{
    return esJugadorValido(jugador(p)) && esTableroValido(tableroActual(p));
}

bool posicionInicial(posicion const &p)
{
    return piezasEnCoordenadas(p.first) && cantidadPiezasAlInicio(p.first) && jugador(p) == BLANCO;
}

vector<coordenada> casillasAtacadas(posicion const &p, int j)
{
    vector<coordenada> atacadas;
    vector<coordenada> piezas = obtenerPiezas(p, j);
    for(int i = 0; i < piezas.size(); ++i)
    {
        coordenada o = piezas[i];
        vector<coordenada> posibles = obtenerPosiblesDestinos(p.first, o);
        for(int k = 0; k < posibles.size(); ++k)
        {
            coordenada d = posibles[k];
            if(casillaAtacada(p.first, o, d) && cantidadAparicionesVector(d, atacadas) == 0)
            {
                atacadas.push_back(d);
            }
        }
    }
    return atacadas;
}

bool posicionSiguienteCorrecta(posicion const &p1, posicion const &p2, coordenada o, coordenada d)
{
    return posicionSiguiente(p1, p2, o, d);
}

void ordenarTablero(posicion &p)
{
    ordenarFilas(p.first);
}

bool finDeLaPartida(posicion const &p, int &j)
{
    bool empate = esEmpate(p);
    j = empate ? 0 : contrincante(p.second);
    return empate || esJaqueMate(p);
}

bool hayJaqueDescubierto(posicion const &p)
{
    bool res = false;
    vector<coordenada> piezas = obtenerPiezas(p, jugador(p));
    for(int i = 0; i < piezas.size(); ++i)
    {
        coordenada o = piezas[i];
        vector<coordenada> jugadas = jugadasDisponibles(p, o);
        for(int k = 0; k < jugadas.size(); ++k)
        {
            res |= esJaqueDescubierto(p, o, jugadas[k]);
        }
    }
    return res;
}

void ejecutarSecuenciaForzada(posicion &p, secuencia s)
{
    for(int i = 0; i < s.size(); ++i)
    {
        ejecutarMovimiento(p, s[i].first, s[i].second);
        pair<coordenada,coordenada> forzada = jugadaForzada(p);
        ejecutarMovimiento(p, forzada.first, forzada.second);
    }
}

int seVieneElJaqueEn(posicion const &p)
{
    int res = 3, k = 1;
    cuantoParaElMate(p, k, res);
    return res;
}
