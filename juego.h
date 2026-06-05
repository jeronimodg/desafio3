#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>

#include "nivel.h"
#include "nivelpasillo.h"
#include "niveltransicion.h"
#include "nivelboss.h"

class juego : public QObject{
    Q_OBJECT

private:
    nivel* nivelActual;

    Dificultad dif;

    bool corriendo;

public:
    juego();
    ~juego();

    void iniciar(Dificultad d);
    void update(float dt);
    void cambiarNivel(nivel* nuevoNivel);

    bool estaCorriendo();

    nivel* getNivel();

    void procesarTecla(short int tecla);
    void procesarTeclaRelease(short int tecla);

    void detener();

signals:
    void gameOver();
    void victoria();
    void cambioNivel();
};

#endif
