#ifndef ZPR_TRAFFIC_SIM_BOOST_TEST_SCREEN_CPP
#define ZPR_TRAFFIC_SIM_BOOST_TEST_SCREEN_CPP

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Screen

#include <boost/test/unit_test.hpp>

#include "coordinateSystem.h"
#include "fixedFramerate.h"
#include "gameScreen.h"
#include "screenID.h"
#include "screenInterface.h"
#include "screenManager.h"
#include "startScreen.h"

int dodaj( int i, int j )
{
    return i + j;
}

BOOST_AUTO_TEST_CASE( testDodaj )
{
    BOOST_CHECK( dodaj( 2, 2 ) == 4 );
}

BOOST_AUTO_TEST_CASE(CoordinateTest){
    auto& set = CoordinateSystemSet::getInstance();
    set.addNewSystem(0.0f, 0.0f, false, true, "basic", "one");
    set.addNewSystem(-7.0f, 5.0f, true, false, "basic", "two");
    set.addNewSystem(20.0f, -10.0f, true, true, "basic", "three");
    set.addNewSystem(-10.0f, 4.0f, false, false, "two", "four");

    auto one = set.get("one");
    auto two = set.get("two");
    auto three = set.get("three");
    auto four = set.get("four");

    auto oneRev = set.getReverse("one");
    auto twoRev = set.getReverse("two");
    auto threeRev = set.getReverse("three");
    auto fourRev = set.getReverse("four");

    s

}



#endif