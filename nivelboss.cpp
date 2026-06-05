#include "nivelboss.h"
#include "proyectil.h"

#include <cstdlib>
#include <cmath>

nivelboss::nivelboss(Dificultad d) : nivel(d){

    boss = new wither(2000, 300);

    difiJefe = d;

    if(d == DIFICIL){
        boss->setVida(800);
        boss->setVidaMaxima(800);
        boss->setDano(25);

        if(rand()%100 < 20){
            boss->setElite(true);
            boss->setVida(1200);
            boss->setVidaMaxima(1200);
            boss->setDano(30);
        }
    }

    plataformas.push_back(plataforma(0, 500, 4000, 50));


    plataformas.push_back(plataforma(0, 500, 4000, 50));


    plataformas.push_back(plataforma(500, 400, 200, 20));
    plataformas.push_back(plataforma(1300, 350, 200, 20));
    plataformas.push_back(plataforma(2500, 400, 200, 20));
    plataformas.push_back(plataforma(3300, 350, 200, 20));


    plataformas.push_back(plataforma(1800, 300, 400, 20));

    enemigos.push_back(boss);

    fase = 1;
    tiempoFase = 0;

    cooldownDash = 0;

    spawnPocionesCooldown = 5.0f;

    jug.setX(100);
    jug.setY(480);
}

void nivelboss::update(float dt){

    tiempoFase += dt;

    cooldownDash -= dt;
    if(cooldownDash < 0) cooldownDash = 0;

    if(jug.getX() < 50) jug.setX(50);
    if(jug.getX() > 3950) jug.setX(3950);

    comportamientoBoss();

    spawnPociones(dt);

    actualizarEntidades();

    limpiarEntidades();
}

void nivelboss::spawn(){}



void nivelboss::comportamientoBoss(){

    if(!boss->estaViva() || !boss) return;


    if(fase == 1 && boss->getVida() < boss->getVidaMax() * 0.7){
        fase = 2;
    }

    if(fase == 2 && boss->getVida() < boss->getVidaMax() * 0.3){
        fase = 3;
    }

    boss->atacar(proyectiles);

    if(fase == 3){

        float dx = boss->getX() - jug.getX();
        float dy = boss->getY() - jug.getY();

        float dist = sqrt(dx*dx + dy*dy);


        if(dist < 800){

            if(cooldownDash <= 0){

                if(difiJefe == FACIL){
                    boss->setDashesRestantes(1);
                }
                else{
                    boss->setDashesRestantes(boss->getElite() ? 3 : 2);
                }

                cooldownDash = (difiJefe == FACIL ? 4.0f : 3.0f);

            }
        }
    }
}

void nivelboss::spawnPociones(float dt){

    if(spawnPocionesCooldown > 0){
        spawnPocionesCooldown -= dt;
        return;
    }

    pocion p;

    p.setX(boss->getX());
    p.setY(boss->getY());

    short int tipo = rand() % 5;

    p.setTipo((TipoPocion)tipo);
    p.setDuracion(5.0f);

    pociones.push_back(p);

    spawnPocionesCooldown = 5.0f;
}

bool nivelboss::verificarWin(){

    if(!boss->estaViva()){
        return true;
    }

    return false;
}

bool nivelboss::verificarLose(){
    if(!jug.getActiva()){
        return true;
    }
    return false;
}

bool nivelboss::esBoss(){return true;}

wither* nivelboss::getBoss(){
    if(!boss || !boss->getActiva()) return nullptr;

    return boss;
}





