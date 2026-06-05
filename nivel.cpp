#include "nivel.h"
#include <QT>
nivel::nivel(Dificultad d){
    difi = d;
    jugador jug(100,100);
}

nivel::~nivel(){
    for(auto e : enemigos){
        delete e;
    }
    for(auto p : proyectiles){
        delete p;
    }
}

void nivel::actualizarEntidades(){

    static short int proyectilesAntes = 0;
    short int proyectilesAhora = proyectiles.size();

    jug.update();

    if(jug.getX() < 0){
        jug.setX(0);
    }

    for(auto& e : enemigos){

        if(!e || !e->getActiva()) continue;

        if(jug.getActiva()){
            e->setObjetivo(&jug);
        } else {
            e->setObjetivo(nullptr);
        }


        if(jug.getActiva()){
            float dx = e->getX() - jug.getX();
            float dy = e->getY() - jug.getY();

            float dist = sqrt(dx*dx + dy*dy);

            if(dist < 24){

                emit jugadorDano();

                jug.recibirDanio(e->getDanio());
            }
        }


        e->update();

    }

    if(proyectilesAhora > proyectilesAntes){

        proyectil* p = proyectiles.back();

        if(p->getTipo() == ENEMIGO){
            emit disparoEnemigo(ENEMIGO); // esqueleto
        }
        else if(p->getTipo() != JUGADOR){
            emit disparoEnemigo(JEFE); // wither
        }
    }

    for(auto& p : proyectiles){

        if(!p) continue;

        p->update();

        for(auto& plat : plataformas){

            float px = p->getX();
            float py = p->getY();

            float rx = plat.getX();
            float ry = plat.getY();
            float rw = plat.getAncho();
            float rh = plat.getAlto();

            if(px >= rx && px <= rx + rw &&
                py >= ry && py <= ry + rh){


                p->setActiva(false);
                break;
            }
        }

        if(p->getTipo() == JUGADOR){

            for(auto e : enemigos){

                if(!e || !e->getActiva()) continue;


                float dx = p->getX() - e->getX();
                float dy = p->getY() - e->getY();

                float dist = sqrt(dx*dx + dy*dy);

                if((dist < 26 && e->getTipo() != 3) ){
                    if(e->getActiva()){
                        emit enemigoDano(e->getTipo());

                        e->recibirDanio(jug.getDanoActual());
                    }

                    p->setActiva(false);
                    break;
                }
                if(dist < 40 && e->getTipo() == 3){

                    if(e->getActiva()){
                        emit enemigoDano(e->getTipo());

                        e->recibirDanio(jug.getDanoActual());
                    }

                    p->setActiva(false);
                    break;
                }
            }
        }

        else{
            if(jug.getActiva()){

                float dx = p->getX() - jug.getX();
                float dy = p->getY() - jug.getY();

                float dist = sqrt(dx*dx + dy*dy);

                if(dist < 20){

                    emit jugadorDano();

                    if(p->getTipo() == ENEMIGO){


                        jug.recibirDanio(10);
                        p->setActiva(false);

                    }
                    else{

                        if(difi == DIFICIL){
                            jug.recibirDanio(30);
                            p->setActiva(false);
                        }
                        else{
                            jug.recibirDanio(25);
                            p->setActiva(false);
                        }
                    }

                }
            }
        }
    }

    for(auto& plat : plataformas){

        if(jug.getVy() >= 0){

            if(plat.colision(jug.getX(), jug.getY(), 10)){


                jug.setY(plat.getY() - 10);

                jug.setVy(0);
                jug.setEnSuelo(true);
            }
        }
    }

    for(auto& e : enemigos){

        for(auto& plat : plataformas){

            if(e->getTipo() == 3) continue;

            if(e->estaEnDash()) continue;



            if(e->getVy() >= 0){

                if(plat.colision(e->getX(), e->getY(), 10)){

                    e->setY(plat.getY() - 10);
                    e->setVy(0);

                    if(e) e->setEnSuelo(true);
                }
            }
        }
    }

    for(auto& p : pociones){
        p.update();

        if(p.getActiva() && p.colision(jug)){
            p.aplicar(jug);
            p.setActiva(false);
        }
    }

    proyectilesAntes = proyectilesAhora;
}

void nivel::limpiarEntidades(){

    for(auto it = enemigos.begin(); it != enemigos.end(); ){

        if(*it == nullptr){
            it = enemigos.erase(it);
            continue;
        }



        if(!(*it)->getActiva()){

            if((*it)->getTipo() == 3){

                emit enemigoMuere((*it)->getTipo());

                ++it;
                continue;
            }

            float x = (*it)->getX();
            float y = (*it)->getY();

            manejarDrops(x, y);

            emit enemigoMuere((*it)->getTipo());

            delete *it;

            it = enemigos.erase(it);
        }
        else {
            ++it;
        }
    }

    for(auto it = proyectiles.begin(); it != proyectiles.end(); ){

        if(!(*it)->getActiva()){

            if(*it != nullptr){
                delete *it;
                *it = nullptr;
            }

            it = proyectiles.erase(it);

        }
        else {
            ++it;
        }
    }

    for(auto it = pociones.begin(); it != pociones.end(); ){

        if(!it->getActiva()){
            it = pociones.erase(it);
        }
        else{
            ++it;
        }
    }


}

jugador& nivel::getJugador(){
    return jug;
}

vector<enemigo*>& nivel::getEnemigos(){
    return enemigos;
}

vector<proyectil*>& nivel::getProyectiles(){
    return proyectiles;
}

vector<plataforma>& nivel::getPlataformas(){
    return plataformas;
}

bool nivel::esPasillo(){return false;}
bool nivel::esTransicion(){return false;}
bool nivel::esBoss(){return false;}

bool nivel::jugadorMuerto(){
    return jug.estavivo();
}

void nivel::procesarTecla(short int tecla){

    if(tecla == Qt::Key_A) jug.moverIzquierda();
    if(tecla == Qt::Key_D) jug.moverDerecha();
    if(tecla == Qt::Key_W) jug.saltar();
}

void nivel::procesarTeclaRelease(short int tecla){

    if(tecla == Qt::Key_A || tecla == Qt::Key_D){
        jug.detener();
    }
}

void nivel::agregarProyectil(proyectil* p){
    proyectiles.push_back(p);
}

vector<pocion>& nivel::getPociones(){
    return pociones;
}

void nivel::manejarDrops(float x, float y){

    short int prob = rand() % 100;


    if(prob > 40) return;

    pocion p;

    short int tipoRand = rand() % 5;

    switch(tipoRand){

    case 0:
        p.setTipo(VIDA);
        break;

    case 1:
        p.setTipo(VELOCIDAD);
        break;

    case 2:
        p.setTipo(FUERZA);
        break;

    case 3:
        p.setTipo(INMUNIDAD);
        break;

    case 4:
        p.setTipo(LENTITUD);
        break;
    }

    p.setX(x);
    p.setY(y);

    p.setActiva(true);

    pociones.push_back(p);
}

void nivel::dispararJugador(float mouseX, float mouseY){

    float dxx = mouseX - jug.getX();
    float dyy = mouseY - jug.getY();

    float mag = sqrt(dxx*dxx + dyy*dyy);

    if(mag != 0){
        dxx /= mag;
        dyy /= mag;
    }

    proyectil* p = jug.disparar(dxx, dyy);

    if(p != nullptr){
        proyectiles.push_back(p);
    }
}



