#include "Bullet.h"

sf::SoundBuffer Bullet::bufferShoot;
sf::Sound Bullet::soundShoot;

Bullet::Bullet(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    sf::Vector2f speed
    ) :
        Moveable(
            aeraToDisplay,
            scale,
            originPos
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
    return ! this-> getGlobalBounds().intersects( sf::FloatRect(0.f, 0.f, 240.f, 400.f) );
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
    if(!bufferShoot.loadFromFile("bullet.ogg")) {
        //Exit when sound file is broken
        system("pause");
        exit(-1);
    }
    soundShoot.setBuffer(bufferShoot);
    soundShoot.setVolume(125);
}
