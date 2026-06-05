#include "entidad.h"

entidad::entidad(float x, float y, short int vida) {
    this->x=x;
    this->y=y;
    this->vx=0;
    this->vy=0;
    this->vida=vida;
    this->activa=true;


}

entidad::~entidad(){}

void entidad::update(){
    mover();
}

void entidad::mover(){

    vy += 0.4f;

    x += vx;
    y += vy;
}

void entidad::recibirDanio(short int d){
    vida -= d;

    if(vida <= 0){
        vida = 0;
        activa = false;
    }
}

bool entidad::estavivo(){return activa;}

float entidad::getX(){ return x; }
float entidad::getY(){ return y; }
short int entidad::getVida(){ return vida; }
bool entidad::getActiva(){ return activa; }
float entidad::getVx(){return vx;}
float entidad::getVy(){return vy;}

void entidad::setX(float nx){ x = nx; }
void entidad::setY(float ny){ y = ny; }
void entidad::setVy(float Vy){vy = Vy;}
void entidad::setVelocidad(float nvx, float nvy){
    vx = nvx;
    vy = nvy;
}
void entidad::setVida(short int v){ vida = v; }
void entidad::setActiva(bool a){ activa = a; }
