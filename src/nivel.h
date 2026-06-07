#ifndef NIVEL_H
#define NIVEL_H

#include <QObject>
#include <vector>
#include "jugador.h"
#include "enemigo.h"
#include "zombie.h"
#include "esqueleto.h"
#include "proyectil.h"
#include "pocion.h"
#include "plataforma.h"

enum Dificultad{
    FACIL,
    DIFICIL
};

using namespace std;

class nivel : public QObject {

    Q_OBJECT

protected:
    jugador jug;

    Dificultad difi;

    vector<enemigo*> enemigos;
    vector<proyectil*> proyectiles;
    vector<pocion> pociones;
    vector<plataforma> plataformas;

public:
    nivel(Dificultad d);

    virtual ~nivel();

    virtual void update(float dt) = 0;
    virtual void spawn() = 0;
    virtual bool verificarWin() = 0;
    virtual bool verificarLose() = 0;

    void actualizarEntidades();
    void limpiarEntidades();

    jugador& getJugador();
    vector<enemigo*>& getEnemigos();
    vector<proyectil*>& getProyectiles();
    vector<plataforma>& getPlataformas();
    vector<pocion>& getPociones();

    virtual bool esPasillo();
    virtual bool esTransicion();
    virtual bool esBoss();

    virtual float getTiempo(){ return 0; }
    virtual short int getKills(){ return 0; }
    virtual short  getObjetivoKills(){ return 0; }

    virtual void dispararJugador(float dx, float dy);

    bool jugadorMuerto();

    void procesarTecla(short int tecla);
    void procesarTeclaRelease(short int tecla);

    void agregarProyectil(proyectil* p);

    void manejarDrops(float x, float y);


signals:
    void enemigoDano(short int tipo);
    void jugadorDano();
    void enemigoMuere(short int tipo);
    void disparoEnemigo(TipoProyectil tipo);

};

#endif
