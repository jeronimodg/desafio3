#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "enemigo.h"
#include "jugador.h"
class zombie : public enemigo {

public:
    zombie(float x, float y);

    void update();
    void atacar();

    short int getTipo() override;




};

#endif // ZOMBIE_H
