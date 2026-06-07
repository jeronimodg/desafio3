#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "entidad.h"

enum TipoProyectil{
    JUGADOR,
    ENEMIGO,
    JEFE
};

class proyectil : public entidad {
private:
    TipoProyectil tipo;



public:

    proyectil(float x, float y, float vx, float vy, TipoProyectil t);

    void update() override;

    TipoProyectil getTipo();


};

#endif
