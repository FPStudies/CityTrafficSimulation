/*
 * Button.h
 *
 *      Author: Kordowski Mateusz
 */
 
#ifndef TRAFFIC_SIM_BUTTON_H
#define TRAFFIC_SIM_BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "ElementObserver.h"
#include "TextBox.h"
#include "../action/ActionInterface.h"

class Button: public ElementObserver, public TextBox{
    std::list<std::shared_ptr<ActionInterface>> action;
 
public:
    Button(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const std::string& text, const std::string& path_to_font);
    Button(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const sf::Text& text, const sf::Font& font);
    Button(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y);
    Button(const uint& width, const uint& height);
    virtual ~Button();
    Button(const Button&) = delete;

    virtual void update(sf::Event event);   // run an action it it was binded

    virtual bool overlap(const ElementObserver& box);
    virtual bool mousePoints();

    void bind(const ActionInterface& action); // can add multiple actions
};


#endif
