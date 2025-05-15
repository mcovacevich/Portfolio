#include "auxiliares.h"

using namespace std;

vector<pair<int,int>> ordenarVectorPares(vector<pair<int,int>> &v)
{
    sort(v.begin(), v.end());
    return v;
}

coordenada setCoord(int i, int j)
{
    return make_pair(i, j);
}

int jugador(posicion const &p)
{
    return p.second;
}

int contrincante(int j)
{
    return j == BLANCO ? NEGRO : BLANCO;
}

casilla setCasilla(int i, int j)
{
    return make_pair(i, j);
}

tablero tableroActual(posicion const &p)
{
    return p.first;
}

bool esJugadorValido(int const j)
{
    return j == BLANCO || j == NEGRO;
}

bool esTableroValido(const tablero &t)
{
    return esMatriz(t) && casillasValidas(t) && sinPeonesNoCoronados(t) && cantidadValidaDePiezas(t);
}

bool esMatriz(tablero t)
{
    bool res = t.size() == ANCHO_TABLERO;
    for(int i = 0; i < t.size(); ++i)
    {
        res &= t[i].size() == ANCHO_TABLERO;
    }
    return res;
}

bool casillasValidas(tablero t)
{
    bool res = true;
    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t.size(); ++j)
        {
            casilla c = t[i][j];
            int c0 = c.first, c1 = c.second;
            res &= (c == cVACIA || (PEON <= c0 && c0 <= REY && BLANCO <= c1 && c1 <= NEGRO));
        }
    }
    return res;
}

bool sinPeonesNoCoronados(tablero t)
{
    bool res = true;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        int pieza1 = t[0][i].first;
        int pieza2 = t[ANCHO_TABLERO - 1][i].first;
        res &= pieza1 != PEON && pieza2 != PEON;
    }
    return res;
}

bool cantidadValidaDePiezas(const tablero &t)
{
    // Peones
    bool res = aparicionesEnTablero(t, cPEON_B) <= ANCHO_TABLERO;
    res &= aparicionesEnTablero(t, cPEON_N) <= ANCHO_TABLERO;

    // Alfiles
    res &= aparicionesEnTablero(t, cALFIL_B) <= 2;
    res &= aparicionesEnTablero(t, cALFIL_N) <= 2;

    // Torres
    res &= aparicionesEnTablero(t, cTORRE_B) <= 2 + (ANCHO_TABLERO - aparicionesEnTablero(t, cPEON_B));
    res &= aparicionesEnTablero(t, cTORRE_N) <= 2 + (ANCHO_TABLERO - aparicionesEnTablero(t, cPEON_N));

    // Reyes
    res &= aparicionesEnTablero(t, cREY_B) == 1;
    res &= aparicionesEnTablero(t, cREY_N) == 1;

    return res;
}

int aparicionesEnTablero(tablero t, casilla p)
{
    int apariciones = 0;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            apariciones += t[i][j] == p ? 1 : 0;
        }
    }
    return apariciones;
}
int pieza(tablero const &t, coordenada c)
{
    return t[c.first][c.second].first;
}

int color(tablero const &t, coordenada c)
{
    return t[c.first][c.second].second;
}

bool piezaEnCoordenada(tablero const &t, coordenada c, int pza, int col)
{
    return (pieza(t, c) == pza) && (color(t, c) == col);
}

bool piezasEnCoordenadas(tablero const &t)
{
    bool res = true;

    // Peones
    for(int x = 0; x < ANCHO_TABLERO; ++x)
    {
        res &= piezaEnCoordenada(t, setCoord(1, x), PEON, NEGRO);
        res &= piezaEnCoordenada(t, setCoord(6, x), PEON, BLANCO);
    }

    // Alfiles
    res &= piezaEnCoordenada(t, setCoord(0, 2), ALFIL, NEGRO);
    res &= piezaEnCoordenada(t, setCoord(0, ANCHO_TABLERO - 3), ALFIL, NEGRO);
    res &= piezaEnCoordenada(t, setCoord(ANCHO_TABLERO - 1, 2), ALFIL, BLANCO);
    res &= piezaEnCoordenada(t, setCoord(ANCHO_TABLERO - 1, ANCHO_TABLERO - 3), ALFIL, BLANCO);

    // Torres
    res &= piezaEnCoordenada(t, setCoord(0, 0), TORRE, NEGRO);
    res &= piezaEnCoordenada(t, setCoord(0, ANCHO_TABLERO - 1), TORRE, NEGRO);
    res &= piezaEnCoordenada(t, setCoord(ANCHO_TABLERO - 1, 0), TORRE, BLANCO);
    res &= piezaEnCoordenada(t, setCoord(ANCHO_TABLERO - 1, ANCHO_TABLERO - 1), TORRE, BLANCO);

    // Reyes
    res &= piezaEnCoordenada(t, setCoord(0, 4), REY, NEGRO);
    res &= piezaEnCoordenada(t, setCoord(ANCHO_TABLERO - 1, 4), REY, BLANCO);

    return res;
}

