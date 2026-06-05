#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"
#include <vector>
#include <QPixmap>
using namespace std;


class proyectil;

class jugador : public entidad {
private:
    float velocidadBase;
    float cooldownDisparo;
    float tiempoUltimoDisparo;
    float tiempoInmune;

    const float velocidad = 3;
    bool enSuelo;

    float tiempoVelocidad;
    float tiempoFuerza;
    float tiempoInmunidad;
    float tiempoLentitud;

    float velocidadActual;

    short int danioBase;
    short int danioActual;



    short int frameAnim;
    float tiempoAnim;

    std::vector<QPixmap> jugadorIdle;
    std::vector<QPixmap> jugadorRun;

    bool mirandoDerecha;

public:

    jugador(float x=0, float y=0);

    void update();

    void moverIzquierda();
    void moverDerecha();
    void detener();
    void saltar();



    float getVelocidad();


    void setVelocidadBase(float v);

    proyectil* disparar(float dirX, float dirY);

    void recibirDanio(short int d) override;

    void setEnSuelo(bool t);

    void curar(short int cantidad);

    void setTiempoVelocidad(float t);
    void setTiempoFuerza(float t);
    void setTiempoInmunidad(float t);
    void setTiempoLentitud(float t);

    short int getDanoActual();

    void sumarTiempoAnim(float dt);
    float getTiempoAnim();
    void setTiempoAnim(float dt);

    void setFrameAnim(short int f);
    short int getFrameAnim();

    bool estaEnDerecha();
};

#endif
