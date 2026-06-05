#include "niveltransicion.h"

niveltransicion::niveltransicion(Dificultad d) : nivel(d) {
    finNivelX = 2215;


    plataformas.push_back(plataforma(0, 500, 2200, 50));
    jug.setX(100);
    jug.setY(480);
}

void niveltransicion::update(float dt){

    actualizarEntidades();
    limpiarEntidades();
}

bool niveltransicion::verificarWin(){

    return jug.getX() >= finNivelX;
}

bool niveltransicion::verificarLose(){

    return !jug.getActiva();
}

bool niveltransicion::esTransicion(){return true;}

void niveltransicion::spawn(){}

niveltransicion::~niveltransicion(){}
