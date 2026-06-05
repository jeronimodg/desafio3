#ifndef WITHER_H
#define WITHER_H

#include "enemigo.h"
#include "jugador.h"
#include "nivel.h"
#include <vector>

class proyectil;

class wither : public enemigo {
private:
    short int fase;
    float cooldownAtaque;
    float tiempoAtaque;

    short int vidaMax;

    float cooldownDash;
    float tiempoDash;

    bool haciendoDash;
    float dashVX;
    float dashVY;

    float distanciaDash;
    float maxDistanciaDash;

    short int dashesRestantes;

    short int patronActual;
    float tiempoPatron;


    short int cantidad;

public:
    wither(float x=0, float y=0);

    void update() override;
    void atacar(std::vector<proyectil*>& proyectiles);

    void cambiarFase();

    bool estaViva();

    short int getFase();
    short int getVidaMax();



    void iniciarDash();

    bool estaEnDash() override;

    void setDashesRestantes(short int d);

    void setVidaMaxima(short int vidmax);

    short int getTipo() override;

    short int getDashesRestantes();



};

#endif
