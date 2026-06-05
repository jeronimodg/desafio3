#ifndef NIVELBOSS_H
#define NIVELBOSS_H

#include "nivel.h"
#include "enemigo.h"
#include "wither.h"
class nivelboss : public nivel {
private:
    wither* boss;

    Dificultad difi;

    short int fase;
    float tiempoFase;

    float spawnPocionesCooldown;

    float cooldownDash;

    Dificultad difiJefe;

public:
    nivelboss(Dificultad d);

    void update(float dt) override;
    void spawn() override;
    bool verificarWin() override;
    bool verificarLose() override;

    void comportamientoBoss();
    void spawnPociones(float dt);

    bool esBoss() override;

    wither* getBoss();


};

#endif
