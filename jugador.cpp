#include "jugador.h"
#include "jugador.h"
#include "proyectil.h"
#include <iostream>

jugador::jugador(float x, float y) : entidad(x,y,100){
    velocidadBase = 2.0;
    cooldownDisparo = 0;
    tiempoUltimoDisparo = 0;
    enSuelo = false;
    tiempoInmune = 0;

    tiempoVelocidad = 0;
    tiempoFuerza = 0;
    tiempoInmunidad = 0;
    tiempoLentitud = 0;

    velocidadBase = 3;
    velocidadActual = velocidadBase;

    danioBase = 20;
    danioActual = danioBase;

    mirandoDerecha = true;

}

void jugador::update(){

    enSuelo =false;


    vy += 0.4f;

    x += vx;
    y += vy;

    if(y > 500){
        y = 500;
        vy = 0;
        enSuelo = true;
    }


    mover();

    if(vx > 0){
        mirandoDerecha = true;
    }
    else if(vx < 0){
        mirandoDerecha = false;
    }

    if(tiempoUltimoDisparo > 0){
        tiempoUltimoDisparo -= 0.06f;
    }

    if(tiempoInmune > 0){
        tiempoInmune -= 0.07f;
    }

    if(cooldownDisparo > 0){
        cooldownDisparo -= 0.09f;
    }

    if(tiempoVelocidad > 0){
        tiempoVelocidad -= 0.07f;
        velocidadActual = velocidadBase * 1.2f;
    } else {
        velocidadActual = velocidadBase;
    }

    if(tiempoLentitud > 0){
        tiempoLentitud -= 0.07f;
        velocidadActual = velocidadBase * 0.6f;
    }

    if(tiempoFuerza > 0){
        tiempoFuerza -= 0.06f;
        danioActual = danioBase * 2;
    } else {
        danioActual = danioBase;
    }

    if(tiempoInmunidad > 0){
        tiempoInmunidad -= 0.7f;
    }




}

void jugador::moverIzquierda(){
    vx = -velocidadActual;
}

void jugador::moverDerecha(){
    vx = velocidadActual;
}

void jugador::detener(){
    vx = 0;
}

void jugador::saltar(){
    if(enSuelo){
        vy = -14;
        enSuelo = false;
    }
}


float jugador::getVelocidad(){
    return velocidadBase;
}


void jugador::setVelocidadBase(float v){
    velocidadBase = v;
}

proyectil* jugador::disparar(float dirX, float dirY){

    if(cooldownDisparo > 0) return nullptr;

    cooldownDisparo = 2.0f;

    float fuerza = 15.0f;

    float vx = dirX * fuerza;


    float vy = dirY * fuerza - 3.0f;

    return new proyectil(x, y, vx, vy, JUGADOR);
}

void jugador::recibirDanio(short int d){

    if(tiempoInmune > 0) return;

    if(tiempoInmunidad > 0) return;

    vida -= d;

    tiempoInmune = 1.5f;

    if(vida <= 0){
        vida = 0;
        activa = false;
    }
}

void jugador::setEnSuelo(bool t){
    enSuelo = t;
}

void jugador::curar(short int cantidad){

    vida += cantidad;

    if(vida > 100){
        vida = 100;
    }
}

void jugador::setTiempoVelocidad(float t){
    tiempoVelocidad = t;
}

void jugador::setTiempoFuerza(float t){
    tiempoFuerza = t;
}

void jugador::setTiempoInmunidad(float t){
    tiempoInmunidad = t;
}

void jugador::setTiempoLentitud(float t){
    tiempoLentitud = t;
}

short int jugador::getDanoActual(){return danioActual;}

void jugador::sumarTiempoAnim(float dt){
    tiempoAnim+=dt;
}

float jugador::getTiempoAnim(){return tiempoAnim;}

void jugador::setFrameAnim(short int f){
    frameAnim = f;
}

void jugador::setTiempoAnim(float dt){
    tiempoAnim = dt;
}

short int jugador::getFrameAnim(){return frameAnim;}

bool jugador::estaEnDerecha(){return mirandoDerecha;}
