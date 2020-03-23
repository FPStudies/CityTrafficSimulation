#ifndef GRAPHIC_LIBRARY_FACADE_H
#define GRAPHIC_LIBRARY_FACADE_H

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class GraphicFacade {
public:

    void print(){
        std::cout << "graphic_facade" << std::endl;
    }
};

#endif