#ifndef SKY_H
#define SKY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <ctime>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"


class Sky : public sf::RenderWindow {
public:

    Sky();

    bool showStartInterface( void );

    void mainLoop( void );

    bool showGameOverInterface( void );

protected:

private:

    sf::Texture textureBackground;

    sf::Sprite spriteBackground;

    void initBackground( void );

    sf::Music musicBGM;

    void initMusic( void );

    sf::Font promptFont;

    sf::Font scoreFont;

    sf::Font yaheiFont;

    void initFont( void );

};

#endif // SKY_H
