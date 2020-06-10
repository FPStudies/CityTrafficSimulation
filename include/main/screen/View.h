/*
 * View.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_VIEW_H
#define TRAFFIC_SIM_MAIN_SCREEN_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace ScreenMaster{

class View{
    sf::View view_;
    std::string name_;

    View(const std::string& name, const sf::FloatRect& rect);

public:
    static std::shared_ptr<View> create(const std::string& name, const sf::FloatRect& rect);
    ~View();

    sf::View& getView();
    const sf::View& getView_const() const;

    std::string& getName();
    const std::string& getName() const;

    void reset(const sf::FloatRect& rect);

};

}

#endif
