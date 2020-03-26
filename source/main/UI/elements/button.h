#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "elementObserver.h"
#include "textBox.h"
#include "../action/actionInterface.h"

class Button: public ElementObserver, public TextBox{
    std::list<std::shared_ptr<ActionInterface>> action;
 
public:
    Button(const uint& width, const uint& height, const uint& posX, const uint& posY, const std::string& text, const std::string& pathToFont);
    Button(const uint& width, const uint& height, const uint& posX, const uint& posY, const sf::Text& text, const sf::Font& font);
    Button(const uint& width, const uint& height, const uint& posX, const uint& posY);
    Button(const uint& width, const uint& height);
    virtual ~Button();
    Button(const Button&) = delete;

    virtual void update(sf::Event event);   // run an action it it was binded

    virtual bool overlap(const ElementObserver& box);
    virtual bool mousePoints();

    void bind(const ActionInterface& action); // can add multiple actions
};


#endif