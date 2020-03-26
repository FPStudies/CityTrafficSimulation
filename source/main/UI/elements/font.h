#ifndef FONT_H
#define FONT_H

/*
Proxy
To not copy element if it is not necessary.
*/

#include <SFML/Graphics.hpp>
#include <memory>

class Font{
    std::shared_ptr<sf::Font> font;

public:
    Font();
    ~Font();
    ~Font();

    bool loadFromFile(const std::string &filename);
    bool loadFromMemory(const void *data, std::size_t sizeInBytes);
    bool loadFromStream(sf::InputStream &stream);
    const sf::Font::Info& getInfo() const;
    const sf::Glyph & getGlyph (sf::Uint32 codePoint, unsigned int characterSize, bool bold, float outlineThickness=0) const;
    float getKerning (sf::Uint32 first, sf::Uint32 second, unsigned int characterSize) const;
    float getLineSpacing (unsigned int characterSize) const;
    float getUnderlinePosition (unsigned int characterSize) const;
    float getUnderlineThickness (unsigned int characterSize) const;
    const sf::Texture & getTexture (unsigned int characterSize) const;
    
    Font & operator= (const Font &right);

    std::shared_ptr<sf::Font> clone();
};

#endif