#ifndef SKY_H
#define SKY_H

#undef __STRICT_ANSI__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <list>
#include <ctime>
#include <iostream>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemies.h"
#include "Message.h"

class Sky : public sf::RenderWindow {
public:

    Sky();

    bool
    showStartInterface( void );

    bool
    mainLoop( void );

protected:

private:

    void
    pause(
        Enemies& enemies,
        Player& player
        );

    bool
    showGameOverInterface(
        Enemies& enemies,
        Player& player
        );

    sf::Texture textureBackground;

    sf::Sprite spriteBackground;

    void
    initBackground( void );

    sf::Music musicBGM;

    sf::SoundBuffer bufferLvlup;

    sf::Sound soundLvlup;

    void
    initMusic( void );

    sf::Font promptFont;

    sf::Font scoreFont;

    sf::Font yaheiFont;

    void
    initFont( void );

    void
    resize(
        int newX,
        int newY
        );

    Message
    getScore( void );

    Message
    getLife(
        int life
        );

    unsigned long long score;
    unsigned level;

    Message
    getLevel( void );

    void
    drawGameInterface(
        Enemies& enemies,
        Player& player
        );
};

#endif // SKY_H
