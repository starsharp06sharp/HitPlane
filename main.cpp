#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    //Create the main window
    sf::RenderWindow windowMain(sf::VideoMode(240, 400), "Hit Plane By L.Zheng");

    //Create and Play BGM
    sf::Music musicBGM;
    if (!musicBGM.openFromFile("TURKY.WAV"))
    {
        exit -(1);
    }
    musicBGM.setVolume(25);
    musicBGM.setLoop(true);
    musicBGM.play();

    //Main loop
    while (windowMain.isOpen())
    {
        sf::Event event;
        while (windowMain.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowMain.close();
        }

        windowMain.clear();

        //Draw something on the windowMain

        windowMain.display();
    }

    return 0;
}
