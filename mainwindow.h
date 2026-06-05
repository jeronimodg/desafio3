#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QLabel>
#include <QMovie>
#include <QElapsedTimer>

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsDropShadowEffect>

#include "juego.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stack;


    QWidget *pantallaInicio;
    QWidget *pantallaSeleccion;
    QWidget *pantallaJuego;
    QWidget *pantallaGameOver;
    QWidget *pantallaVictoria;

    QWidget *pantallaAyuda;

    QWidget* pantallaPausa;
    QWidget* pantallaCarga;

    QPushButton* btnContinuar;
    QPushButton* btnReiniciarPausa;
    QPushButton* btnSalirMenu;


    QPushButton *btnJugar;
    QPushButton *btnSalir;
    QPushButton *btnAyuda;
    QPushButton *btnVolverAyuda;

    QPushButton *btnFacil;
    QPushButton *btnDificil;

    QPushButton *btnReiniciar;
    QPushButton *btnSalirFinal;

    QPushButton *btnReiniciarVic;
    QPushButton *btnSalirVic;

    QGraphicsView *view;
    QGraphicsScene *scene;

    QTimer *timer;

    QPixmap pixPlataforma;
    QPixmap spriteJugador;

    QLabel* gifLabel;
    QMovie* loadingGif;

    juego jueg;

    Dificultad ultimaDificultad;

    void crearPantallas();
    void conectarBotones();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);

    float camX = 400;
    float margen = 100;

    bool enCarga;
    QElapsedTimer relojCarga;

    short int pantallaDestino;

    bool pausado;

    bool nivelConectado;

    bool enTransicion;
    float tiempoTransicion;

    void renderJugador(jugador& j);
    void renderEnemigos(vector<enemigo*>& enemigos, jugador& jug);
    void renderProyectiles(vector<proyectil*>& proyectiles);
    void renderPlataformas(vector<plataforma>& plataformas);
    void renderPociones(vector<pocion>& pociones);
    void renderHUD(nivel* n);

    void renderFondo(nivel* n);

    void renderPortal();

    QPixmap imgFlecha;
    QPixmap imgLanza;
    QPixmap imgCraneo;


    //-----------------------daños

    QMediaPlayer* musica;
    QAudioOutput* audioMusica;

    QString musicaMenu;
    QString musicaPasillo;
    QString musicaBoss;

    QMediaPlayer* sHitJugador;
    QMediaPlayer* sHitZombie;
    QMediaPlayer* sHitEsqueleto;
    QMediaPlayer* sHitWither1;
    QMediaPlayer* sHitWither2;

    QAudioOutput* aHitJugador;
    QAudioOutput* aHitZombie;
    QAudioOutput* aHitEsqueleto;
    QAudioOutput* aHitWither1;
    QAudioOutput* aHitWither2;

    //------------------------disparos

    QMediaPlayer* sDisparoEsqueleto;
    QAudioOutput* aDisparoEsqueleto;

    QMediaPlayer* sDisparoWither;
    QAudioOutput* aDisparoWither;

    //---------------------muertes

    QMediaPlayer* sMuerteZombie;
    QAudioOutput* aMuerteZombie;

    QMediaPlayer* sMuerteEsqueleto;
    QAudioOutput* aMuerteEsqueleto;

    QMediaPlayer* sMuerteWither;
    QAudioOutput* aMuerteWither;

    //----------------------click

    QMediaPlayer* sClick;
    QAudioOutput* aClick;


    //----------------spawnjefe

    QMediaPlayer* sSpawnBoss;
    QAudioOutput* aSpawnBoss;


    QMediaPlayer* sFase2Boss;
    QAudioOutput* aFase2Boss;

    QMediaPlayer* sDashBoss;
    QAudioOutput* aDashBoss;

    // control
    bool bossFase2Sonido;
    bool bossDashSonido;

    QPixmap frame;

    QPixmap imgPocionVida;
    QPixmap imgPocionVelocidad;
    QPixmap imgPocionDanio;
    QPixmap imgPocionInmunidad;
    QPixmap imgPocionLentitud;

    QPixmap imgEsqueleto;

    QPixmap imgWitherFase1;
    QPixmap imgWitherFase2;
    QPixmap imgWitherDash;

    QPixmap imgPortal;

    void sonidoEnemigo(short int tipo);
    void sonidoMuerte(short int tipo);
    void sonidoDisparo(TipoProyectil tipo);

    void reproducirMusica(QString ruta);

    void actualizarMusica(nivel* n);

    bool bossSonidoYa;

    std::vector<QPixmap> jugadorIdle;
    std::vector<QPixmap> zombieIdle;

    std::vector<QPixmap> jugadorRun;
    std::vector<QPixmap> zombieRun;

};
#endif // MAINWINDOW_H
