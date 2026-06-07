#include "enemigo.h"
#include "jugador.h"
#include "nivel.h"
#include <cmath>


enemigo::enemigo(float x, float y) : entidad(x, y, 50){
    objetivo = nullptr;
    velocidad = 1.5;
    dano = 10;
    rangoAtaque = 20;
    elite = false;

    frameAnim = 0;
    tiempoAnim = 0;
    mirandoDerecha = true;
}

void enemigo::update(){

    if(!activa) return;

    if(objetivo != nullptr && objetivo->getActiva()){


        seguirObjetivo();

        if(vx > 0){
            mirandoDerecha = true;
        }
        else if(vx < 0){
            mirandoDerecha = false;
        }


        float dx = objetivo->getX() - x;
        float dy = objetivo->getY() - y;

        float dist = sqrt(dx*dx + dy*dy);

        if(dist <= rangoAtaque){
            atacar();
        }
    }

    mover();


}

void enemigo::seguirObjetivo(){

    float dx = objetivo->getX() - x;
    float dy = objetivo->getY() - y;

    float mag = sqrt(dx*dx + dy*dy);

    if(mag == 0) return;

    vx = (dx / mag) * velocidad;
    vy = (dy / mag) * velocidad;
}

void enemigo::atacar(){
    if(objetivo){
        objetivo->recibirDanio(dano);
    }
}

jugador* enemigo::getObjetivo(){
    return objetivo;
}

void enemigo::setObjetivo(jugador* obj){
    objetivo = obj;
}

void enemigo::setVelocidad(float v){
    velocidad = v;
}

void enemigo::setDano(short int d){
    dano = d;
}

void enemigo::setElite(bool el){
    elite = el;
}

bool enemigo::getElite(){return elite;}


short int enemigo::getTipo(){return 0;}

short int enemigo::getDanio(){return dano;}

void enemigo::setEnSuelo(bool t){enSuelo = t;}

void enemigo::setNivel(nivel* n){
    nivelPtr = n;
}

bool enemigo::estaEnDash(){return false;}

QPixmap enemigo::getFrame(
    const std::vector<QPixmap>& idle,
    const std::vector<QPixmap>& run
    ){
    bool enMovimiento = std::abs(vx) > 0.1f;

    if(enMovimiento){

        tiempoAnim += 0.016f;

        if(tiempoAnim > 0.12f){
            frameAnim = (frameAnim + 1) % run.size();
            tiempoAnim = 0;
        }

        return run[frameAnim];
    }
    else{
        frameAnim = 0;
        tiempoAnim = 0;

        return idle[0];
    }
}

bool enemigo::estaMirandoDerecha(){return mirandoDerecha;}


