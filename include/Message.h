#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include "constDef.h"

namespace Pos{
    enum {
        Top = 0,
        Vmiddle = 1,
        Bottom = 2,
        Left = 0 * 3,
        Hmiddle = 1 * 3,
        Right = 2 * 3
    };
};

namespace Driect{
    enum {
        Up,
        Down,
        Left,
        Right
    };
};


class Message : public sf::Text {
public:

    Message(
        const wchar_t* str,
        sf::Font& font,
        int size,
        sf::Color color,
        int position
        );

    Message(
        const wchar_t* str,
        sf::Font& font,
        int size,
        sf::Color color,
        int driection,
        Message& reference
        );

protected:
private:
};

#endif // MESSAGE_H
