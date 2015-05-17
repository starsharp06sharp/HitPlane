#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>

#include "Moveable.h"

int main() {
    //Moveable::initTexturePlanes();
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
        exit -(1);
    }
    musicBGM.setVolume(25);
    musicBGM.setLoop(true);
    musicBGM.play();

    //TEMP player
    Moveable player(
        sf::IntRect(0, 99, 102, 126),
        sf::Vector2f(0.5f, 0.5f),
        sf::Vector2f(-190.f, -670.f)
    );

    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));

    //Main loop
    while (windowMain.isOpen()) {
        sf::Event event;
        while (windowMain.pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                windowMain.close();
            }

            //Move player's plane when key preessed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                player.move(sf::Vector2f(-16, 0));
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                player.move(sf::Vector2f(16, 0));
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                player.move(sf::Vector2f(0, -16));
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                player.move(sf::Vector2f(0, 16));
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
