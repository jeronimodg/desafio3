#include "nivelpasillo.h"
#include "enemigo.h"
#include <cstdlib>
#include <Qt>
nivelpasillo::nivelpasillo(Dificultad d) : nivel(d){

    difi = d;

    contadorKills = 0;
    objetivoKills = 15;
    tiempo = 80.0f;


    spawnCooldown = 0;

    maxEnemigos = 12;

    finNivelX = 2800;

    plataformas.push_back(plataforma(0, 510, 3000, 50));

    for(short int i = 200; i < 2800; i += 300){

        float x = i;
        float y = 250 + rand() % 200;

        plataformas.push_back(plataforma(x, y, 150, 20));
    }
}

void nivelpasillo::update(float dt){

    tiempo -= dt;

    spawn();

    actualizarEntidades();

    for(auto e : enemigos){
        if(!e->getActiva()){
            contadorKills++;
            manejarDrops(e->getX(), e->getY());
        }
    }

    limpiarEntidades();
}


void nivelpasillo::spawn(){

    if(spawnCooldown > 0){
        spawnCooldown -= 0.01f;
        return;
    }

    if(enemigos.size() >= maxEnemigos){return;}

    float x = rand() % 1400 + 200;
    float y = rand() % 200 + 100;

    enemigo* e;

    short int i= rand()%2;

    short int idx = rand() % plataformas.size();
    plataforma& plat = plataformas[idx];

    float pox = plat.getX() + rand() % (short int)plat.getAncho();
    float poy = plat.getY() - 10;

    if(abs(x - jug.getX()) < 200) return;

    if(i==0){
        e = new esqueleto(pox,poy);
    }
    else{
        e = new zombie(x,y);

    }

    e->setNivel(this);

    if(difi == FACIL){
        e->setVida(50);
        e->setDano(10);
    }
    else{
        e->setVelocidad(2.5);

        if(rand()%100 <= 30){
            e->setVida(120);
            e->setDano(20);
            e->setElite(true);
            e->setVelocidad(3);
        }
        else{
            e->setVida(80);
            e->setDano(15);

        }

    }
    enemigos.push_back(e);

    spawnCooldown = 1.4f;
}



bool nivelpasillo::verificarWin(){

    if(contadorKills >= objetivoKills && tiempo > 0 && jug.getX()>= finNivelX){
        return true;
    }

    return false;
}

bool nivelpasillo::verificarLose(){

    if(!jug.getActiva()) return true;

    if(tiempo <= 0) return true;

    return false;
}

bool nivelpasillo::esPasillo(){return true;}


short int nivelpasillo::getKills(){
    return contadorKills;
}

short int nivelpasillo::getObjetivoKills(){
    return objetivoKills;
}

float nivelpasillo::getTiempo(){
    return tiempo;
}

