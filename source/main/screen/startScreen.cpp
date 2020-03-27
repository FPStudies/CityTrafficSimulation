#ifndef START_SCREEN_CPP
#define START_SCREEN_CPP

#include "startScreen.h"

StartScreen::StartScreen() 
: ScreenInteface()
{}

StartScreen::~StartScreen() {}

ScreenID StartScreen::run(sf::RenderWindow & window){
    EventManager eventManager;
    BasicEvents ev;

    eventManager.add("test", EventManager::State::Active, ev);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            eventManager.checkEvents(window, event);
        }

        window.clear();
        window.display();    
    }
}


#endif