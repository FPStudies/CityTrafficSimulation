/*
 * ScreenTests.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BOOST_TEST_SCREEN_CC
#define TRAFFIC_SIM_BOOST_TEST_SCREEN_CC

#define BOOST_TEST_MODULE Screen

#include <boost/test/unit_test.hpp>
#include <memory>

#include "CoordinateSystem.h"
#include "FixedFramerate.h"
#include "GameScreen.h"
#include "ScreenID.h"
#include "ScreenInterface.h"
#include "ScreenManager.h"
#include "StartScreen.h"

CoordinateSystemSet& createCoordinateSystem(){
    auto& set = CoordinateSystemSet::getInstance();
    set.addNewSystem(0.0f, 0.0f, false, true, "basic", "one");
    set.addNewSystem(-7.0f, 5.0f, true, false, "basic", "two");
    set.addNewSystem(20.0f, -10.0f, true, true, "basic", "three");
    set.addNewSystem(-10.0f, 4.0f, false, false, "two", "four");
    set.addNewSystem(-10.0f, 4.0f, true, false, "three", "five");

    return set;
}

std::unique_ptr<FixedFramerate> createFixedFramerate(const float& FPS){
    return std::make_unique<FixedFramerate>(FPS);
}


BOOST_AUTO_TEST_CASE(coordinate_system_constructor){
    auto& set = CoordinateSystemSet::getInstance();
    set.addNewSystem(0.0f, 0.0f, false, true, "basic", "one");
    auto base_system = set.get("one");

    BOOST_REQUIRE( base_system.getNameFrom() == "basic" && base_system.getNameTo() == "one");

    CoordinateSystem copy_system(base_system);

    BOOST_REQUIRE( base_system.getNameFrom() == copy_system.getNameFrom());

    CoordinateSystem move_system(std::move(base_system));

    BOOST_CHECK( move_system.getNameFrom() == copy_system.getNameFrom() && base_system.getNameTo().length() == 0);
}

BOOST_AUTO_TEST_CASE(coordinate_system_calculation){
    auto& set = createCoordinateSystem();

    auto one = set.get("one");
    auto two = set.get("two");
    auto three = set.get("three");
    auto four = set.get("four");
    auto five = set.get("five");

    auto one_rev = set.getReverse("one");
    auto two_rev = set.getReverse("two");
    auto three_rev = set.getReverse("three");
    auto four_rev = set.getReverse("four");
    auto five_rev = set.getReverse("five");

    BOOST_CHECK_CLOSE(one.translateX(224), 224, 0.01);
    BOOST_CHECK_CLOSE(one.translateX(-56), -56, 0.01);
    BOOST_CHECK_CLOSE(one.translateY(224), -224, 0.01);
    BOOST_CHECK_CLOSE(one.translateY(-44), 44, 0.01);

    BOOST_CHECK_CLOSE(two.translateX(224), -231, 0.01);
    BOOST_CHECK_CLOSE(two.translateX(-66), 59, 0.01);
    BOOST_CHECK_CLOSE(two.translateY(224), 219, 0.01);
    BOOST_CHECK_CLOSE(two.translateY(-60), -65, 0.01);
    BOOST_CHECK_CLOSE(two.translateY(0), -5, 0.01);

    BOOST_CHECK_CLOSE(three.translateX(0), 20, 0.01);
    BOOST_CHECK_CLOSE(three.translateX(534.65), -514.65, 0.01);
    BOOST_CHECK_CLOSE(three.translateX(-74.001), 94.001, 0.01);
    BOOST_CHECK_CLOSE(three.translateY(654.253), -664.253, 0.01);
    BOOST_CHECK_CLOSE(three.translateY(-20), 10, 0.01);

    BOOST_CHECK_CLOSE(four.translateX(0), 10, 0.01);
    BOOST_CHECK_CLOSE(four.translateX(-66), -56, 0.01);
    BOOST_CHECK_CLOSE(four.translateX(42.027), 52.027, 0.01);
    BOOST_CHECK_CLOSE(four.translateY(248.6348), 244.6348, 0.01);
    BOOST_CHECK_CLOSE(four.translateY(-742.027), -746.027, 0.01);

    BOOST_CHECK_CLOSE(five.translateX(0), -10, 0.01);
    BOOST_CHECK_CLOSE(five.translateX(75), -85, 0.01);
    BOOST_CHECK_CLOSE(five.translateX(-5), -5, 0.01);
    BOOST_CHECK_CLOSE(five.translateY(1), -3, 0.01);
    BOOST_CHECK_CLOSE(five.translateY(-56), -60, 0.01);

    // Reverse

    BOOST_CHECK_CLOSE(one_rev.translateX(224), 224, 0.01);
    BOOST_CHECK_CLOSE(one_rev.translateX(-56), -56, 0.01);
    BOOST_CHECK_CLOSE(one_rev.translateY(224), -224, 0.01);
    BOOST_CHECK_CLOSE(one_rev.translateY(-44), 44, 0.01);

    BOOST_CHECK_CLOSE(two_rev.translateX(224), -231, 0.01);
    BOOST_CHECK_CLOSE(two_rev.translateX(-66), 59, 0.01);
    BOOST_CHECK_CLOSE(two_rev.translateY(224), 229, 0.01);
    BOOST_CHECK_CLOSE(two_rev.translateY(-60), -55, 0.01);
    BOOST_CHECK_CLOSE(two_rev.translateY(0), 5, 0.01);

    BOOST_CHECK_CLOSE(three_rev.translateX(0), 20, 0.01);
    BOOST_CHECK_CLOSE(three_rev.translateX(534.65), -514.65, 0.01);
    BOOST_CHECK_CLOSE(three_rev.translateX(-74.001), 94.001, 0.01);
    BOOST_CHECK_CLOSE(three_rev.translateY(654.253), -664.253, 0.01);
    BOOST_CHECK_CLOSE(three_rev.translateY(-20), 10, 0.01);

    BOOST_CHECK_CLOSE(four_rev.translateX(0), -10, 0.01);
    BOOST_CHECK_CLOSE(four_rev.translateX(-66), -76, 0.01);
    BOOST_CHECK_CLOSE(four_rev.translateX(42.027), 32.027, 0.01);
    BOOST_CHECK_CLOSE(four_rev.translateY(248.6348), 252.6348, 0.01);
    BOOST_CHECK_CLOSE(four_rev.translateY(-742.027), -738.027, 0.01);

    BOOST_CHECK_CLOSE(five_rev.translateX(0), -10, 0.01);
    BOOST_CHECK_CLOSE(five_rev.translateX(75), -85, 0.01);
    BOOST_CHECK_CLOSE(five_rev.translateX(-5), -5, 0.01);
    BOOST_CHECK_CLOSE(five_rev.translateY(1), 5, 0.01);
    BOOST_CHECK_CLOSE(five_rev.translateY(-56), -52, 0.01);
}

BOOST_AUTO_TEST_CASE(fixed_framerate_constructor){
    auto fr = createFixedFramerate(60);
    auto fr_2 = createFixedFramerate(60);
    
    fr->setPoint();
    fr_2->setPoint();

    fr->checkTime();
    fr_2->checkTime();

    FixedFramerate test_1(*fr);
    FixedFramerate test_2(*fr_2);

    BOOST_REQUIRE_CLOSE(test_1.getRealDiff(), test_2.getRealDiff(), 0.001);
    BOOST_REQUIRE_CLOSE(test_1.getFramerate(), test_2.getFramerate(), 0.001);
    BOOST_REQUIRE(test_1.getRealFramerate() == test_2.getRealFramerate());

    FixedFramerate test_3 = std::move(test_1);
    FixedFramerate test_4 = std::move(test_2);

    BOOST_REQUIRE_CLOSE(test_1.getRealDiff(), test_2.getRealDiff(), 0.001);
    BOOST_REQUIRE_CLOSE(test_1.getFramerate(), test_2.getFramerate(), 0.001);
    BOOST_REQUIRE(test_1.getRealFramerate() == test_2.getRealFramerate());

    FixedFramerate test_5(std::move(test_3));
    FixedFramerate test_6(std::move(test_4));

    BOOST_REQUIRE_CLOSE(test_1.getRealDiff(), test_2.getRealDiff(), 0.001);
    BOOST_REQUIRE_CLOSE(test_1.getFramerate(), test_2.getFramerate(), 0.001);
    BOOST_REQUIRE(test_1.getRealFramerate() == test_2.getRealFramerate());

}

BOOST_AUTO_TEST_CASE(fixed_framerate_time){
    auto fr = createFixedFramerate(60);
    auto fr_2 = createFixedFramerate(30);
    fr->setFramerate(30);

    BOOST_CHECK_CLOSE(fr->getFramerate(), 1.0 / 30.0, 0.01);
    fr->setPoint();
    fr_2->setPoint();

    fr->checkTime();
    fr_2->checkTime();

    BOOST_CHECK_CLOSE(fr->getRealDiff(), fr_2->getRealDiff(), 0.04);
    
    fr->reset();
    fr_2->reset();

    fr->setFramerate(64);
    fr_2->setFramerate(64);

    fr->checkTime();
    fr_2->checkTime();

    fr->checkTime();
    fr_2->checkTime();

    BOOST_CHECK(fr->getRealFramerate() == 0);
    BOOST_CHECK(fr->getRealFramerate() == fr_2->getRealFramerate());


}

BOOST_AUTO_TEST_CASE(screen_ID){
    ScreenID id;
    StartScreen new_screen;

    BOOST_CHECK(id.isValid() == false);
    BOOST_CHECK(new_screen.getID().isValid() == true);

    ScreenID new_ID(new_screen.getID());
    BOOST_CHECK(new_ID.isValid() == true);
    BOOST_CHECK(*new_ID == *(new_screen.getID()));
}

BOOST_AUTO_TEST_CASE(screen_manager_start_screen){
    ScreenManager manager;
    std::shared_ptr<StartScreen> screen = std::make_shared<StartScreen>();

    manager.addScreen(screen, "test");

    BOOST_CHECK(manager.getScreenID("test") == screen->getID());

    auto id = manager.getScreenID("test");

    BOOST_CHECK(manager.getScreenName(id) == "test");

}


#endif 