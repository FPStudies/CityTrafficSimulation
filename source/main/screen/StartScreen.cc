/*
 * ScreenManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_START_SCREEN_CC
#define TRAFFIC_SIM_START_SCREEN_CC

#include "StartScreen.h"

StartScreen::StartScreen() 
: ScreenInteface()
{}

StartScreen::~StartScreen() {}

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
    event_manager_ = std::make_unique<EventManager>();
    std::shared_ptr<Basic> ev = std::make_shared<Basic>();

    event_manager_->add("test", EventManager::State::ACTIVE, ev);
}

ScreenID StartScreen::run(std::shared_ptr<sf::RenderWindow> & window){
    setBox2D();
    setEventManager();

    auto& coord_set = CoordinateSystemSet::getInstance();
    coord_set.addNewSystem(0.0f, 0.0f, false, true, "basic", "sfml");
    coord_set.addNewSystem(0.0f, 0.0f, true, false, "basic", "view");
    auto coord_to_basic = coord_set.getReverse("sfml");
    auto coord_to_SFML = coord_set.get("sfml");
    auto coord_from_view = coord_set.get("view");

    float res_X = 1920.f, res_Y = 1080.f;

    view_ = std::make_unique<sf::View>(sf::FloatRect(-(res_X / 2), -(res_Y / 2), res_X, res_Y)); // point is in bottom left

    sf::RectangleShape rectangle(sf::Vector2f(200, 40));

    rectangle.setPosition(sf::Vector2f(coord_to_basic.translateX(0.0f), coord_to_basic.translateY(200.0f)));

    window->setView(*view_);

    FixedFramerate framerate(60.0f);

    while(window->isOpen()){
        sf::Event event;
        framerate.checkTime();

        while(window->pollEvent(event)){
            event_manager_->checkEvents(*window, event);
        }
        world_->Step(framerate.getRealDiff(), 6, 2 );
        rectangle.setPosition(coord_to_SFML.translateX(world_->GetBodyList()->GetPosition().x), coord_to_SFML.translateY(world_->GetBodyList()->GetPosition().y));
        std::cout << world_->GetBodyList()->GetPosition().x << " " << world_->GetBodyList()->GetPosition().y << " " << framerate.getRealFramerate() << "\n";

        window->clear();
        window->draw(rectangle);
        window->display();    
    }

    return ScreenID();
}


#endif