#ifndef START_SCREEN_CPP
#define START_SCREEN_CPP

#include <memory>

#include "startScreen.h"

StartScreen::StartScreen() 
: ScreenInteface()
{}

StartScreen::~StartScreen() {}

ScreenID StartScreen::run(std::shared_ptr<sf::RenderWindow> & window){
    EventManager eventManager;
    std::shared_ptr<BasicEvents> ev = std::make_shared<BasicEvents>();
    DrawManager drawManager = std::move(DrawManager::create("First layer", window));

    eventManager.add("test", EventManager::State::Active, ev);

    sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));

    sf::RectangleShape rectangle(sf::Vector2f(200, 40));
    rectangle.setPosition(sf::Vector2f(100, 200));

    window->setView(view);

    while(window->isOpen()){
        sf::Event event;

        while(window->pollEvent(event)){
            eventManager.checkEvents(*window, event);
        }

        window->clear();
        
        window->draw(rectangle);

        window->display();    
    }

    return ScreenID();
}


#endif