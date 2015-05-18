#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>

#include "Moveable.h"

sf::Vector2f
getStepFromKeyboardEvent(
    sf::Event keyEvent
    );

int main() {
    //Create the main window
    sf::RenderWindow windowMain(sf::VideoMode(240, 400), "HitPlane By L.Zheng");

    //Load background from file
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("Background.png")) {
        //Exit when plane's texture is broken
        system("pause");
        exit(-1);
    }

    //Create and Play BGM
    sf::Music musicBGM;
    if (!musicBGM.openFromFile("TURKY.WAV")) {
        //Exit when music file is broken
        system("pause");
        exit (-1);
    }
    musicBGM.setVolume(25);
    musicBGM.setLoop(true);
    musicBGM.play();

    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));

    //Inital moveable object's texture
    Moveable::initTexturePlanes();
    //TEMP player
    Moveable player(
        sf::IntRect(0, 99, 102, 126),
        sf::Vector2f(0.5f, 0.5f),
        //sf::Vector2f(-190.f, -670.f)
        sf::Vector2f(96.f, 336.f)
        //sf::Vector2f(0, 0)
        );

    //Main loop
    while (windowMain.isOpen()) {
        sf::Event event;
        while (windowMain.pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                windowMain.close();
            }

            //Move player's plane when key preessed
            if (event.type == sf::Event::KeyPressed) {
                player.move(
                    getStepFromKeyboardEvent( event )
                    );
                sf::Vector2f pos = player.getPosition();
                std::cout<<'('<<pos.x<<','<<pos.y<<')'<<std::endl;
            }
        }

        windowMain.clear();

        //draw
        windowMain.draw(spriteBackground);
        windowMain.draw(*(sf::Sprite*)&player);

        windowMain.display();
    }

    return 0;
}

sf::Vector2f
getStepFromKeyboardEvent(
    sf::Event keyEvent
    )
{
    sf::Vector2f step;

    switch(keyEvent.key.code) {
    case sf::Keyboard::Up :
        step = sf::Vector2f(0, -16);
        break;

    case sf::Keyboard::Down :
        step = sf::Vector2f(0, 16);
        break;

    case sf::Keyboard::Left :
        step = sf::Vector2f(-16, 0);
        break;

    case sf::Keyboard::Right :
        step = sf::Vector2f(16, 0);
        break;
    }

    return step;
}
