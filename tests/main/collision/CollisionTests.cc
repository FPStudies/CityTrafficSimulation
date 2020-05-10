/*
 * CollisionTests.cc
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_BOOST_TEST_COLLISION_CC
#define TRAFFIC_SIM_BOOST_TEST_COLLISION_CC

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Colliion

#include <boost/test/unit_test.hpp>

#include "Sensor.h"
#include "CollisionManagerBridgeToSets.h"
#include "CollisionManager.h"
#include "CollisionInterface.h"
#include "CollisionID.h"
#include <Box2D/Box2D.h>

BOOST_AUTO_TEST_CASE(collision_sensor_creation_test){

        Sensor sensor_1, sensor_2;

        b2Vec2 vec(1,1);
        b2World world(vec);

        BOOST_REQUIRE( sensor_1.createSensorSphere(1.0f, world) == false);
        BOOST_REQUIRE( sensor_2.createFOV(5.0f, 60.0f, world) == false);

        BOOST_CHECK_EQUAL( sensor_1.createSensorSphere(1.0f, world), true);
        BOOST_CHECK_EQUAL( sensor_2.createFOV(1.0f, 1.0f, world), true);
}

BOOST_AUTO_TEST_CASE(collision_sensor_awake_test){

        Sensor sensor_1, sensor_2;

        BOOST_CHECK_EQUAL( sensor_1.sensorAwake(), false);
        BOOST_CHECK_EQUAL( sensor_2.sensorAwake(), false);

        b2Vec2 vec(1,1);
        b2World world(vec);

        sensor_1.createSensorSphere(1.0f, world);
        sensor_2.createFOV(5.0f, 60.0f, world);

        sensor_1.setAwake(true);
        sensor_2.setAwake(true);

        BOOST_CHECK_EQUAL( sensor_1.sensorAwake(), true);
        BOOST_CHECK_EQUAL( sensor_2.sensorAwake(), true);
}


#endif 