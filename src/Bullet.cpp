#include "Bullet.h"

sf::SoundBuffer Bullet::bufferShoot;
sf::Sound Bullet::soundShoot;

Bullet::Bullet(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    sf::Vector2f speed,
    float angle
    ) :
        Moveable(
            aeraToDisplay,
            scale,
            originPos,
            angle
            ),
        speed(speed)
{
    this-> soundShoot.play();
}

void
Bullet::flash( void )
{
    this-> move( speed );
}

bool
Bullet::isDisappear( void )
{
    return ! this-> getGlobalBounds().intersects( sf::FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y) );
}

bool
Bullet::hit(
    sf::FloatRect target
    )
{
    return this-> getGlobalBounds().intersects( target );
}

void
Bullet::initSound( void )
{
    if(!bufferShoot.loadFromFile("./resources/sound/bullet.ogg")) {
        //Exit when sound file is broken
        //system("pause");
        exit(-1);
    }
    soundShoot.setBuffer(bufferShoot);
    soundShoot.setVolume(125);
}
