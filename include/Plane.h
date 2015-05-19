#ifndef PLANE_H
#define PLANE_H

#include "Moveable.h"

class Plane : public Moveable {
public:
    Plane(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    int
    judgeOutOfBorder( void );

    void
    shoot( void );

protected:

private:

    int life;

};

#endif // PLANE_H
