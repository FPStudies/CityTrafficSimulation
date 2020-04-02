#ifndef ZPR_TRAFFIC_SIM_TEXT_BOX_H
#define ZPR_TRAFFIC_SIM_TEXT_BOX_H

#include "font.h"
#include "box.h"

class TextBox: public Box{
    sf::Text text;
    Font font;

public:
    TextBox(const uint& width, const uint& height, const uint& posX, const uint& posY, const std::string& text, const std::string& pathToFont);
    TextBox(const uint& width, const uint& height, const uint& posX, const uint& posY, const sf::Text& text, const Font& font);
    TextBox(const uint& width, const uint& height, const uint& posX, const uint& posY);
    TextBox(const uint& width, const uint& height);
    virtual ~TextBox();
    TextBox(const TextBox&);

    virtual bool setPosition(const uint& posX, const uint& posY);
    virtual void draw();
    Font& getFont() const;
    sf::Text& getText() const;

    void setText(const std::string& text);
    void setColor(const sf::Color& color);
    void setFont(const Font& font)
};

#endif