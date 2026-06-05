#ifndef ESQUELETO_H
#define ESQUELETO_H
#include "enemigo.h"
#include "proyectil.h"
#include "nivel.h"
class esqueleto : public enemigo {
private:
    float cooldownDisparo;


public:
    esqueleto(float x, float y);

    void update();
    void atacar();

    short int getTipo() override;


};

#endif // ESQUELETO_H
