#include "juego.h"
#include "nivelpasillo.h"
#include "nivelboss.h"
#include <iostream>
#include <QApplication>

juego::juego(){
    nivelActual = nullptr;
}

juego::~juego(){
    if(nivelActual){
        delete nivelActual;
    }
}

void juego::iniciar(Dificultad d){

    dif = d;

    if(nivelActual){
        delete nivelActual;
    }

    nivelActual = new nivelpasillo(d);

    corriendo = true;


}

void juego::update(float dt){

    if(!corriendo) return;

    if(!nivelActual) return;

    nivelActual->update(dt);

    if(nivelActual->verificarWin()){


        if(nivelActual->esPasillo()){

            emit cambioNivel();

            cambiarNivel(new niveltransicion(dif));

        }
        else if(nivelActual->esTransicion()){

            emit cambioNivel();

            cambiarNivel(new nivelboss(dif));

        }
        else if(nivelActual->esBoss()){

            corriendo = false;
            emit victoria();
        }

        return;
    }

    if(nivelActual->verificarLose()){

        corriendo = false;
        emit gameOver();
        return;
    }


}

void juego::cambiarNivel(nivel* nuevoNivel){

    if(nivelActual){
        delete nivelActual;
    }

    nivelActual = nuevoNivel;
}

bool juego::estaCorriendo(){
    return corriendo;
}

nivel* juego::getNivel(){
    return nivelActual;
}

void juego::procesarTecla(short int tecla){

    if(!nivelActual) return;

    nivelActual->procesarTecla(tecla);
}
void juego::procesarTeclaRelease(short int tecla){
    nivelActual->procesarTeclaRelease(tecla);
}

void juego::detener(){
    corriendo = false;
}
