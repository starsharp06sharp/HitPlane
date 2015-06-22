#include "Message.h"

Message::Message(
    const wchar_t* str,
    sf::Font& font,
    int size,
    sf::Color color,
    int position
    )
{
    this->setFont( font );
    this->setCharacterSize( size );
    this->setColor( color );
    this->setString( str );

    sf::Vector2f coord;
    switch( position%3 ){//vertical
    case 0://top
        coord.y = 0;
        break;
    case 1://middle
        coord.y = WINDOW_SIZE_Y / 2 - this->getGlobalBounds().height / 2;
        break;
    case 2://bottom
        coord.y = WINDOW_SIZE_Y - this->getGlobalBounds().height;
        break;
    }
    switch( (int)(position/3) ){//horizontal
    case 0://left
        coord.x = 0;
        break;
    case 1://middle
        coord.x = WINDOW_SIZE_X / 2 - this->getGlobalBounds().width / 2;
        break;
    case 2://right
        coord.x = WINDOW_SIZE_X - this->getGlobalBounds().width;
        break;
    }
    this->setPosition( coord );
}

Message::Message(
    const wchar_t* str,
    sf::Font& font,
    int size,
    sf::Color color,
    int driection,
    Message& reference
    )
{
    this->setFont( font );
    this->setCharacterSize( size );
    this->setColor( color );
    this->setString( str );

    sf::Vector2f coord;
    switch( driection ){//horizontal
    case Driect::Up:
    case Driect::Down:
        coord.x = reference.getGlobalBounds().left + reference.getGlobalBounds().width / 2 - this->getGlobalBounds().width / 2;
        break;
    case Driect::Left:
        coord.x = reference.getGlobalBounds().left - this->getGlobalBounds().width;
        break;
    case Driect::Right:
        coord.x = reference.getGlobalBounds().left + reference.getGlobalBounds().width;
        break;
    }
    switch( driection ){//vertical
    case Driect::Left:
    case Driect::Right:
        coord.y = reference.getGlobalBounds().top + reference.getGlobalBounds().height / 2 - this->getGlobalBounds().height / 2;
        break;
    case Driect::Up:
        coord.y = reference.getGlobalBounds().top - this->getGlobalBounds().height;
        break;
    case Driect::Down:
        coord.y = reference.getGlobalBounds().top + reference.getGlobalBounds().height;
    }
    this->setPosition( coord );
}
