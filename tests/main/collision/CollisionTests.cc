/*
 * CollisionTests.cc
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_BOOST_TEST_COLLISION_CPP
#define TRAFFIC_SIM_BOOST_TEST_COLLISION_CPP

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Screen

//#include <boost/test/included/unit_test.hpp>
#include "../../BoostTestInclude.h"

#include "Sensor.h"
#include "CollisionManagerBridgeToSets.h"
#include "CollisionManager.h"
#include "CollisionInterface.h"
#include "CollisionID.h"
#include <box2d/box2d.h>


BOOST_AUTO_TEST_CASE(collision_sensor_awake_test){

        Sensor sensor;

        BOOST_REQUIRE( sensor.sensorAwake() == false);

        b2BodyDef body_def;

}



#endif 