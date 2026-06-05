#include "esqueleto.h"
#include <cmath>
esqueleto::esqueleto(float x, float y){
    this->x = x;
    this->y = y;
    rangoAtaque = 600;
    cooldownDisparo = 0;
}

void esqueleto::update(){
    if(cooldownDisparo > 0){
        cooldownDisparo -= 0.1f;
    }
    atacar();
}

void esqueleto::atacar(){

    if(cooldownDisparo > 0) return;

    cooldownDisparo = 8.0f;

    if(!objetivo) return;

    float dx = objetivo->getX() - x;
    float dy = objetivo->getY() - y;

    if(abs(dx) > 600) return;

    float tiempo = abs(dx) / 6.0f;

    float vx = dx / tiempo;


    float g = 0.3f;

    float vy = (dy / tiempo) - (0.5f * g * tiempo);

    float offsetDisparoX = 15;
    float offsetDisparoY = -10;

    float offsetX = offsetDisparoX;

    if(objetivo->getX() < x){
        offsetX = -offsetDisparoX;
    }

    float origenX = x + offsetX;
    float origenY = y + offsetDisparoY;

    proyectil* p = new proyectil(origenX, origenY, vx, vy, ENEMIGO);

    if(nivelPtr){
        nivelPtr->agregarProyectil(p);
    }
}

short int esqueleto::getTipo(){return 2;}

