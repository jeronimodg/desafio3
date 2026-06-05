#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QKeyEvent>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bossSonidoYa = false;

    bossDashSonido = false;
    bossFase2Sonido = false;

    jugadorIdle.push_back(QPixmap(":/imagenes/idle_jugador.png").scaledToHeight(40));


    for(short int i = 1; i <= 4; i++){
        jugadorRun.push_back(
            QPixmap(QString(":/imagenes/jugador%1.png").arg(i))
                .scaledToHeight(40)
            );
    }


    zombieIdle.push_back(QPixmap(":/imagenes/idle_zombie.png").scaledToHeight(40));


    for(short int i = 1; i <= 3; i++){
        zombieRun.push_back(
            QPixmap(QString(":/imagenes/zombie%1.png").arg(i))
                .scaledToHeight(40)
            );
    }


    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    musica = new QMediaPlayer(this);
    audioMusica = new QAudioOutput(this);

    musica->setAudioOutput(audioMusica);
    audioMusica->setVolume(1.0);

    musicaMenu = "qrc:/sonidos/dry_hands.mp3";
    musicaPasillo = "qrc:/sonidos/aria_math.mp3";
    musicaBoss = "qrc:/sonidos/infinite_amethyst.mp3";

    connect(musica, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::EndOfMedia){
            musica->setPosition(0);
            musica->play();
        }
    });

    imgPocionVida = QPixmap(":/imagenes/pocion_curar.png").scaled(20,20,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgPocionVelocidad = QPixmap(":/imagenes/pocion_velocidad.png").scaled(20,20,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgPocionDanio = QPixmap(":/imagenes/pocion_fuerza.png").scaled(20,20,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgPocionInmunidad = QPixmap(":/imagenes/pocion_inmunidad.png").scaled(20,20,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgPocionLentitud = QPixmap(":/imagenes/pocion_lentitud.png").scaled(20,20,Qt::KeepAspectRatio, Qt::SmoothTransformation);



    imgFlecha = QPixmap(":/imagenes/prueba_flecha.png").scaled(22,22, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgLanza = QPixmap(":/imagenes/ataque_jugador.png").scaled(25,25, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgCraneo = QPixmap(":/imagenes/ataque_wither.png").scaled(24,24, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgEsqueleto = QPixmap(":/imagenes/posible_esqueleto.png")
                       .scaled(50, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgWitherFase1 = QPixmap(":/imagenes/posible_wither.png")
                         .scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgWitherFase2 = QPixmap(":/imagenes/posible_fase2_wither.png")
                         .scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgWitherDash = QPixmap(":/imagenes/posible_fase2_wither.png")
                        .scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgPortal = QPixmap(":/imagenes/posible_portal.png")
                    .scaled(420, 340, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //-----------------------------------------SONIDOS-----------------------------------------

    auto crearSonido = [&](QMediaPlayer*& player, QAudioOutput*& audio, QString ruta){

        player = new QMediaPlayer(this);
        audio = new QAudioOutput(this);

        player->setAudioOutput(audio);
        audio->setVolume(0.7);

        player->setSource(QUrl(ruta));

        player->play();
        player->pause();
        player->setPosition(0);
    };

    // Boton
    crearSonido(sClick, aClick, "qrc:/sonidos/boton_menu.wav");

    // Jugador
    crearSonido(sHitJugador, aHitJugador, "qrc:/sonidos/dano_steve.wav");

    // Enemigos
    crearSonido(sHitZombie, aHitZombie, "qrc:/sonidos/dano_zombie.wav");
    crearSonido(sHitEsqueleto, aHitEsqueleto, "qrc:/sonidos/dano_esqueleto.wav");

    crearSonido(sHitWither1, aHitWither1, "qrc:/sonidos/dano_wither1.wav");
    crearSonido(sHitWither2, aHitWither2, "qrc:/sonidos/dano_wither2.wav");

    // Disparos
    crearSonido(sDisparoEsqueleto, aDisparoEsqueleto, "qrc:/sonidos/disparo_esqueleto.wav");
    crearSonido(sDisparoWither, aDisparoWither, "qrc:/sonidos/disparo_wither.wav");

    // Muertes
    crearSonido(sMuerteZombie, aMuerteZombie, "qrc:/sonidos/derrota_zombie.wav");
    crearSonido(sMuerteEsqueleto, aMuerteEsqueleto, "qrc:/sonidos/derrota_esqueleto.wav");
    crearSonido(sMuerteWither, aMuerteWither, "qrc:/sonidos/derrota_wither.wav");

    //Spawn
    crearSonido(sSpawnBoss, aSpawnBoss, "qrc:/sonidos/Wither_spawn.wav");

    //Fase 2 wither y dash
    crearSonido(sFase2Boss, aFase2Boss, "qrc:/sonidos/wither_fase2.wav");
    crearSonido(sDashBoss, aDashBoss, "qrc:/sonidos/dashjefe.wav");


    pausado = false;

    crearPantallas();

    conectarBotones();

    stack->setCurrentIndex(0);

    reproducirMusica(musicaMenu);


    connect(&jueg, &juego::gameOver, this, [=](){

        jueg.detener();
        stack->setCurrentIndex(3);
        scene->clear();
    });

    connect(&jueg, &juego::victoria, this, [=](){

        jueg.detener();

        stack->setCurrentIndex(4);
        scene->clear();
    });

    connect(&jueg, &juego::cambioNivel, this, [=](){
        enCarga = true;
        pantallaDestino = 2;

        stack->setCurrentIndex(6);

        loadingGif->start();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;

        nivel* n = jueg.getNivel();
        actualizarMusica(n);

        bossSonidoYa = false;
        bossFase2Sonido = false;
        bossDashSonido = false;
    });

    pixPlataforma = QPixmap("://imagenes/candidato_plataforma.png");

    nivelConectado = false;

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=](){

        if(enCarga){

            if(relojCarga.elapsed() >= 5500){

                enCarga = false;

                loadingGif->stop();

                scene->clear();

                stack->setCurrentIndex(pantallaDestino);
            }

            return;
        }


        if(stack->currentIndex() == 2 && jueg.estaCorriendo() && !pausado){
            jueg.update(0.016f);
        }

        if(stack->currentIndex() != 2){
            return;
        }



        scene->clear();

        QPixmap test = spriteJugador.copy(45, 25, 38, 67).scaled(64,64);
        scene->addPixmap(test)->setPos(0,0);

        nivel* n = jueg.getNivel();
        if(!n) return;

        if(n && n->esBoss()){
            reproducirMusica(musicaBoss);
        }



        if(n && !nivelConectado){

            connect(n, &nivel::enemigoDano, this, [=](int tipo){
                sonidoEnemigo(tipo);
            });

            connect(n, &nivel::jugadorDano, this, [=](){
                sHitJugador->setPosition(0);
                sHitJugador->play();
            });

            connect(n, &nivel::enemigoMuere, this, [=](short int tipo){
                sonidoMuerte(tipo);
            });

            connect(n, &nivel::disparoEnemigo, this, [=](TipoProyectil tipo){
                sonidoDisparo(tipo);
            });

            nivelConectado = true;
        }

        jugador& j = n->getJugador();

        renderFondo(n);
        renderPlataformas(n->getPlataformas());
        renderEnemigos(n->getEnemigos(), j);
        renderJugador(j);
        renderProyectiles(n->getProyectiles());
        renderPociones(n->getPociones());
        renderHUD(n);
        if(dynamic_cast<niveltransicion*>(n)){
            renderPortal();
        }


        if(auto nb = dynamic_cast<nivelboss*>(n)){

            wither* b = nb->getBoss();

            if(b && b->getActiva()){

                if(!bossSonidoYa){

                    sSpawnBoss->setPosition(0);
                    sSpawnBoss->play();

                    bossSonidoYa = true;
                }

                if(b->estaEnDash()){

                    if(!bossDashSonido){

                        sDashBoss->setPosition(0);
                        sDashBoss->play();

                        bossDashSonido = true;
                    }
                }
                else{
                    bossDashSonido = false;
                }

                float vida = b->getVida();
                float maxVida = b->getVidaMax();

                if(vida < maxVida * 0.7 && !bossFase2Sonido){

                    sFase2Boss->setPosition(0);
                    sFase2Boss->play();

                    bossFase2Sonido = true;
                }

                float porcentaje = (float)vida / (float)maxVida;

                float ancho = 300;
                float alto = 20;

                short int anchoView = view->viewport()->width();

                float x = view->mapToScene(anchoView - 320, 20).x();
                float y = view->mapToScene(20, 20).y();


                scene->addRect(x, y, ancho, alto, QPen(), QBrush(Qt::black));


                scene->addRect(x, y, ancho * porcentaje, alto, QPen(), QBrush(Qt::red));
            }
        }

        float jugadorX = j.getX();

        if(jugadorX > camX + margen) camX = jugadorX - margen;
        if(jugadorX < camX - margen) camX = jugadorX + margen;

        view->centerOn(camX, 300);
    });

}

void MainWindow::crearPantallas(){

    pantallaInicio = new QWidget();


    QVBoxLayout *layoutInicio = new QVBoxLayout();


    QLabel* fondoInicio = new QLabel();
    fondoInicio->setScaledContents(true);
    fondoInicio->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    fondoInicio->setMinimumSize(1,1);

    QPixmap imgInicio(":/imagenes/fondo_inicio.jpg");
    fondoInicio->setPixmap(imgInicio);



    QVBoxLayout* overlayLayout = new QVBoxLayout(fondoInicio);

    btnJugar = new QPushButton("Jugar");
    btnSalir = new QPushButton("Salir");
    btnAyuda = new QPushButton("¿Como jugar?");

    QString estiloBoton =
        "QPushButton {"
        "background-color: #d3d3d3;"
        "border: 2px solid #888;"
        "border-radius: 5px;"
        "padding: 8px;"
        "font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #e0e0e0;"
        "}"
        "QPushButton:pressed {"
        "background-color: #bcbcbc;"
        "}";

    btnJugar->setStyleSheet(estiloBoton);
    btnSalir->setStyleSheet(estiloBoton);
    btnAyuda->setStyleSheet(estiloBoton);

    btnJugar->setFixedSize(200, 50);
    btnSalir->setFixedSize(200, 50);
    btnAyuda->setFixedSize(200,50);

    QLabel* tituloInicio = new QLabel();
    QPixmap txtInicio("://imagenes/Udeacraft.jpg");

    tituloInicio->setPixmap(txtInicio);
    tituloInicio->setAlignment(Qt::AlignCenter);
    tituloInicio->setScaledContents(true);
    tituloInicio->setMaximumHeight(150);


    overlayLayout->addStretch();
    overlayLayout->addWidget(tituloInicio, 0, Qt::AlignCenter);
    overlayLayout->addSpacing(20);

    overlayLayout->addWidget(btnJugar, 0, Qt::AlignCenter);
    overlayLayout->addWidget(btnSalir, 0, Qt::AlignCenter);
    overlayLayout->addWidget(btnAyuda, 0, Qt::AlignCenter);
    overlayLayout->addStretch();

    layoutInicio->addWidget(fondoInicio);
    pantallaInicio->setLayout(layoutInicio);



    // PANTALLA SELECCIÓN

    pantallaSeleccion = new QWidget();
    QVBoxLayout *layoutSel = new QVBoxLayout();

    QLabel* fondoSel = new QLabel();
    fondoSel->setScaledContents(true);
    fondoSel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    fondoSel->setMinimumSize(1,1);

    QPixmap imgSel(":/imagenes/fondo_inicio.jpg");
    fondoSel->setPixmap(imgSel);


    QVBoxLayout* overlaySel = new QVBoxLayout(fondoSel);

    btnFacil = new QPushButton("Facil");
    btnDificil = new QPushButton("Dificil");

    btnFacil->setStyleSheet(estiloBoton);
    btnDificil->setStyleSheet(estiloBoton);

    btnFacil->setFixedSize(200,50);
    btnDificil->setFixedSize(200,50);

    overlaySel->addStretch();
    overlaySel->addWidget(btnFacil, 0, Qt::AlignCenter);
    overlaySel->addWidget(btnDificil, 0, Qt::AlignCenter);
    overlaySel->addStretch();

    layoutSel->addWidget(fondoSel);
    pantallaSeleccion->setLayout(layoutSel);



    // PANTALLA JUEGO

    pantallaJuego = new QWidget();
    QVBoxLayout *layoutJuego = new QVBoxLayout();

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    scene->setSceneRect(0, 0, 3000, 600);

    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setMinimumSize(800, 600);

    layoutJuego->addWidget(view);
    pantallaJuego->setLayout(layoutJuego);



    // GAME OVER


    pantallaGameOver = new QWidget();
    QVBoxLayout *layoutOver = new QVBoxLayout();

    QLabel* fondoOver = new QLabel();
    fondoOver->setScaledContents(true);
    fondoOver->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    fondoOver->setMinimumSize(1,1);

    QPixmap imgOver(":/imagenes/fondo_derrota.jpg");
    fondoOver->setPixmap(imgOver);

    QVBoxLayout* overlayOver = new QVBoxLayout(fondoOver);

    btnReiniciar = new QPushButton("Reiniciar");
    btnSalirFinal = new QPushButton("Salir");

    btnReiniciar->setStyleSheet(estiloBoton);
    btnSalirFinal->setStyleSheet(estiloBoton);

    btnReiniciar->setFixedSize(200,50);
    btnSalirFinal->setFixedSize(200,50);

    QLabel* tituloOver = new QLabel();
    QPixmap txtOver(":/imagenes/gameover.jpg");

    tituloOver->setPixmap(txtOver);
    tituloOver->setAlignment(Qt::AlignCenter);
    tituloOver->setScaledContents(true);
    tituloOver->setMaximumHeight(150);

    overlayOver->addStretch();
    overlayOver->addWidget(tituloOver, 0, Qt::AlignCenter);
    overlayOver->addSpacing(20);
    overlayOver->addWidget(btnReiniciar, 0, Qt::AlignCenter);
    overlayOver->addWidget(btnSalirFinal, 0, Qt::AlignCenter);
    overlayOver->addStretch();

    layoutOver->addWidget(fondoOver);
    pantallaGameOver->setLayout(layoutOver);

    // VICTORIA

    pantallaVictoria = new QWidget();
    QVBoxLayout *layoutVic = new QVBoxLayout();

    QLabel* fondoVic = new QLabel();
    fondoVic->setScaledContents(true);
    fondoVic->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    fondoVic->setMinimumSize(1,1);

    QPixmap imgVic(":/imagenes/fondo_victoria.jpg");
    fondoVic->setPixmap(imgVic);

    QVBoxLayout* overlayVic = new QVBoxLayout(fondoVic);

    btnReiniciarVic = new QPushButton("Reiniciar");
    btnSalirVic = new QPushButton("Salir");

    btnReiniciarVic->setStyleSheet(estiloBoton);
    btnSalirVic->setStyleSheet(estiloBoton);

    btnReiniciarVic->setFixedSize(200,50);
    btnSalirVic->setFixedSize(200,50);

    QLabel* tituloVic = new QLabel();
    QPixmap txtVic(":/imagenes/victory.jpg");

    tituloVic->setPixmap(txtVic);
    tituloVic->setAlignment(Qt::AlignCenter);
    tituloVic->setScaledContents(true);
    tituloVic->setMaximumHeight(150);

    overlayVic->addStretch();
    overlayVic->addWidget(tituloVic, 0, Qt::AlignCenter);
    overlayVic->addSpacing(20);
    overlayVic->addWidget(btnReiniciarVic, 0, Qt::AlignCenter);
    overlayVic->addWidget(btnSalirVic, 0, Qt::AlignCenter);
    overlayVic->addStretch();

    layoutVic->addWidget(fondoVic);
    pantallaVictoria->setLayout(layoutVic);

    // PANTALLA PAUSA

    pantallaPausa = new QWidget();
    QVBoxLayout *layoutPausa = new QVBoxLayout();


    QLabel* fondoPausa = new QLabel();
    fondoPausa->setScaledContents(true);

    QPixmap imgPausa(":/imagenes/fondo_inicio.jpg");
    fondoPausa->setPixmap(imgPausa);


    QVBoxLayout* overlayPausa = new QVBoxLayout(fondoPausa);

    btnContinuar = new QPushButton("Continuar");
    btnReiniciarPausa = new QPushButton("Reiniciar");
    btnSalirMenu = new QPushButton("Salir al menu");


    btnContinuar->setStyleSheet(estiloBoton);
    btnReiniciarPausa->setStyleSheet(estiloBoton);
    btnSalirMenu->setStyleSheet(estiloBoton);

    btnContinuar->setFixedSize(200,50);
    btnReiniciarPausa->setFixedSize(200,50);
    btnSalirMenu->setFixedSize(200,50);

    overlayPausa->addStretch();
    overlayPausa->addWidget(btnContinuar, 0, Qt::AlignCenter);
    overlayPausa->addWidget(btnReiniciarPausa, 0, Qt::AlignCenter);
    overlayPausa->addWidget(btnSalirMenu, 0, Qt::AlignCenter);
    overlayPausa->addStretch();

    layoutPausa->addWidget(fondoPausa);
    pantallaPausa->setLayout(layoutPausa);



    // PANTALLA CARGA

    pantallaCarga = new QWidget();

    QVBoxLayout* layoutCarga = new QVBoxLayout();
    layoutCarga->setContentsMargins(0,0,0,0);
    layoutCarga->setSpacing(0);

    gifLabel = new QLabel();
    gifLabel->setAlignment(Qt::AlignCenter);
    gifLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    loadingGif = new QMovie(":/imagenes/fondo_cargando.gif");

    loadingGif->setScaledSize(this->size());

    gifLabel->setMovie(loadingGif);

    layoutCarga->addWidget(gifLabel);

    pantallaCarga->setLayout(layoutCarga);

    pantallaCarga->setStyleSheet("background-color: black;");



    // PANTALLA AYUDA


    pantallaAyuda = new QWidget();
    QVBoxLayout *layoutAyuda = new QVBoxLayout();

    QLabel* fondoAyuda = new QLabel();
    fondoAyuda->setScaledContents(true);

    QPixmap imgAyuda(":/imagenes/fondo_inicio.jpg");
    fondoAyuda->setPixmap(imgAyuda);


    QVBoxLayout* overlayAyuda = new QVBoxLayout(fondoAyuda);

    QLabel* textoAyuda = new QLabel(
        "<h2 style='color:white;'>OBJETIVO</h2>"
        "<p style='color:lightgray;'>"
        "- Elimina enemigos<br>"
        "- Llega al jefe"
        "</p>"

        "<h2 style='color:white;'>CONTROLES</h2>"
        "<p style='color:lightgray;'>"
        "WASD: Movimiento<br>"
        "Click: Disparo"
        "</p>"

        "<h2 style='color:#ffcc00;'>CONSEJO</h2>"
        "<p style='color:lightgray;'>"
        "Esquiva los dashes del jefe"
        "</p>"
        );

    textoAyuda->setAlignment(Qt::AlignCenter);
    textoAyuda->setWordWrap(true);
    textoAyuda->setMaximumWidth(400);

    textoAyuda->setStyleSheet(R"(
    QLabel {
        background-color: rgba(0, 0, 0, 160);
        padding: 15px;
        border-radius: 10px;
        font-size: 16px;
    }
    )");

    QGraphicsDropShadowEffect* sombra = new QGraphicsDropShadowEffect();

    sombra->setBlurRadius(15);
    sombra->setOffset(3, 3);
    sombra->setColor(Qt::black);

    textoAyuda->setGraphicsEffect(sombra);

    btnVolverAyuda = new QPushButton("Volver");
    btnVolverAyuda->setStyleSheet(estiloBoton);
    btnVolverAyuda->setFixedSize(200,50);

    overlayAyuda->addStretch();
    overlayAyuda->addWidget(textoAyuda, 0, Qt::AlignCenter);
    overlayAyuda->addSpacing(20);
    overlayAyuda->addWidget(btnVolverAyuda, 0, Qt::AlignCenter);
    overlayAyuda->addStretch();

    layoutAyuda->addWidget(fondoAyuda);
    pantallaAyuda->setLayout(layoutAyuda);





    // STACK


    stack->addWidget(pantallaInicio);    // 0
    stack->addWidget(pantallaSeleccion); // 1
    stack->addWidget(pantallaJuego);     // 2
    stack->addWidget(pantallaGameOver);  // 3
    stack->addWidget(pantallaVictoria);  // 4
    stack->addWidget(pantallaPausa);     // 5
    stack->addWidget(pantallaCarga);     // 6
    stack->addWidget(pantallaAyuda);     // 7

}


void MainWindow::conectarBotones(){

    connect(btnJugar, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        stack->setCurrentIndex(1);
    });

    connect(btnSalir, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        QApplication::quit();
        timer->stop();
        this->close();
    });


    // DIFICULTAD


    connect(btnFacil, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        enCarga = true;
        pantallaDestino = 2;

        stack->setCurrentIndex(6);

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        jueg.iniciar(FACIL);

        nivel* n = jueg.getNivel();
        actualizarMusica(n);


        relojCarga.restart();
        timer->start(16);

    });

    connect(btnDificil, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        enCarga = true;
        pantallaDestino = 2;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());
        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        jueg.iniciar(DIFICIL);

        nivel* n = jueg.getNivel();
        actualizarMusica(n);

        relojCarga.restart();

        timer->start(16);

    });


    // DERROTA


    connect(btnReiniciar, &QPushButton::clicked, this, [=](){

        reproducirMusica(musicaMenu);

        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 1;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });

    connect(btnSalirFinal, &QPushButton::clicked, this, [=](){

        reproducirMusica(musicaMenu);


        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 0;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });


    // VICTORIA


    connect(btnReiniciarVic, &QPushButton::clicked, this, [=](){

        reproducirMusica(musicaMenu);

        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 1;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });

    connect(btnSalirVic, &QPushButton::clicked, this, [=](){

        reproducirMusica(musicaMenu);

        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 0;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });


    // PAUSA


    connect(btnContinuar, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        stack->setCurrentIndex(2);
    });

    connect(btnReiniciarPausa, &QPushButton::clicked, this, [=](){


        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 1;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });

    connect(btnSalirMenu, &QPushButton::clicked, this, [=](){
        reproducirMusica(musicaMenu);

        sClick->setPosition(0);
        sClick->play();

        pausado = false;
        jueg.detener();

        enCarga = true;
        pantallaDestino = 0;

        stack->setCurrentIndex(6);
        loadingGif->setScaledSize(stack->size());

        loadingGif->start();
        gifLabel->repaint();
        QCoreApplication::processEvents();

        relojCarga.restart();

        nivelConectado = false;
    });

    //-----------------------------AYUDA-------------
    connect(btnAyuda, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        stack->setCurrentIndex(7);
    });

    connect(btnVolverAyuda, &QPushButton::clicked, this, [=](){

        sClick->setPosition(0);
        sClick->play();

        stack->setCurrentIndex(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(event->isAutoRepeat()) return;

    if(event->key() == Qt::Key_Escape){

        if(stack->currentIndex() == 2){
            pausado = true;
            stack->setCurrentIndex(5);
        }
        else if(stack->currentIndex() == 5){
            pausado = false;
            stack->setCurrentIndex(2);
        }

        return;
    }

    if(stack->currentIndex() == 2 && !pausado){
        jueg.procesarTecla(event->key());
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

    if(event->isAutoRepeat()) return;


    if(event->key() == Qt::Key_A || event->key() == Qt::Key_D){
        jueg.procesarTeclaRelease(event->key());
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){


    if(stack->currentIndex() != 2) return;

    if(pausado) return;

    QPointF punto = view->mapToScene(event->pos());

    float mx = punto.x();
    float my = punto.y();

    nivel* n = jueg.getNivel();

    if(n){
        n->dispararJugador(mx, my);
    }
}



//----------------------------------------------------------------------------------------
//---------------------------------- RENDERS ---------------------------------------------



void MainWindow::renderJugador(jugador& j){

    if(!j.getActiva()) return;

    QPixmap frame;


    bool enMovimiento = abs(j.getVx()) > 0.1f;


    if(enMovimiento){

        j.sumarTiempoAnim(0.016f);

        if(j.getTiempoAnim() > 0.1f){
            j.setFrameAnim((j.getFrameAnim() + 1) % jugadorRun.size());
            j.setTiempoAnim(0);
        }

        frame = jugadorRun[j.getFrameAnim()];
    }
    else{
        // idle
        j.setFrameAnim(0);
        j.setTiempoAnim(0);

        frame = jugadorIdle[0];
    }


    QGraphicsPixmapItem* item = scene->addPixmap(frame);


    item->setPos(
        j.getX() - frame.width()/2,
        j.getY() - frame.height() + 10
        );

    QTransform t;

    if(!j.estaEnDerecha()){
        t.translate(frame.width(), 0);
        t.scale(-1, 1);
    }
    else{
        t.scale(1, 1);
    }

    item->setTransform(t);

}



void MainWindow::renderEnemigos(vector<enemigo*>& enemigos, jugador& jug){


    for(auto& e : enemigos){

        if(!e || !e->getActiva()) continue;

        if(e->getElite()){


            scene->addEllipse(
                e->getX() - 18,
                e->getY() - 10,
                36, 20,
                QPen(Qt::NoPen),
                QBrush(QColor(180, 0, 255, 100))
                );


            float t = QTime::currentTime().msec() / 200.0;
            float escala = 1.05 + sin(t) * 0.05;


            QGraphicsPixmapItem* glow = scene->addPixmap(frame);

            glow->setPos(
                e->getX() - frame.width()/2,
                e->getY() - frame.height() + 10
                );

            glow->setScale(escala);
            glow->setOpacity(0.4);

            QGraphicsColorizeEffect* color = new QGraphicsColorizeEffect();
            color->setColor(QColor(180, 0, 255));
            color->setStrength(1.0);

            glow->setGraphicsEffect(color);

            QTransform tFlip;

            if(jug.getX() < e->getX()){
                tFlip.translate(frame.width(), 0);
                tFlip.scale(-1, 1);
            }

            glow->setTransform(tFlip);
        }


        if(e->getTipo() == 1){

            QPixmap frame = e->getFrame(zombieIdle, zombieRun);

            QGraphicsPixmapItem* item = scene->addPixmap(frame);


            item->setPos(
                e->getX() - frame.width()/2,
                e->getY() - frame.height() + 10
                );


            QTransform t;

            if(jug.getX() < e->getX()){
                t.translate(frame.width(), 0);
                t.scale(-1, 1);
            }

            item->setTransform(t);



        }
        else if(e->getTipo() == 2){

            QGraphicsPixmapItem* item = scene->addPixmap(imgEsqueleto);

            float x = e->getX() - imgEsqueleto.width()/2;
            float y = e->getY() - imgEsqueleto.height()/2;

            item->setPos(x, y);

            float w = imgEsqueleto.width();

            QTransform t;

            if(jug.getX() > e->getX()){


                t.translate(w, 0);
                t.scale(-1, 1);
            }
            else{
                t.scale(1, 1);
            }

            item->setTransform(t);


        }
        else{


            wither* w = dynamic_cast<wither*>(e);
            if(!w) return;

            QPixmap img;


            if(w->estaEnDash()){
                img = imgWitherDash;


            }
            else if(w->getFase() == 1){
                img = imgWitherFase1;
            }
            else{
                img = imgWitherFase2;
            }

            QGraphicsPixmapItem* item = scene->addPixmap(img);


            item->setPos(
                w->getX() - img.width()/2,
                w->getY() - img.height()/2
                );


            item->setTransformOriginPoint(
                img.width()/2,
                img.height()/2
                );

            QTransform t;

            if(jug.getX() > w->getX()){

                t.translate(img.width(), 0);
                t.scale(-1, 1);
            }
            else{
                t.scale(1, 1);
            }

            item->setTransform(t);



        }




    }
}

void MainWindow::renderPlataformas(vector<plataforma>& plataformas){

    for(auto& plat : plataformas){

        QPixmap scaled = pixPlataforma.scaled(
            plat.getAncho(),
            plat.getAlto()
            );

        scene->addPixmap(scaled)->setPos(
            plat.getX(),
            plat.getY()
            );
    }
}


void MainWindow::renderPociones(std::vector<pocion>& pociones){

    for(auto& p : pociones){

        if(!p.getActiva()) continue;

        QPixmap img;

        switch(p.getTipo()){
        case VIDA: img = imgPocionVida; break;
        case VELOCIDAD: img = imgPocionVelocidad; break;
        case FUERZA: img = imgPocionDanio; break;
        case INMUNIDAD: img = imgPocionInmunidad; break;
        case LENTITUD: img = imgPocionLentitud; break;
        }

        float offsetY = sin(p.tiempoAnim) * 3;

        scene->addPixmap(img)->setPos(p.getX(), p.getY() + offsetY);
    }
}

void MainWindow::renderHUD(nivel* n){

    jugador& j = n->getJugador();

    float x = view->mapToScene(10,10).x();
    float y = view->mapToScene(10,10).y();

    float porcentaje = j.getVida() / 100.0f;

    if(porcentaje < 0) porcentaje = 0;
    if(porcentaje > 1) porcentaje = 1;

    float ancho = 200;
    float alto = 15;


    scene->addRect(x, y, ancho, alto, QPen(), QBrush(Qt::darkGray));


    scene->addRect(x, y, ancho * porcentaje, alto, QPen(), QBrush(Qt::green));

    QString texto = "";

    if(auto np = dynamic_cast<nivelpasillo*>(n)){
        texto = QString("Kills: %1/%2\nTiempo: %3")
        .arg(np->getKills())
            .arg(np->getObjetivoKills())
            .arg((short int)np->getTiempo());
    }

    QGraphicsTextItem* hud = scene->addText(texto);
    hud->setDefaultTextColor(Qt::white);

    hud->setPos(x, y + alto + 5);
}

void MainWindow::renderFondo(nivel* n){



    QPixmap fondo;

    if(n->esPasillo()){
        fondo = QPixmap("://imagenes/candidato_pasillo.jpg");
    }
    else if(n->esTransicion()){
        fondo = QPixmap("://imagenes/candidato_transicion.jpg");
    }
    else if(n->esBoss()){
        fondo = QPixmap("://imagenes/candidato_boss.jpg");
    }

    fondo = fondo.scaled(3000, 600);

    scene->addPixmap(fondo)->setPos(0,0);
}

void MainWindow::sonidoEnemigo(short int tipo){

    switch(tipo){

    case 1:
        sHitZombie->setPosition(0);
        sHitZombie->play();
        break;

    case 2:
        sHitEsqueleto->setPosition(0);
        sHitEsqueleto->play();
        break;

    case 3:{
        short int r = rand() % 2;

        if(r == 0){
            sHitWither1->setPosition(0);
            sHitWither1->play();
        }else{
            sHitWither2->setPosition(0);
            sHitWither2->play();
        }
        break;
    }

    }
}

void MainWindow::sonidoMuerte(short int tipo){

    switch(tipo){

    case 1:
        sMuerteZombie->setPosition(0);
        sMuerteZombie->play();
        break;

    case 2:
        sMuerteEsqueleto->setPosition(0);
        sMuerteEsqueleto->play();
        break;

    case 3:
        sMuerteWither->setPosition(0);
        sMuerteWither->play();
        break;
    }
}

void MainWindow::sonidoDisparo(TipoProyectil tipo){

    if(tipo == ENEMIGO){
        sDisparoEsqueleto->setPosition(0);
        sDisparoEsqueleto->play();
    }

    if(tipo == JEFE){
        sDisparoWither->setPosition(0);
        sDisparoWither->play();
    }
}

void MainWindow::reproducirMusica(QString ruta){

    if(musica->source() == QUrl(ruta)) return;

    musica->setSource(QUrl(ruta));
    musica->setPosition(0);
    musica->play();
}

void MainWindow::actualizarMusica(nivel* n){

    if(!n) return;

    if(n->esBoss()){
        reproducirMusica(musicaBoss);
    }
    else{
        reproducirMusica(musicaPasillo);
    }
}

void MainWindow::renderProyectiles(std::vector<proyectil*>& proyectiles){

    for(auto* p : proyectiles){

        if(!p || !p->getActiva()) continue;

        QPixmap img;


        switch(p->getTipo()){

        case JUGADOR:
            img = imgLanza;
            break;

        case ENEMIGO:
            img = imgFlecha;
            break;

        case JEFE:
            img = imgCraneo;
            break;
        }

        QGraphicsPixmapItem* item = scene->addPixmap(img);


        item->setPos(
            p->getX() - img.width()/2,
            p->getY() - img.height()/2
            );


        if(p->getTipo() != JEFE){

            float vx = p->getVx();
            float vy = p->getVy();

            float angulo = atan2(vy, vx) * 180 / M_PI+45;

            if(p->getTipo() == JUGADOR){
                angulo+=70;
            }

            item->setTransformOriginPoint(img.width()/2, img.height()/2);
            item->setRotation(angulo);
        }
    }
}

void MainWindow::renderPortal(){

    float x = 2240;
    float y = 380;

    QGraphicsPixmapItem* item = scene->addPixmap(imgPortal);

    item->setPos(
        x - imgPortal.width()/2,
        y - imgPortal.height()/2
        );
}
