#include "Enemies.h"

Enemies::Enemies() :
    enemy1Counter( 0 ),
    enemy2Counter( 0 )
{
    Enemy::clearBullet();
}

void
Enemies::addEnemy( void )
{
    //Create enemy1
    if( enemy1Counter == 120 ) {
        enemies.push_back(
            Enemy(
                enemy1,
                sf::Vector2f(SCALE, SCALE),
                sf::Vector2f( rand()% (int)(WINDOW_SIZE_X - 57 * SCALE), 0)
                )
            );
        enemy1Counter = 0;
    }
    enemy1Counter++;

    //Create enemy2
    if ( enemy2Counter == 600 ) {
        enemies.push_back(
            Enemy(
                enemy2,
                sf::Vector2f(SCALE, SCALE),
                sf::Vector2f( rand()% (int)(WINDOW_SIZE_X - 69 * SCALE), 0)
                )
            );
        enemy2Counter = 0;
    }
    enemy2Counter++;
}

void
Enemies::flashAll(
    Player& player
    )
{
    //Flash enemy
    for( auto &enemy : enemies ){
        enemy.flash();
    }

    //Enemy shoot
    for( auto &enemy : enemies ){
        enemy.shoot(player.getCenter());
    }
    //Flash enemy'sAmmo
    Enemy::flashAmmo();
}

unsigned
Enemies::judge(
    Player& player
    )
{
    unsigned score = 0;
    //Mark all hited planes
    for( auto &enemy : this->enemies ){
        if ( player.hitEnemy( enemy ) ) {
            enemy.getHit();
            if ( enemy.isDead() ) {
                score+=deadScore [ enemy.getEnemyNo() ];
            }
        }
    }

    //Destory all marked planes
    enemies.remove_if(
        std::mem_fun_ref(&Enemy::isDisappear)
        );
    return score;
}

bool
Enemies::hit(
    Player& player
    )
{
    return Enemy::hitPlayer( player );
}

void
Enemies::draw(
    sf::RenderWindow& window
    )
{
    for( auto &enemy : enemies ){
        window.draw( enemy );
    }
}