bool cantidadPiezasAlInicio(tablero const &t)
{
    bool res = true;
    res = aparicionesEnTablero(t, setCasilla(TORRE, NEGRO)) == 2;
    res &= aparicionesEnTablero(t, setCasilla(TORRE, BLANCO)) == 2;
    res &= aparicionesEnTablero(t, setCasilla(ALFIL, NEGRO)) == 2;
    res &= aparicionesEnTablero(t, setCasilla(ALFIL, BLANCO)) == 2;
    res &= aparicionesEnTablero(t, setCasilla(PEON, NEGRO)) == ANCHO_TABLERO;
    res &= aparicionesEnTablero(t, setCasilla(PEON, BLANCO)) == ANCHO_TABLERO;
    return res;
}

bool casillaVacia(tablero const &t, coordenada c)
{
    return cVACIA == t[c.first][c.second];
}

bool movimientoPiezaValido(tablero const &t, coordenada o, coordenada d)
{
    bool res = false;
    switch(pieza(t, o))
    {
        case PEON:
            res = (d.second == o.second) && ((color(t, o) == BLANCO && d.first == o.first - 1) || (color(t, o) == NEGRO && d.first == o.first + 1));
            break;
        case ALFIL:
            res = abs(d.first - o.first) == abs(d.second - o.second);
            for(int x = 1; x < abs(d.first - o.first); ++x)
            {
                int sgn1 = 1;
                int sgn2 = 1;
                if(d.first - o.first < 0)
                {
                    sgn1 = -1;
                }
                if(d.second - o.second < 0)
                {
                    sgn2 = -1;
                }
                res &= casillaVacia(t, setCoord(o.first + sgn1 * x, o.second + sgn2 * x));
            }
            break;
        case TORRE:
            if(d.second == o.second)
            {
                res = true;
                for(int x = min(o.first, d.first) + 1; x < max(o.first, d.first); ++x)
                {
                    res &= casillaVacia(t, setCoord(x, o.second));
                }
            }
            else if(d.first == o.first)
            {
                res = true;
                for(int y = min(o.second, d.second) + 1; y < max(o.second, d.second); ++y)
                {
                    res &= casillaVacia(t, setCoord(o.first, y));
                }
            }
            break;
        case REY:
            res = (abs(o.first - d.first) == 1 && abs(o.second - d.second) == 1);
            res |= (abs(o.first - d.first) == 1 && abs(o.second - d.second) == 0);
            res |= (abs(o.first - d.first) == 0 && abs(o.second - d.second) == 1);
    }
    return res;
}

bool posicionSiguiente(posicion const &p, posicion const &q, coordenada o, coordenada d)
{
    bool res = posicionesIgualesExceptoEn(p, q, o, d) && casillaVacia(q.first, o);
    res &= (esMovimientoValido(p, o, d) || esCapturaValida(p, o, d));
    res &= piezaCorrectaEnDestino(p, q, o, d);
    return res;
}

bool posicionesIgualesExceptoEn(posicion const &p1, posicion const &p2, coordenada o, coordenada d)
{
    bool res = true;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            casilla c1 = p1.first[i][j];
            casilla c2 = p2.first[i][j];
            if(setCoord(i, j) != o && setCoord(i, j) != d)
            {
                res &= c1 == c2;
            }
        }
    }
    return res;
}

bool esMovimientoValido(const posicion &p, coordenada o, coordenada d)
{
    return jugador(p) == color(p.first, o) && !casillaVacia(p.first, o) &&
           casillaVacia(p.first, d) && movimientoPiezaValido(p.first, o, d);
}

bool esCapturaValida(const posicion &p, coordenada o, coordenada d)
{
    return !casillaVacia(p.first, o) && !casillaVacia(p.first, d) && color(p.first, o) != color(p.first, d) &&
           casillaAtacada(p.first, o, d);
}

int cantidadAparicionesVector(coordenada c, vector<coordenada> v)
{
    int apariciones = 0;
    for(int i = 0; i < v.size(); i++)
    {
        apariciones += v[i] == c ? 1 : 0;
    }
    return apariciones;
}

bool casillaAtacada(const tablero &t, coordenada o, coordenada d)
{
    bool res = !casillaVacia(t, o);
    if(pieza(t, o) != PEON)
        res &= movimientoPiezaValido(t, o, d);
    else
        res &= capturaPeonValida(t, o, d);
    return res;
}

