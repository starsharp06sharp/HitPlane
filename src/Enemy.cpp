#include "Enemy.h"

sf::SoundBuffer Enemy::bufferExplode[3];
sf::Sound Enemy::soundExplode[3];

std::list<Bullet> Enemy::ammo;

Enemy::Enemy(
    enemyStyle enemyNo,
    sf::Vector2f scale,
    sf::Vector2f originPos
    ) :
        enemyNo( enemyNo ),
        Plane(
            livePlaneToDisplay [ enemyNo ] [ maxLife [ enemyNo ] ],//aeraToDisplay
            scale,
            originPos,
            maxLife [ enemyNo ]//life
            ),
        speed(
            sf::Vector2f(0, 0.3)
            ),
        deadCounter( 0 ),
        disappear( false )
{
    //Do nothing
}

void
Enemy::flash( void )
{
    if ( deadCounter <= 0 ) {
        this-> move(speed);
        if ( this-> judgeOutOfBorder() >= 6 ) this-> disappear = true;
    } else {
        if (deadDelayConuter == deadDelaySpeed[enemyNo]) {
            this-> setTextureRect(
                deadPlaneToDisplay [enemyNo] [deadCounter]
                );
            if( deadCounter++ > 4 ) this-> disappear = true;
        deadDelayConuter=0;
        } else deadDelayConuter++;
    }
}

void
Enemy::getHit( void )
{
    life--;
    if ( life > 0 ) {
        this-> setTextureRect(
            livePlaneToDisplay [enemyNo] [life]
            );
    } else if ( life == 0 ) {
        deadCounter = 1;
        soundExplode[enemyNo].play();
        deadDelayConuter = 0;
    }
}

bool
Enemy::isDisappear( void )
{
    return disappear;
}

void
Enemy::initSound( void )
{
    char soundFileName[] = "enemy1_down.ogg";
    for (int i = enemy1;
           i <= enemy2;
           i++
          )
    {
        soundFileName[5] = '1' + i;
        if( !bufferExplode[i].loadFromFile(soundFileName) ) {
            //Exit when sound file is broken
            system("pause");
            exit(-1);
        }
        soundExplode[i].setBuffer(bufferExplode[i]);
        soundExplode[i].setVolume(100);
    }
}

enemyStyle
Enemy::getEnemyNo( void )
{
    return enemyNo;
}

bool
Enemy::isDead( void )
{
    return ( life <= 0 );
}
