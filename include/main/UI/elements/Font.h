/*
 * Font.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_FONT_H
#define TRAFFIC_SIM_FONT_H

/*
Proxy
To not copy element if it is not necessary.
*/

#include <SFML/Graphics.hpp>
#include <memory>

class Font{
    std::shared_ptr<sf::Font> font_;

public:
    Font();
    ~Font();
    ~Font();

    bool loadFromFile(const std::string &file_name);
    bool loadFromMemory(const void *data, std::size_t size_in_bytes);
    bool loadFromStream(sf::InputStream &stream);
    const sf::Font::Info& getInfo() const;
    const sf::Glyph & getGlyph (sf::Uint32 code_point, unsigned int character_size, bool bold, float outline_thickness=0) const;
    float getKerning (sf::Uint32 first, sf::Uint32 second, unsigned int character_size) const;
    float getLineSpacing (unsigned int character_size) const;
    float getUnderlinePosition (unsigned int character_size) const;
    float getUnderlineThickness (unsigned int character_size) const;
    const sf::Texture & getTexture (unsigned int character_size) const;
    
    Font & operator= (const Font &right);

    std::shared_ptr<sf::Font> clone();
};

#endif
