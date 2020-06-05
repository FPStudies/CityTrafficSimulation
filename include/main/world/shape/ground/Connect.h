/*
 * Connect.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_WORLD_SHAPES_GROUND_CONNECT_H
#define TRAFFIC_SIM_MAIN_WORLD_SHAPES_GROUND_CONNECT_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace World::Shape::Ground{

class Connect{

public:
    virtual unsigned int getMaxNumberOfConnections() = 0;
    virtual bool connect(const std::weak_ptr<Connect>& other) = 0;

    virtual bool disconnect(const std::shared_ptr<Connect>& other) = 0;
    

};

}



#endif
