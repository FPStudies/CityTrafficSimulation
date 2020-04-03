#ifndef ZPR_TRAFFIC_SIM_SENSOR_CPP
#define ZPR_TRAFFIC_SIM_SENSOR_CPP


#include "sensor.h"

const float Sensor::VERTICES_PER_2PI = 0.1;

Sensor::Sensor()
: staticBody(nullptr), fixture(nullptr), isActive(true), created(false)
{}

void Sensor::setPropertiesAndCreate(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef, b2World& world){
    bodyDef.type = b2_staticBody;
    bodyDef.allowSleep = false;
    bodyDef.awake = true;
    bodyDef.fixedRotation = true;
    bodyDef.gravityScale = 0.0f;
    
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = 0x0001;
    fixtureDef.filter.maskBits = 0x0002;

    staticBody = world.CreateBody(&bodyDef);
    fixture = staticBody->CreateFixture(&fixtureDef);
}

bool Sensor::createFOV(const float& radius, const float& angle, b2World& world){
    if(created) return true;

    b2BodyDef bodyDef;
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    
    uint numberOfVertices = VERTICES_PER_2PI * angle + 1;
    b2Vec2* vertices = new b2Vec2[numberOfVertices + 1];

    vertices[0].Set(0, 0);
    float ratio = angle / numberOfVertices;
    float angleSet = -0.5f * angle;

    for(uint i = 0; i < numberOfVertices; ++i){
        angleSet += i * ratio;
        vertices[i + 1].Set(radius * cosf(angleSet), radius * sinf(angleSet));
    }
    fixtureDef.shape = &polygonShape; // cloned here
    polygonShape.Set(vertices, numberOfVertices + 1);

    setPropertiesAndCreate(bodyDef, fixtureDef, world);

    delete[] vertices;

    created = true;
    return false;
}

bool Sensor::createSensorSphere(const float& radius, b2World& world){
    if(created) return true;

    b2BodyDef bodyDef;
    b2CircleShape circleShape;
    b2FixtureDef fixtureDef;

    circleShape.m_radius = radius;
    fixtureDef.shape = &circleShape;
    setPropertiesAndCreate(bodyDef, fixtureDef, world);

    created = true;
    return false;
}

bool Sensor::setObjectInterface(CollisionInterface& interface){
    if(!created) return true;
    staticBody->SetUserData(&interface);

    return false;
}

 bool Sensor::sensorAwake(){
     if(!created) return false;
     return staticBody->IsEnabled();
 }

 void Sensor::setAwake(bool mode){
     if(!created) return;
     staticBody->SetAwake(mode);
 }

CollisionInterface* Sensor::getInterface(){
    if(!created) return nullptr;
    return static_cast<CollisionInterface*>(staticBody->GetUserData());
}

#endif