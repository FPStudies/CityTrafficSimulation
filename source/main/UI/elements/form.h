#ifndef FORM_H
#define FORM_H

/*
Trzeba stworzyć własny sposób na to, aby wpisywany tekst wyswietlał się w formularzu.
Można to zrobić aktualizując obiekt po naciśnięciu jakiegoś znaku.
Trzeba móc wiedzieć kiedy obiekt jest zaznaczony i przekierować event naciśnięcia klawisza 
sf::Event::TextEntered; event.text.unicode
*/

#include <SFML/Graphics.hpp>

#include "elementObserver.h"
#include "textBox.h"

class Form: public ElementObserver, public TextBox{
    bool alreadyUsed; // to have a nice, welcome message at the beginning

public:
    Form(const uint& width, const uint& height, const uint& posX, const uint& posY, const std::string& text, const std::string& pathToFont);
    Form(const uint& width, const uint& height, const uint& posX, const uint& posY, const sf::Text& text, const sf::Font& font);
    Form(const uint& width, const uint& height, const uint& posX, const uint& posY);
    Form(const uint& width, const uint& height);
    virtual ~Form();
    Form(const Form&) = delete;

    virtual void update(sf::Event event);

    virtual bool overlap(const ElementObserver& box);
    virtual bool mousePoints();
};


#endif