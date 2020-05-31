/*
 * EventsTest.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BOOST_TEST_EVENTS_CC
#define TRAFFIC_SIM_BOOST_TEST_EVENTS_CC

#define BOOST_TEST_MODULE Events

#include <boost/test/unit_test.hpp>

#include "BasicEvents.h"
#include "EventManager.h"
#include "EventSet.h"
#include "UIEvents.h"


BOOST_AUTO_TEST_CASE(basic_events_methods){
    Basic event;
    auto copy = event.clone();

    BOOST_CHECK_EQUAL(event.equals(*copy), true);

    auto copy_2 = copy->clone();

    BOOST_CHECK_EQUAL(copy_2->equals(event), true);
}

BOOST_AUTO_TEST_CASE(UI_events_methods){
    UIEvents event;
    auto copy = event.clone();

    BOOST_CHECK_EQUAL(event.equals(*copy), true);

    auto copy_2 = copy->clone();

    BOOST_CHECK_EQUAL(copy_2->equals(event), true);
}

BOOST_AUTO_TEST_CASE(event_manager_methods){
    EventManager manager;
    std::shared_ptr<Basic> b_event = std::make_shared<Basic>();
    std::shared_ptr<UIEvents> ui_event = std::make_shared<UIEvents>();

    manager.add("test1", EventManager::State::ACTIVE, b_event);
    manager.add("test2", EventManager::State::INACTIVE, ui_event);
    manager.add("test3", EventManager::State::INACTIVE, b_event);

    BOOST_CHECK_EQUAL(manager.remove("test1"), false);
    BOOST_CHECK_EQUAL(manager.remove("test1"), true);

    BOOST_CHECK_EQUAL(manager.addNew("test1", EventManager::State::ACTIVE, b_event), false);


    manager.add("test4", EventManager::State::INACTIVE, b_event);
    manager.add("test4", EventManager::State::INACTIVE, ui_event);

    BOOST_CHECK_EQUAL(manager.remove("test4"), false);
    BOOST_CHECK_EQUAL(manager.remove("test4"), true);

}   


#endif