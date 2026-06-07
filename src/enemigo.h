#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"

#include <iostream>
#include <QPixmap>
class nivel;

class jugador;

class enemigo : public entidad {
protected:
    jugador* objetivo;
    float velocidad;
    short int dano;
    float rangoAtaque;

    bool elite;
    bool enSuelo;

    nivel *nivelPtr;

    short int frameAnim;
    float tiempoAnim;

    bool mirandoDerecha;

public:
    enemigo(float x=0, float y=0);

    virtual void update();

    virtual void atacar();

    void seguirObjetivo();

    jugador* getObjetivo();

    void setObjetivo(jugador* obj);
    void setVelocidad(float v);
    void setDano(short int d);

    void setElite(bool el);
    bool getElite();

    short int getDanio();

    virtual short int getTipo();

    void setEnSuelo(bool t);

    void setNivel(nivel* n);

    virtual bool estaEnDash();


    virtual QPixmap getFrame(
        const std::vector<QPixmap>& idle,
        const std::vector<QPixmap>& run
        );

    bool estaMirandoDerecha();

};

#endif
