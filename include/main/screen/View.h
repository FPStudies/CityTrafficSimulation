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

/**
 * @brief Store an view with a name. A sf::View can be changed but it will affect all the objects that 
 * store this View. Because of that is is easy to change view for a group of objects.
 * 
 */
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

    /**
     * @brief Utwórz nowy widok z określonymi granicami.
     * 
     * @param rect 
     */
    void reset(const sf::FloatRect& rect);

};

}

#endif
