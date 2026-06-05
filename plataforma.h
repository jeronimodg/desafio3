#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "entidad.h"

class plataforma {
private:
    float x, y;
    float ancho, alto;

public:
    plataforma(float x=0, float y=0, float ancho=100, float alto=20);

    bool colision(float px, float py, float radio);

    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;
};

#endif
