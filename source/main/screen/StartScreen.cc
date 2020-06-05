/*
 * ScreenManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_START_SCREEN_CC
#define TRAFFIC_SIM_START_SCREEN_CC

#include "StartScreen.h"

StartScreen::StartScreen() 
: ScreenInteface(), 
world_(),
event_manager_(),
view_world_(),
texture_manager_(Draw::Texture::Manager::getInstance()),
font_manager_(Draw::Font::Manager::getInstance()),
draw_manager_()
{}

StartScreen::~StartScreen() = default;

static const std::string LAYER_NAME = "First_layer";

void StartScreen::setBox2D(){
    world_ = std::make_unique<b2World>(b2Vec2( 0.0f, -10.0f ));

    b2BodyDef ground_body_def;
	ground_body_def.position.Set(0.0f, 0.0f);
    ground_body_def.type = b2_staticBody;


	b2Body* ground_body = world_->CreateBody(&ground_body_def);

	b2PolygonShape ground_box;

	ground_box.SetAsBox(200.0f, 1.0f);

	ground_body->CreateFixture(&ground_box, 0.0f);

    b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position.Set(0.0f, 200.0f);
	b2Body* body = world_->CreateBody(&body_def);

	b2PolygonShape dynamic_box;
	dynamic_box.SetAsBox(200.0f, 40.0f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &dynamic_box;
	fixture_def.density = 1.0f;
	fixture_def.friction = 0.3f;

	body->CreateFixture(&fixture_def);
}

void StartScreen::setEventManager(){
    event_manager_ = std::make_unique<Event::Manager>(view_world_);
    std::shared_ptr<Event::Basic> ev = std::make_shared<Event::Basic>();

    event_manager_->add("test", Event::Manager::State::ACTIVE, ev);
}

void StartScreen::setTextureManagers(std::shared_ptr<sf::RenderWindow> & window){
    float res_X = 1920.f, res_Y = 1080.f;

    view_world_ = std::make_shared<sf::View>(sf::FloatRect(-(res_X / 2), -(res_Y / 2), res_X, res_Y)); // point is in bottom left
    view_UI_ = std::make_shared<sf::View>(sf::FloatRect(0, 0, res_X, res_Y));
    draw_manager_ = Draw::Manager::create(LAYER_NAME, window, view_world_);

    texture_manager_.load("resource/texture/blue_light.jpg", "blue_light");
    texture_manager_.load("resource/texture/highway_road.jpg", "highway_road");

    //draw_manager_->addLayer(LAYER_NAME, "UI", view_UI);
}

void StartScreen::addExitButton(std::shared_ptr<Button::Exit>& exit_button, std::shared_ptr<sf::RenderWindow> & window){
    // how it is done
    // create button object. this object on press will do nothing
    // but when we connect it to the Trigger::Event that will tell us how to
    // interpret the event from sfml and will call the right method from button object.
    // In short trigger will call the right method based on sfml event.
   
    // this must be shared, because the trigger must have the button to invoke its methods
    exit_button = std::make_shared<Button::Exit>(*window, texture_manager_.get("blue_light"));
    exit_button->setSize(sf::Vector2f(100, 100));
    draw_manager_->addEntity(LAYER_NAME, exit_button);
    exit_button->setTexture(&texture_manager_.get("blue_light")->getResource());

    // create action trigger that will interpret the sfml event and will call method from button object.

    // shared_ptr, because the button could have a need to change something in his trigger
    auto trigger_button_event = Trigger::Event::Button::create();
    // connect them both
    trigger_button_event->connect(exit_button);


    // create control mapping

    // this unique_ptr is needed only at creation time. Later this pointer is useless.
    std::unique_ptr<Control::Mapping> controls = std::make_unique<Control::Mapping>();    
    // this trigger will be triggered when the mouse will be used.
    controls->addControl(Control::Mouse::ButtonLeft, trigger_button_event);
    
    // now we connect control to the event that is used only to store the controls and call it.
    // the only thing this event control is doing is spliting the keyboard and the mouse invoking.
    std::shared_ptr<Event::Control> event_control = std::make_shared<Event::Control>(controls);
    // this can be used to get the previous unique_ptr mapping
    event_control->getMapping().addControl(Control::Mouse::ButtonRight, trigger_button_event);
    // now add event that control the controls to the event manager
    event_manager_->addNew("test_button", Event::Manager::State::ACTIVE, event_control);

    /*
    Event manager can have multiple controls that some are inactive and some are active.
    Event control stores maping key -> trigger. One trigger can be mapped to multiple keys.
    Trigger will tell how to manage the event.
    Trigger can have other objects like button. I decidet that the button object will tell what to do instead of trigger but this can be different.
    Button should know what trigger is used on him.
    */
}

void StartScreen::addTextToButton(std::shared_ptr<Button::Exit>& exit_button){
    font_manager_.load("resource/fonts/open-sans/OpenSans-Italic.ttf", "Normal");
    exit_button->setFont(font_manager_.get("Normal"));
}

ScreenID StartScreen::run(std::shared_ptr<sf::RenderWindow> & window){
    setBox2D();
    setTextureManagers(window);
    setEventManager();
    std::shared_ptr<Button::Exit> exit_button;
    addExitButton(exit_button, window);
    addTextToButton(exit_button);

    auto& coord_set = CoordinateSystemSet::getInstance();
    coord_set.addNewSystem(0.0f, 0.0f, false, true, "basic", "sfml");
    coord_set.addNewSystem(0.0f, 0.0f, true, false, "basic", "view");
    auto coord_to_basic = coord_set.getReverse("sfml");
    auto coord_to_SFML = coord_set.get("sfml");
    auto coord_from_view = coord_set.get("view");

    sf::RectangleShape rectangle(sf::Vector2f(200, 40));
    sf::RectangleShape rect_UI(sf::Vector2f(60, 60));
    window->setView(*view_UI_);
    rect_UI.setPosition(0, 0);

    window->setView(*view_world_);
    rectangle.setPosition(sf::Vector2f(coord_to_basic.translateX(0.0f), coord_to_basic.translateY(200.0f)));

    window->setView(*view_world_);


    FixedFramerate framerate(15.0f);
    exit_button->setPosition(sf::Vector2f(coord_to_basic.translateX(-150.0f), coord_to_basic.translateY(300.0f)));

    while(window->isOpen()){
        sf::Event event;
        framerate.checkTime();

        while(window->pollEvent(event)){
            event_manager_->checkEvents(*window, event);
        }
        world_->Step(framerate.getRealDiff(), 6, 2 );
        view_world_->move(0, -2);

        rectangle.setPosition(coord_to_SFML.translateX(world_->GetBodyList()->GetPosition().x), coord_to_SFML.translateY(world_->GetBodyList()->GetPosition().y));
        //std::cout << world_->GetBodyList()->GetPosition().x << " " << world_->GetBodyList()->GetPosition().y << " " << framerate.getRealFramerate() << "\n";
        //std::cout << view_world->getCenter().x << " " << view_world->getCenter().y << "\n";
        //std::cout << sf::Mouse::getPosition(*window).x << "  " << sf::Mouse::getPosition(*window).y << "\n";
        window->clear();
        window->setView(*view_world_);
        window->draw(rectangle);
        draw_manager_->drawAll();
        window->setView(*view_UI_);
        window->draw(rect_UI);
        window->display();    
    }

    return ScreenID();
}


#endif