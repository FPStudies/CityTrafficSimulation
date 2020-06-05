/*
 * EventsTest.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BOOST_TEST_EVENTS_CC
#define TRAFFIC_SIM_BOOST_TEST_EVENTS_CC

#define BOOST_TEST_MODULE Events

#include <boost/test/unit_test.hpp>

#include "Basic.h"
#include "Manager.h"
#include "Set.h"
#include "UI.h"


BOOST_AUTO_TEST_CASE(basic_events_methods){
    Event::Basic event;
    auto copy = event.clone();

    BOOST_CHECK_EQUAL(event.equals(*copy), true);

    auto copy_2 = copy->clone();

    BOOST_CHECK_EQUAL(copy_2->equals(event), true);
}

BOOST_AUTO_TEST_CASE(UI_events_methods){
    Event::UI event;
    auto copy = event.clone();

    BOOST_CHECK_EQUAL(event.equals(*copy), true);

    auto copy_2 = copy->clone();

    BOOST_CHECK_EQUAL(copy_2->equals(event), true);
}

BOOST_AUTO_TEST_CASE(event_manager_methods){
    Event::Manager manager;
    std::shared_ptr<Event::Basic> b_event = std::make_shared<Event::Basic>();
    std::shared_ptr<Event::UI> ui_event = std::make_shared<Event::UI>();

    manager.add("test1", Event::Manager::State::ACTIVE, b_event);
    manager.add("test2", Event::Manager::State::INACTIVE, ui_event);
    manager.add("test3", Event::Manager::State::INACTIVE, b_event);

    BOOST_CHECK_EQUAL(manager.remove("test1"), false);
    BOOST_CHECK_EQUAL(manager.remove("test1"), true);

    BOOST_CHECK_EQUAL(manager.addNew("test1", Event::Manager::State::ACTIVE, b_event), false);


    manager.add("test4", Event::Manager::State::INACTIVE, b_event);
    manager.add("test4", Event::Manager::State::INACTIVE, ui_event);

    BOOST_CHECK_EQUAL(manager.remove("test4"), false);
    BOOST_CHECK_EQUAL(manager.remove("test4"), true);

}   


#endif