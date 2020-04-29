/*
 * Sensor.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SENSOR_CPP
#define TRAFFIC_SIM_SENSOR_CPP


#include "Sensor.h"

const float Sensor::VERTICES_PER_2PI = 0.1;

Sensor::Sensor()
: static_body_(nullptr), fixture_(nullptr), is_active_(true), created_(false)
{}

void Sensor::setPropertiesAndCreate(b2BodyDef& body_def, b2FixtureDef& fixture_def, b2World& world){
    body_def.type_ = b2_static_body_;
    body_def.allow_sleep_ = false;
    body_def.awake_ = true;
    body_def.fixed_rotation_ = true;
    body_def.gravity_scale_ = 0.0f;
    
    fixture_def.is_sensor_ = true;
    fixture_def.filter_.category_bits_ = 0x0001;
    fixture_def.filter_.mask_bits_ = 0x0002;

    static_body_ = world.CreateBody(&body_def);
    fixture_ = static_body_->CreateFixture(&fixture_def);
}

bool Sensor::createFOV(const float& radius, const float& angle, b2World& world){
    if(created) return true;

    b2BodyDef body_def;
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    
    uint number_of_vertices = VERTICES_PER_2PI * angle + 1;
    b2Vec2* vertices = new b2Vec2[number_of_vertices + 1];

    vertices[0].Set(0, 0);
    float ratio = angle / number_of_vertices;
    float angle_set = -0.5f * angle;

    for(uint i = 0; i < number_of_vertices; ++i){
        angle_set += i * ratio;
        vertices[i + 1].Set(radius * cosf(angle_set), radius * sinf(angle_set));
    }
    fixture_def.shape = &polygon_shape; // cloned here
    polygon_shape.Set(vertices, number_of_vertices + 1);

    setPropertiesAndCreate(body_def, fixture_def, world);

    delete[] vertices;

    created = true;
    return false;
}

bool Sensor::createSensorSphere(const float& radius, b2World& world){
    if(created) return true;

    b2BodyDef body_def;
    b2CircleShape circle_shape;
    b2FixtureDef fixture_def;

    circle_shape.m_radius = radius;
    fixture_def.shape = &circle_shape;
    setPropertiesAndCreate(body_def, fixture_def, world);

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
