#include "plataforma.h"

plataforma::plataforma(float x, float y, float ancho, float alto){
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
}

bool plataforma::colision(float px, float py, float radio){

    return (px + radio > x &&
            px - radio < x + ancho &&
            py + radio > y &&
            py - radio < y + alto);
}

float plataforma::getX()const{ return x; }
float plataforma::getY() const{ return y; }
float plataforma::getAncho() const{ return ancho; }
float plataforma::getAlto() const{ return alto; }