bool capturaPeonValida(const tablero &t, coordenada o, coordenada d)
{
    bool res = abs(d.first - o.first) == 1;
    if(color(t, o) == BLANCO)
    {
        res &= o.first - 1 == d.first;
        res &= d.second == o.second - 1 || d.second == o.second + 1;
    }
    else
    {
        res &= o.first + 1 == d.first;
        res &= d.second == o.second - 1 || d.second == o.second + 1;
    }
    return res;
}

bool piezaCorrectaEnDestino(const posicion &p, const posicion &q, coordenada o, coordenada d)
{
    bool res = color(p.first, o) == color(q.first, d);
    if(enLineaFinalInicial(d) && pieza(p.first, o) == PEON)
        res &= pieza(q.first, d) == TORRE;
    else
        res &= pieza(q.first, d) == pieza(p.first, o);
    return res;
}

bool enLineaFinalInicial(coordenada d)
{
    return d.first == 0 || d.first == ANCHO_TABLERO - 1;
}

void ordenarFilas(tablero &t)
{
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        vector<casilla> piezas;
        vector<int> indices;
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            casilla c = t[i][j];
            if(c != cVACIA)
            {
                piezas.push_back(c);
                indices.push_back(j);
            }
        }
        ordenarVectorPares(piezas);
        for(int k = 0; k < piezas.size(); ++k)
        {
            int j = indices[k];
            t[i][j] = piezas[k];
        }
    }
}

bool esEmpate(const posicion &p)
{
    return soloHayReyes(p.first) || (!jugadorEnJaque(p) && !hayMovimientosLegales(p));
}

bool soloHayReyes(const tablero &t)
{
    int piezasNoReales = 0;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            int pieza = t[i][j].first;
            piezasNoReales += (pieza != REY && pieza != VACIO) ? 1 : 0;
        }
    }
    return piezasNoReales == 0;
}

bool jugadorEnJaque(const posicion &p)
{
    return !cualesAtacanAlRey(p).empty();
}

vector<coordenada> cualesAtacanAlRey(const posicion &p)
{
    vector<coordenada> res;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            coordenada o = setCoord(i, j);
            if(atacaAlRey(p, o) && color(p.first, o) != p.second)
                res.push_back(o);
        }
    }
    return res;
}

coordenada dondeEstaElRey(const tablero &t, int jugador)
{
    casilla rey = setCasilla(4, jugador);
    coordenada coordenadasRey;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            casilla c = t[i][j];
            if(c == rey)
                coordenadasRey = setCoord(i, j);
        }
    }
    return coordenadasRey;
}

bool atacaAlRey(const posicion &p, coordenada o)
{
    coordenada coordenadasRey = dondeEstaElRey(p.first, p.second);
    return esCapturaValida(p, o, coordenadasRey);
}

bool hayMovimientosLegales(const posicion &p)
{
    bool res = false;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            coordenada o = setCoord(i, j);
            if(color(p.first, o) == p.second && !jugadasDisponibles(p, o).empty())
            {
                res = true;
            }
        }
    }
    return res;
}

bool coordenadaEnRango(coordenada c)
{
    return 0 <= c.first && c.first < ANCHO_TABLERO && 0 <= c.second && c.second < ANCHO_TABLERO;
}

bool esJaqueMate(const posicion &p)
{
    return jugadorEnJaque(p) && !existeMovimientoParaSalirDelJaque(p);
}

bool existeMovimientoParaSalirDelJaque(const posicion &p)
{
    bool res = false;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            coordenada o = setCoord(i, j);
            if(jugador(p) == color(p.first, o))
                res |= !jugadasDisponibles(p, o).empty();
        }
    }
    return res;
}

// Dada una pieza en una coordenada o, devuelve las coordenadas a las que puede moverse legalmente
// Se asume que jugador(p) == color(p.first, o)
vector<coordenada> jugadasDisponibles(const posicion &p, coordenada o)
{
    vector<coordenada> jugadasPosibles = obtenerPosiblesDestinos(p.first, o);
    vector<coordenada> res;
    for(int i = 0; i < jugadasPosibles.size(); ++i)
    {
        coordenada d = jugadasPosibles[i];
        if(esJugadaLegal(p, o, d))
            res.push_back(d);
    }
    return res;
}

