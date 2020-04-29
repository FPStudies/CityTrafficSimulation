#ifndef ZPR_TRAFFIC_SIM_START_SCREEN_CPP
#define ZPR_TRAFFIC_SIM_START_SCREEN_CPP

#include "startScreen.h"

StartScreen::StartScreen() 
: ScreenInteface()
{}

StartScreen::~StartScreen() {}

void StartScreen::setBox2D(){
    world = std::make_unique<b2World>(b2Vec2( 0.0f, -10.0f ));

    b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
    groundBodyDef.type = b2_staticBody;


	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(200.0f, 1.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 200.0f);
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

    auto& coordSet = CoordinateSystemSet::getInstance();
    coordSet.addNewSystem(0.0f, 0.0f, false, true, "basic", "sfml");
    coordSet.addNewSystem(0.0f, 0.0f, true, false, "basic", "view");
    auto coordToBasic = coordSet.getReverse("sfml");
    auto coordToSFML = coordSet.get("sfml");
    auto coordFromView = coordSet.get("view");

    float resX = 1920.f, resY = 1080.f;

    view = std::make_unique<sf::View>(sf::FloatRect(-(resX / 2), -(resY / 2), resX, resY)); // point is in bottom left

    sf::RectangleShape rectangle(sf::Vector2f(200, 40));

    rectangle.setPosition(sf::Vector2f(coordToBasic.translateX(0.0f), coordToBasic.translateY(200.0f)));

    window->setView(*view);

    FixedFramerate framerate(60.0f);

    while(window->isOpen()){
        sf::Event event;
        framerate.checkTime();

        while(window->pollEvent(event)){
            eventManager->checkEvents(*window, event);
        }
        world->Step(framerate.getRealDiff(), 6, 2 );
        rectangle.setPosition(coordToSFML.translateX(world->GetBodyList()->GetPosition().x), coordToSFML.translateY(world->GetBodyList()->GetPosition().y));
        std::cout << world->GetBodyList()->GetPosition().x << " " << world->GetBodyList()->GetPosition().y << " " << framerate.getRealFramerate() << "\n";

        window->clear();
        window->draw(rectangle);
        window->display();    
    }

    return ScreenID();
}


#endif