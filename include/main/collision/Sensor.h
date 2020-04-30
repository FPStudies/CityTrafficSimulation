/*
 * Sensor.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SENSOR_H
#define TRAFFIC_SIM_SENSOR_H


#include <memory>
#include <box2d/box2d.h>

//#include "CollisionInterface.h"

class CollisionInterface; //circural dependency workaround 

class Sensor{
    b2Body* static_body_; // world will delete body
    b2Fixture* fixture_;

    bool is_active_;
    bool created_;

    static const float VERTICES_PER_2PI;

    void setPropertiesAndCreate(b2BodyDef& body_def, b2FixtureDef& fixture_def, b2World& world);

public:

    Sensor();
    ~Sensor();

    bool createFOV(const float& radius, const float& angle, b2World& world);
    bool createSensorSphere(const float& radius, b2World& world);

    const bool sensorAwake();
    void setAwake(bool mode);

    /**
     * @brief It is used to set userdata to CollisionInterface and after that to cast to it and use contact methods.
     * You have also access to CollisionID of the object.
     * 
     * @param interface 
     * @return true 
     * @return false 
     */
    bool setObjectInterface(CollisionInterface& interface); // this will be used to set userdata to this and in contact listener cast to it.

    CollisionInterface* getInterface();
};

#endif
