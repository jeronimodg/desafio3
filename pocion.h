#ifndef POCION_H
#define POCION_H

#include "jugador.h"

enum TipoPocion {VIDA, VELOCIDAD, FUERZA, INMUNIDAD, LENTITUD};

class pocion {
private:
    float x, y;
    TipoPocion tipo;
    float duracion;
    bool activa;

public:
    pocion(float x=0, float y=0);

    void aplicar(jugador& j);
    void update();

    bool colision(jugador& j);

    bool getActiva();

    void setTipo(TipoPocion t);
    void setDuracion(float d);
    void setActiva(bool t);

    void setX(float px);
    void setY(float py);

    float getX() const;
    float getY() const;

    TipoPocion getTipo() const;

    float tiempoAnim;

};

#endif
