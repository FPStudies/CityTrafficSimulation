/*
 * KeyboardMappingNormal.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_KEYBOARD_MAPPING_NORMAL_H
#define TRAFFIC_SIM_KEYBOARD_MAPPING_NORMAL_H


#include "MappingTemplate.h"

namespace Keyboard{
    typedef sf::Keyboard::Key Key;

    const static int KEY_SIZE = sf::Keyboard::KeyCount;

    class MappingNormal : public MappingTemplate<Key, MappingNormal>{

    };
}


#endif