#ifndef ZPR_TRAFFIC_SIM_RENDER_LOOP_CPP
#define ZPR_TRAFFIC_SIM_RENDER_LOOP_CPP

#include <memory>
#include <box2d/box2d.h>
#include <iostream>

#include "renderLoop.h"

using namespace sf;

RenderLoop::RenderLoop(const uint& width, const uint& height, const char* name, const uint& modeBitsPerPixel)
: window(sf::VideoMode(width, height, modeBitsPerPixel), name)
{}

RenderLoop::~RenderLoop(){}

const int RenderLoop::render(){
    EventManager eventManager;
    std::shared_ptr<BasicEvents> ev = std::make_shared<BasicEvents>();



    b2World world(b2Vec2( 0.0f, -10.0f ));
    
    b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
    


    eventManager.add("test", EventManager::State::Active, ev);

    int i = 60; // because it is too fast
    while(window.isOpen() && --i != 0){
        sf::Event event;

        while(window.pollEvent(event)){
            eventManager.checkEvents(window, event);
        }

        world.Step( 1.0f / 60.0f, 6, 2 );
        b2Vec2 position = body->GetPosition();
        printf("%4.2f %4.2f\n", position.x, position.y);


        window.clear();
        window.display();    
    }

    return EXIT_SUCCESS;
}




static const std::vector<sf::VideoMode> getFullscreenVideoModes() {
    return std::vector<sf::VideoMode>(sf::VideoMode::getFullscreenModes());
}

#endif
