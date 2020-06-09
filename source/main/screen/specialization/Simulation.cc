

#include "specialization/Simulation.h"

using namespace Screen::Spec;

Simulation::Simulation(unsigned int width, unsigned int height, const ScreenManager& screenManager)
: width_(width),
height_(height),
screen_manager_(screenManager),
framerate(60.0f),
texture_manager_(Draw::Texture::Manager::getInstance()),
font_manager_(Draw::Font::Manager::getInstance()),
loop_synch_(Synch::Loop::create(1))
/*
view_world_(Screen::View::create("World", sf::FloatRect(-(width_ / 2), -(height / 2), width_, height))),
view_UI_(Screen::View::create("UI", sf::FloatRect(0, 0, width_, height))),
world_(std::make_unique<b2World>(b2Vec2( 0.0f, 0.0f ))),
event_manager_(std::make_unique<Event::Manager>(view_UI_)),
draw_manager_(Draw::Manager::create("First_layer", window, view_UI_))*/
{}

Simulation::Simulation(const sf::Vector2u& viewSize, const ScreenManager& screenManager)
: Simulation(viewSize.x, viewSize.y, screenManager)
{}

Simulation::~Simulation() = default;

void Simulation::init(std::shared_ptr<sf::RenderWindow> & window){
    view_UI_ = Screen::View::create("UI", sf::FloatRect(0, 0, width_, height_));
    event_manager_ = std::make_unique<Event::Manager>(view_UI_);
    draw_manager_ = Draw::Manager::create("First_layer", window, view_UI_);
}

void Simulation::release(std::shared_ptr<sf::RenderWindow> & window){
    draw_manager_.release();
    event_manager_.release();
    view_UI_.reset();
}


ScreenID Simulation::run(std::shared_ptr<sf::RenderWindow> & window){
    ScreenID MainMenuID = screen_manager_.getScreenID("MainMenu");

    std::shared_ptr<Event::Basic> ev = std::make_shared<Event::Basic>();

    event_manager_->add("test", Event::Manager::State::ACTIVE, ev);

    window->setView(view_UI_->getView());

    while(window->isOpen()){
        sf::Event event;
        framerate.checkTime();

        while(window->pollEvent(event)){
            event_manager_->checkEvents(*window, event);
        }

        if(ScreenInteface::isAnyoneWaiting()){
            // if someone miss a call then it will be registered in the next frame
            std::lock_guard<std::mutex> guard(lock_loopback_data_);
            // decide what to do with these informations.
            for(auto& it : received_data_->request_for_next_screen_){
                if(it == MainMenuID)
                    return it;
            }
        }
        

        window->clear();
        draw_manager_->drawAll();
        window->display();    
        loop_synch_.enter();
    }

    return ScreenID();
}