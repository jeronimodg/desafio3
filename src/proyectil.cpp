#include "proyectil.h"

proyectil::proyectil(float x, float y, float vx, float vy, TipoProyectil t){
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->tipo=t;
    activa = true;

}

void proyectil::update(){

    if(tipo == JEFE){
        x += vx;
        y += vy;
    }
    else{
        vy += 0.3f;
        x += vx;
        y += vy;
    }
    if(y > 600) activa = false;
}

TipoProyectil proyectil::getTipo(){return tipo;}

