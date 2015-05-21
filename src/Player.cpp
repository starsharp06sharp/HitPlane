#include "Player.h"

Player::Player(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    int life
    ) :
        Plane(
            aeraToDisplay,
            scale,
            originPos,
            life
            )
{
    //Do nothing
}

void
Player::shoot( void )
{
    ammo.push_back(
        Bullet(
            sf::IntRect(69, 78, 9, 21),
            sf::Vector2f(0.5f, 0.5f),
            this-> getPosition() + sf::Vector2f(24.f, -10.f),
            sf::Vector2f(0, -5)
            )
        );
}

void
Player::flash( void )
{
    std::for_each(
        ammo.begin(),
        ammo.end(),
        std::mem_fun_ref(&Bullet::flash)
        );
    ammo.remove_if(
        []( Bullet& bullet ) {return bullet.isDisappear();}
        );
    std::cout<<ammo.size()<<std::endl;
}

void
Player::draw(
    sf::RenderWindow& window
    )
{
    window.draw(*this);
    std::for_each(
        ammo.begin(),
        ammo.end(),
        //std::bind1st(std::mem_fun1_ref(&sf::RenderWindow::draw),window)
        [&]( Bullet& bullet ) {window.draw(bullet);}
        );
//    std::list<Bullet>::iterator it = ammo.begin();
//    for (; it != )
}
