#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"


class Enemies {
public:
    Enemies();

    void
    addEnemy( unsigned level );

    void
    flashAll(
        Player& player
        );

    bool
    hit(
        Player& player
        );

    unsigned
    judge(
        Player& player
        );

    void
    draw(
        sf::RenderWindow& window
        );

protected:

private:

    std::list<Enemy> enemies;

    unsigned enemy1Counter;

    unsigned enemy2Counter;

};

#endif // ENEMIES_H
