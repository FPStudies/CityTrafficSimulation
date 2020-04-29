/*
 * ScreenTests.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef ZPR_TRAFFIC_SIM_BOOST_TEST_SCREEN_CPP
#define ZPR_TRAFFIC_SIM_BOOST_TEST_SCREEN_CPP

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Screen

#include <boost/test/unit_test.hpp>

#include "CoordinateSystem.h"
#include "FixedFramerate.h"
#include "GameScreen.h"
#include "ScreenID.h"
#include "ScreenInterface.h"
#include "ScreenManager.h"
#include "StartScreen.h"

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

    auto one_rev = set.getReverse("one");
    auto two_rev = set.getReverse("two");
    auto three_rev = set.getReverse("three");
    auto four_rev = set.getReverse("four");

}



#endif 