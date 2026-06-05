#ifndef ENTIDAD_H
#define ENTIDAD_H

class entidad{
protected:
    float x, y;
    float vx, vy;
    short int vida;
    bool activa;

public:

    entidad(float x=0, float y=0, short int vida=100);

    virtual ~entidad();

    virtual void update();

    void mover();

    virtual void recibirDanio(short int d);

    bool estavivo();

    float getY();
    float getX();
    short int getVida();
    bool getActiva();
    float getVy();
    float getVx();


    void setX(float nx);
    void setY(float ny);

    void setVelocidad(float nvx, float nvy);
    void setVy(float Vy);


    void setVida(short int v);
    void setActiva(bool a);



};

#endif // ENTIDAD_H
