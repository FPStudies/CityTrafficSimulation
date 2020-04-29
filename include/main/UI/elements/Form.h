/*
 * Form.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_FORM_H
#define TRAFFIC_SIM_FORM_H

/*
Trzeba stworzyć własny sposób na to, aby wpisywany tekst wyswietlał się w formularzu.
Można to zrobić aktualizując obiekt po naciśnięciu jakiegoś znaku.
Trzeba móc wiedzieć kiedy obiekt jest zaznaczony i przekierować event naciśnięcia klawisza 
sf::Event::TextEntered; event.text.unicode
*/

#include <SFML/Graphics.hpp>

#include "ElementObserver.h"
#include "TextBox.h"

class Form: public ElementObserver, public TextBox{
    bool already_used_; // to have a nice, welcome message at the beginning

public:
    Form(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const std::string& text, const std::string& path_to_font);
    Form(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const sf::Text& text, const sf::Font& font);
    Form(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y);
    Form(const uint& width, const uint& height);
    virtual ~Form();
    Form(const Form&) = delete;

    virtual void update(sf::Event event);

    virtual bool overlap(const ElementObserver& box);
    virtual bool mousePoints();
};


#endif