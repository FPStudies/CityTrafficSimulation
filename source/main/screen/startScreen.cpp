#ifndef ZPR_TRAFFIC_SIM_START_SCREEN_CPP
#define ZPR_TRAFFIC_SIM_START_SCREEN_CPP

#include "startScreen.h"

StartScreen::StartScreen() 
: ScreenInteface()
{}

StartScreen::~StartScreen() {}

void StartScreen::setBox2D(){
    world = std::make_unique<b2World>(b2Vec2( 0.0f, 0.02f ));

    b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 400.0f);
    groundBodyDef.type = b2_staticBody;


	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(1000.0f, 1.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(100.0f, 200.0f);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(200.0f, 40.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}

void StartScreen::setEventManager(){
    eventManager = std::make_unique<EventManager>();
    std::shared_ptr<BasicEvents> ev = std::make_shared<BasicEvents>();

    eventManager->add("test", EventManager::State::Active, ev);
}

ScreenID StartScreen::run(std::shared_ptr<sf::RenderWindow> & window){
    setBox2D();
    setEventManager();

    sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));

    sf::RectangleShape rectangle(sf::Vector2f(200, 40));
    rectangle.setPosition(sf::Vector2f(100, 200));

    window->setView(view);

    while(window->isOpen()){
        sf::Event event;

        while(window->pollEvent(event)){
            eventManager->checkEvents(*window, event);
        }
        world->Step( 1.0f / 60.0f, 6, 2 );
        rectangle.setPosition(world->GetBodyList()->GetPosition().x, world->GetBodyList()->GetPosition().y);

        window->clear();
        window->draw(rectangle);
        window->display();    
    }

    return ScreenID();
}


#endif