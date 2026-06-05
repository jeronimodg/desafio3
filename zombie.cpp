#include "zombie.h"

#include <cmath>
zombie::zombie(float x, float y){
    this->x=x;
    this->y=y;
}
void zombie::update(){

    vy += 0.3f;


    if(objetivo  && objetivo->getActiva()){

        float dx = objetivo->getX() - x;
        float dy = objetivo->getY() - y;


        if(dx > 0) vx = 0.5;
        else vx = -0.5;

        if(dy < -40 && enSuelo){
            vy = -8;
            enSuelo = false;
        }
    }

    x += vx;
    y += vy;

    if(y > 500){
        y = 500;
        vy = 0;
    }


}

void zombie::atacar(){
}

short int zombie::getTipo(){return 1;}




