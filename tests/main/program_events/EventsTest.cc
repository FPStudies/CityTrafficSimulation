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


BOOST_AUTO_TEST_CASE(basic_events_methods){
    Event::Basic event;
    auto copy = event.clone();

    BOOST_CHECK_EQUAL(event.equals(*copy), true);

    auto copy_2 = copy->clone();

    BOOST_CHECK_EQUAL(copy_2->equals(event), true);
}

#endif