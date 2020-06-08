

#include "specialization/MainMenu.h"


using namespace Screen::Spec;


MainMenu::MainMenu(unsigned int width, unsigned int height, std::shared_ptr<sf::RenderWindow> & window, const ScreenManager& screenManager)
: width_(width),
height_(height),
screen_manager_(screenManager),
framerate(60.0f),
texture_manager_(Draw::Texture::Manager::getInstance()),
font_manager_(Draw::Font::Manager::getInstance()),
loop_synch_(Synch::Loop::create(1)),
view_UI_(Screen::View::create("UI", sf::FloatRect(0, 0, width_, height))),
event_manager_(std::make_unique<Event::Manager>(view_UI_)),
draw_manager_(Draw::Manager::create("First_layer", window, view_UI_)),
exit_button_(nullptr),
background_(nullptr)
{}

MainMenu::MainMenu(const sf::Vector2u& viewSize, std::shared_ptr<sf::RenderWindow> & window, const ScreenManager& screenManager)
: MainMenu(viewSize.x, viewSize.y, window, screenManager)
{}


MainMenu::~MainMenu() = default;


void MainMenu::addButtons(std::shared_ptr<sf::RenderWindow> & window){
    exit_button_ = std::make_shared<Button::Exit>(*window, texture_manager_.get("blue_light"));
    exit_button_->setFont(font_manager_.get("Normal"));
    exit_button_->setSize(sf::Vector2f(100, 100));
    auto buttonSize = exit_button_->getSize();
    exit_button_->setPosition(sf::Vector2f(width_ / 2 - (buttonSize.x / 2), height_ / 2 - ((buttonSize.y))));

    auto trigger_button_event = Trigger::Event::Button::create();
    Trigger::Event::Button::connect(exit_button_, trigger_button_event);

    std::shared_ptr<Event::Control> event_control = std::make_shared<Event::Control>();
    event_control->getMapping().addControl(Control::Mouse::ButtonLeft, trigger_button_event);
    event_control->getMapping().addControl(Control::Mouse::ButtonRight, trigger_button_event);

    event_manager_->addNew("test_button", Event::Manager::State::ACTIVE, event_control); 
    draw_manager_->addEntity("First_layer", exit_button_);



    sim_button_ = std::make_shared<Button::Default>(*window, texture_manager_.get("blue_light"));
    sim_button_->setFont(font_manager_.get("Normal"));
    sim_button_->setSize(sf::Vector2f(100, 100));
    sim_button_->getText().setString("Start");
    sim_button_->getText().setCharacterSize(34);
    sim_button_->getText().setFillColor(sf::Color::Red);
    buttonSize = sim_button_->getSize();
    sim_button_->setPosition(sf::Vector2f(width_ / 2 - (buttonSize.x / 2), height_ / 3 - ((buttonSize.y))));

    std::shared_ptr<Trigger::Action::NextScreen> trig_next_screen = std::make_shared<Trigger::Action::NextScreen>(screen_manager_.getScreenID("Simulation"));
    sim_button_->addTriggerOnReleased(trig_next_screen);

    auto trigger_button_event_next = Trigger::Event::Button::create();
    Trigger::Event::Button::connect(sim_button_, trigger_button_event_next);

    

    event_control->getMapping().addControl(Control::Mouse::ButtonLeft, trigger_button_event_next);
    event_control->getMapping().addControl(Control::Mouse::ButtonRight, trigger_button_event_next);

    event_manager_->addNew("test_button", Event::Manager::State::ACTIVE, event_control); 
    draw_manager_->addEntity("First_layer", sim_button_);

}

void MainMenu::addBackground(std::shared_ptr<sf::RenderWindow> & window){
    draw_manager_->addLayerBefore("First_layer", "Second_layer", view_UI_);
    background_ = std::make_shared<Tiles::Background>(texture_manager_.get("grey"));
    draw_manager_->addEntity("Second_layer", background_);
    background_->setSize(sf::Vector2f(width_, height_));
    background_->setPosition(sf::Vector2f(0, 0));
}

void MainMenu::addOther(){
    std::shared_ptr<Event::Basic> ev = std::make_shared<Event::Basic>();

    event_manager_->add("test", Event::Manager::State::ACTIVE, ev);
}

ScreenID MainMenu::run(std::shared_ptr<sf::RenderWindow> & window){
    addBackground(window);
    addButtons(window);
    addOther();


    ScreenID symulationID = screen_manager_.getScreenID("Simulation");

    window->setView(view_UI_->getView());

    while(window->isOpen()){
        sf::Event event;
        framerate.checkTime();

        while(window->pollEvent(event)){
            event_manager_->checkEvents(*window, event);
        }

        if(ScreenInteface::isAnyoneWaiting()){
            // decide what to do with these informations.
            for(auto& it : received_data_->request_for_next_screen_){
                return it;
            }
        }
        

        window->clear();
        draw_manager_->drawAll();
        window->display();    
    }

    return ScreenID();
}