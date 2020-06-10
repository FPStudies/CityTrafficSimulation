/*
 * Box2DBody.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_INTERFACE_BOX2D_BODY_H
#define TRAFFIC_SIM_MAIN_INTERFACE_BOX2D_BODY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../draw/Drawable.h"

namespace Interface{

    // TODO
    class Box2DBody{
    protected:
        b2Body* body_;

    public:
        Box2DBody(const b2BodyDef& bodyDef, b2FixtureDef& fixture, b2World& world)
        {
            body_ = world.CreateBody(&bodyDef);
            body_->CreateFixture(&fixture);
        }
        
        ~Box2DBody() = default;

        b2Body& getBody(){
            return *body_;
        }



    };    
}



#endif