// Dada una coordenada o con una pieza, devuelve las casillas a las que podría moverse si no hubiese obstáculos
vector<coordenada> obtenerPosiblesDestinos(const tablero &t, coordenada o)
{
    vector<coordenada> res;
    switch(pieza(t, o))
    {
        case PEON:
            for(int i = -1; i <= 1; i += 2)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    coordenada d = setCoord(o.first + i, o.second + j);
                    if(coordenadaEnRango(d) && o != d)
                        res.push_back(d);
                }
            }
            break;
        case ALFIL:
            for(int k = 1; k < ANCHO_TABLERO; ++k)
            {
                for(int i = -1; i <= 1; i += 2)
                {
                    for(int j = -1; j <= 1; j += 2)
                    {
                        coordenada d = setCoord(o.first + i * k, o.second + j * k);
                        if(coordenadaEnRango(d) && o != d)
                            res.push_back(d);
                    }
                }
            }
            break;
        case TORRE:
            for(int i = 0; i < ANCHO_TABLERO; ++i)
            {
                coordenada d = setCoord(o.first, i);
                if(coordenadaEnRango(d) && o != d)
                    res.push_back(d);
                d = setCoord(i, o.second);
                if(coordenadaEnRango(d) && o != d)
                    res.push_back(d);
            }
            break;
        case REY:
            for(int i = -1; i <= 1; ++i)
            {
                for(int j = -1; j <= 1; ++j)
                {
                    coordenada d = setCoord(o.first + i, o.second + j);
                    if(coordenadaEnRango(d) && o != d)
                        res.push_back(d);
                }
            }
    }
    return res;
}

bool esJugadaLegal(const posicion &p, coordenada o, coordenada d)
{
    return (esMovimientoValido(p, o, d) || esCapturaValida(p, o, d)) && !loPoneEnJaque(p, o, d);
}

bool loPoneEnJaque(posicion p, coordenada o, coordenada d)
{
    ejecutarMovimiento(p, o, d);
    cambiarJugador(p);
    return jugadorEnJaque(p);
}

void ejecutarMovimiento(posicion &p, coordenada o, coordenada d)
{
    if(pieza(p.first, o) == PEON && (d.first == 0 || d.first == 7))
    {
        int col = color(p.first, o);
        p.first[o.first][o.second] = cVACIA;
        p.first[d.first][d.second] = make_pair(TORRE, col);
    }
    else
    {
        casilla tmp = obtenerCasilla(p.first, o);
        p.first[o.first][o.second] = cVACIA;
        p.first[d.first][d.second] = tmp;
    }
    cambiarJugador(p);
}

casilla obtenerCasilla(const tablero &t, coordenada o)
{
    return t[o.first][o.second];
}

void cambiarJugador(posicion &p)
{
    p.second = contrincante(jugador(p));
}

bool esJaqueDescubierto(posicion p, coordenada o, coordenada d)
{
    bool res = false;
    ejecutarMovimiento(p, o, d);
    vector<coordenada> regicidas = cualesAtacanAlRey(p);
    for(int i = 0; i < regicidas.size(); ++i)
    {
        res |= jugadorEnJaque(p) && atacaAlRey(p, regicidas[i]);
    }
    return res;
}

// Si el jugador tiene un solo movimiento, devuelve las coordenadas de origen y destino de esa jugada
pair<coordenada,coordenada> jugadaForzada(const posicion &p)
{
    int cantidadJugadas = 0;
    pair<coordenada,coordenada> res;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int j = 0; j < ANCHO_TABLERO; ++j)
        {
            coordenada o = setCoord(i, j);
            vector<coordenada> jugadas = jugadasDisponibles(p, o);
            if(color(p.first, o) == jugador(p) && int(jugadas.size()) > 0)
            {
                cantidadJugadas += int(jugadas.size());
                res.first = o;
                res.second = jugadas[0];
            }
        }
    }
    if(cantidadJugadas > 1)
    {
        coordenada invalida = make_pair(-1, -1);
        res = make_pair(invalida, invalida);
    }
    return res;
}

vector<coordenada> obtenerPiezas(const posicion &p, int j)
{
    vector<coordenada> res;
    for(int i = 0; i < ANCHO_TABLERO; ++i)
    {
        for(int k = 0; k < ANCHO_TABLERO; ++k)
        {
            coordenada o = setCoord(i, k);
            if(color(p.first, o) == j)
                res.push_back(o);
        }
    }
    return res;
}

void cuantoParaElMate(const posicion &p, int k, int &res)
{
    vector<coordenada> piezas = obtenerPiezas(p, jugador(p));
    for(int i = 0; i < piezas.size() && k < res; ++i)
    {
        coordenada o = piezas[i];
        vector<coordenada> jugadas = jugadasDisponibles(p, o);
        for(int j = 0; j < jugadas.size(); ++j)
        {
            coordenada d = jugadas[j];
            posicion q = p;
            ejecutarMovimiento(q, o, d);
            pair<coordenada,coordenada> forzada = jugadaForzada(q);
            if(esJaqueMate(q))
            {
                res = k;
            }
            else if(forzada.first.first != -1)
            {
                ejecutarMovimiento(q, forzada.first, forzada.second);
                cuantoParaElMate(q, k + 1, res);
            }
        }
    }
}
