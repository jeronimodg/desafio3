#ifndef NIVELTRANSICION_H
#define NIVELTRANSICION_H
#include "nivel.h"
class niveltransicion : public nivel{
private:
    float finNivelX;

public:
    niveltransicion(Dificultad d);

    void update(float dt) override;
    bool verificarWin() override;
    bool verificarLose() override;

    bool esTransicion() override;

    void spawn() override;

    ~niveltransicion();

};

#endif // NIVELTRANSICION_H
