#include "pocion.h"

pocion::pocion(float x, float y){
    this->x = x;
    this->y = y;
    activa = true;

    tiempoAnim = 0;
}

void pocion::aplicar(jugador& j){

    switch(tipo){

    case VIDA:
        j.curar(15);
        break;

    case VELOCIDAD:
        j.setTiempoVelocidad(8.0f);
        break;

    case FUERZA:
        j.setTiempoFuerza(8.0f);
        break;

    case INMUNIDAD:
        j.setTiempoInmunidad(5.0f);
        break;

    case LENTITUD:
        j.setTiempoLentitud(5.0f);
        break;
    }
}
void pocion::update(){
    tiempoAnim += 0.05f;
}

/*bool pocion::colision(jugador& j){

    return (j.getX() >= x - 10 && j.getX() <= x + 10 &&
            j.getY() >= y - 10 && j.getY() <= y + 10);
}*/

bool pocion::colision(jugador& j){

    float px = x;
    float py = y;
    float pw = 20; // ancho pocion
    float ph = 20;

    float jx = j.getX();
    float jy = j.getY();
    float jw = 20;
    float jh = 20;

    return (px < jx + jw &&
            px + pw > jx &&
            py < jy + jh &&
            py + ph > jy);
}

bool pocion::getActiva(){
    return activa;
}

void pocion::setTipo(TipoPocion t){
    tipo = t;
}

void pocion::setDuracion(float d){
    duracion = d;
}

void pocion::setX(float px){
    x = px;
}

void pocion::setActiva(bool t){
    activa = t;
}

void pocion::setY(float py){
    y = py;
}

float pocion::getX() const{return x;}
float pocion::getY() const{return y;}

TipoPocion pocion::getTipo() const{return tipo;}
