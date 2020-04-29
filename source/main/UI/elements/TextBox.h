/*
 * TextBox.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TEXT_BOX_H
#define TRAFFIC_SIM_TEXT_BOX_H

#include "Font.h"
#include "Box.h"

class TextBox: public Box{
    sf::Text text;
    Font font;

public:
    TextBox(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const std::string& text, const std::string& path_to_font);
    TextBox(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y, const sf::Text& text, const Font& font);
    TextBox(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y);
    TextBox(const uint& width, const uint& height);
    virtual ~TextBox();
    TextBox(const TextBox&);

    virtual bool setPosition(const uint& pos_X, const uint& pos_Y);
    virtual void draw();
    Font& getFont() const;
    sf::Text& getText() const;

    void setText(const std::string& text);
    void setColor(const sf::Color& color);
    void setFont(const Font& font)
};

#endif
