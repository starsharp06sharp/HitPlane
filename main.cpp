#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    //Create the main window
    sf::RenderWindow windowMain(sf::VideoMode(240, 400), "Hit Plane By L.Zheng");

    //Load Planes's texture from file
    sf::Texture texturePlanes;
    if (!texturePlanes.loadFromFile("Planes.png"))
    {
        //Exit when plane's texture is broken
        exit(-1);
    }

    //Load background from file
     sf::Texture textureBackground;
     if (!textureBackground.loadFromFile("Background.png"))
    {
        //Exit when plane's texture is broken
        exit(-1);
    }

    //Create and Play BGM
    sf::Music musicBGM;
    if (!musicBGM.openFromFile("TURKY.WAV"))
    {
        //Exit when music file is broken
        exit -(1);
    }
    musicBGM.setVolume(25);
    musicBGM.setLoop(true);
    musicBGM.play();

    //TEMP player
    sf::Sprite planePlayer;
    planePlayer.setTexture(texturePlanes);
    planePlayer.setTextureRect(sf::IntRect(0, 99, 102, 126));
    planePlayer.setScale(sf::Vector2f(0.5f, 0.5f));
    planePlayer.setOrigin(sf::Vector2f(-190.f, -670.f));

    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));

    //Main loop
    while (windowMain.isOpen())
    {
        sf::Event event;
        while (windowMain.pollEvent(event))
        {
            //Close window when exit
            if (event.type == sf::Event::Closed)
                windowMain.close();
        }

        windowMain.clear();

        //draw
        windowMain.draw(spriteBackground);
        windowMain.draw(planePlayer);

        windowMain.display();
    }

    return 0;
}
