#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include <cmath>
#include "Player.h"
#include "Plane.h"
#include "Bullet.h"

enum enemyStyle {
    enemy1,
    enemy2
    //,enemy3
};

const int deadScore[] = { 1, 10, 100 };

class Player;

class Enemy : public Plane {
public:

    Enemy(
        enemyStyle enemyNo,
        sf::Vector2f scale,
        sf::Vector2f originPos
    );

    static void
    initSound( void );

    static void
    clearBullet( void );

    enemyStyle
    getEnemyNo( void );

    void
    move(
        sf::Vector2f speed
        );

    void
    flash( void );

    void
    getHit( void );

    void
    shoot(
        sf::Vector2f targetPosition
        );

    static bool
    hitPlayer( Player& player );

    static void
    flashAmmo( void );

    static void
    drawAllBullet( sf::RenderWindow& window );

protected:

private:

    enemyStyle enemyNo;

    static std::list<Bullet> ammo;

    int deadCounter;
    /*
    *This counter repesents the different stage of dead plane:
    *When it is 0, the plane is alive
    *When it is a num>0 ,it means the picture NO that is putting on the screen now.
    */

    int deadDelayConuter;
    /*
    *This counter can control the speed of explode action.
    *Every to number play one frame.
    */

    int shootCounter;
    /*
    *This counter control the shoot frequency of the enemy.
    *The frequency depends on the array shootInterval[]
    */

    static sf::SoundBuffer bufferExplode[3];

    static sf::Sound soundExplode[3];

};

#endif // ENEMY_H
