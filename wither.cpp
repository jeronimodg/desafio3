#include "wither.h"
#include "proyectil.h"
#include <cmath>
#include <cstdlib>

wither::wither(float x, float y) : enemigo(x,y){

    vidaMax = 400;
    vida = vidaMax;

    fase = 1;

    cooldownAtaque = 1.5f;
    tiempoAtaque = 0;

    velocidad = 1.0f;
    dano = 20;

    cooldownDash = 3.0f;
    tiempoDash = 0;

    haciendoDash = false;
    dashVX = 0;
    dashVY = 0;


    distanciaDash = 0;
    maxDistanciaDash = 300;

    dashesRestantes = 0;

    patronActual = 0;
    tiempoPatron = 0;

}

void wither::update(){

    if(!activa) return;

    tiempoAtaque += 0.015f;

    tiempoPatron += 0.015f;

    static float t = 0;
    t += 0.05f;

    y += sin(t) * 0.5f;

    if(tiempoPatron > 3.0f){
        patronActual = rand() % 3;
        tiempoPatron = 0;
    }


    cambiarFase();

    if(haciendoDash){

        x += dashVX;
        y += dashVY;

        distanciaDash += sqrt(dashVX*dashVX + dashVY*dashVY);

        if(distanciaDash >= maxDistanciaDash){

            haciendoDash = false;

            if(dashesRestantes > 0){
                iniciarDash();
                dashesRestantes--;
            }
        }

        return;
    }

    if(!haciendoDash && dashesRestantes > 0){
        iniciarDash();
        dashesRestantes--;
        return;
    }


    if(objetivo){
        seguirObjetivo();
    }

    mover();
}

void wither::cambiarFase(){

    if(fase == 1 && vida < vidaMax * 0.7){
        fase = 2;

        cantidad = 7;

        velocidad = 2.0f;
        cooldownAtaque = 1.2f;
    }

    if(fase == 2 && vida < vidaMax * 0.3){
        fase = 3;

        velocidad = 2.5f;
        cooldownAtaque = 1.0f;
    }
}


void wither::atacar(std::vector<proyectil*>& proyectiles){

    if(tiempoAtaque < cooldownAtaque) return;
    if(!objetivo) return;

    float dx = objetivo->getX()-x;
    float dy = objetivo->getY() - y;

    float mag = sqrt(dx*dx + dy*dy);
    if(mag == 0) return;

    dx /= mag;
    dy /= mag;

    float velocidad = (fase == 1 ? 3 : 5);

    switch(patronActual){


    case 0:{
        proyectil* p = new proyectil(x, y, dx*velocidad, dy*velocidad, JEFE);

        proyectiles.push_back(p);
        break;
    }


    case 1:{
        cantidad = 5;
        float anguloBase = -0.4f;
        float paso = 0.2f;

        float angCentro = atan2(dy, dx);

        for(short int i = 0; i < cantidad; i++){

            float ang = angCentro + anguloBase + i * paso;

            float vx = cos(ang) * velocidad;
            float vy = sin(ang) * velocidad;

            proyectil* p = new proyectil(x, y, vx, vy, JEFE);

            proyectiles.push_back(p);
        }
        break;
    }

    case 2:{
        float v = velocidad;

        proyectiles.push_back(new proyectil(x,y, v,0,JEFE));
        proyectiles.push_back(new proyectil(x,y,-v,0,JEFE));
        proyectiles.push_back(new proyectil(x,y,0, v,JEFE));
        proyectiles.push_back(new proyectil(x,y,0,-v,JEFE));

        break;
    }
    }

    tiempoAtaque = 0;
}

bool wither::estaViva(){
    return vida > 0;
}
short int wither::getFase(){
    return fase;
}

short int wither::getVidaMax(){
    return vidaMax;
}

void wither::iniciarDash(){

    if(!objetivo) return;

    float dx = objetivo->getX() - x;
    float dy = objetivo->getY() - y;

    float dist = sqrt(dx*dx + dy*dy);
    if(dist == 0) return;

    dx /= dist;
    dy /= dist;

    float velocidad = 20;

    dashVX = dx * velocidad;
    dashVY = dy * velocidad;

    if(dist < 200){
        maxDistanciaDash = 250;
    }
    else if(dist < 400){
        maxDistanciaDash = 400;
    }
    else{
        maxDistanciaDash = 600;
    }

    distanciaDash = 0;
    haciendoDash = true;
}


bool wither::estaEnDash(){
    return haciendoDash;
}

short int wither::getTipo(){return 3;}

void wither::setDashesRestantes(short int d){

    if(dashesRestantes > 0 ||  haciendoDash) return;

    dashesRestantes = d;

}

void wither::setVidaMaxima(short vidmax){vidaMax = vidmax;}

short int wither::getDashesRestantes(){ return dashesRestantes; }


