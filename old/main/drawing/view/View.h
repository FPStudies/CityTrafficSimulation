/*
 * View.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAW_VIEW_VIEW_H
#define TRAFFIC_SIM_MAIN_DRAW_VIEW_VIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../../utility/SharedResourceManager.hpp"

namespace Draw::View{

class View: public ::SharedResource::Resource<sf::View>{
    friend class Manager;

    sf::IntRect portion_;
    bool request_for_deleting;

    View();
    View(const sf::View& texture);
};

}

#endif
