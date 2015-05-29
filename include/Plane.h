#ifndef PLANE_H
#define PLANE_H

#include "Moveable.h"

class Plane : public Moveable {
public:

    Plane() {}

    Plane(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    int
    judgeOutOfBorder( void );

protected:

    int life;

    bool disappear;


private:

};

#endif // PLANE_H
