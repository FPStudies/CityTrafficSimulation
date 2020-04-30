/*
 * GraphicLibraryFacade.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef GRAPHIC_LIBRARY_FACADE_CPP
#define GRAPHIC_LIBRARY_FACADE_CPP

#include "GraphicLibraryFacade.h"

void GraphicFacade::test(){
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML test");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while(window.isOpen()){

            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();    
        }
    }

#endif
