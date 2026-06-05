#ifndef NIVELPASILLO_H
#define NIVELPASILLO_H

#include "nivel.h"

class nivelpasillo : public nivel {
private:
    short int contadorKills;
    short int objetivoKills;
    float finNivelX;
    float tiempo;

    float spawnCooldown;

    Dificultad difi;

    short int maxEnemigos;


public:
    nivelpasillo(Dificultad d);

    void update(float dt) override;
    void spawn() override;
    bool verificarWin() override;
    bool verificarLose() override;

    bool esPasillo() override;

    short int getKills() override;
    short int getObjetivoKills() override;
    float getTiempo() override;

};


#endif
