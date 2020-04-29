#ifndef ZPR_TRAFFIC_SIM_COORDINATE_SYSTEM_CPP
#define ZPR_TRAFFIC_SIM_COORDINATE_SYSTEM_CPP

#include <iostream>

#include "coordinateSystem.h"

CoordinateSystemSet::CoordinateSystemSet()
    :systems()
{
    systems.emplace("basic", CoordinateSystem(0.0, 0.0, false, false, "NULL", "basic"));
}

CoordinateSystemSet& CoordinateSystemSet::getInstance(){
    static CoordinateSystemSet instance;
    return instance;
}


CoordinateSystemSet::~CoordinateSystemSet()
{}

bool CoordinateSystemSet::addNewSystem(
    const CoordType& relativeX, 
    const CoordType& relativeY, 
    const bool reverseX, 
    const bool reverseY, 
    const std::string& relativeCoord, 
    const std::string& CoordName
    )
{
    if(systems.find(CoordName) != systems.end() || systems.find(relativeCoord) == systems.end()) return true;
    systems.emplace(CoordName, CoordinateSystem(relativeX, relativeY, reverseX, reverseY, relativeCoord, CoordName));
    return false;
}

CoordinateSystem CoordinateSystemSet::get(const std::string& CoordName){
    return systems.at(CoordName);
}

CoordinateSystem CoordinateSystemSet::getReverse(const std::string& CoordName){
    CoordinateSystem toReverse = get(CoordName);
    
    return CoordinateSystem(
        toReverse.reverseX ? toReverse.relativeX : -toReverse.relativeX,
        toReverse.reverseY ? toReverse.relativeY : -toReverse.relativeY,
        toReverse.reverseX,
        toReverse.reverseY,
        toReverse.nameTo,
        toReverse.nameFrom
    );
}




CoordinateSystem::CoordinateSystem(
    const CoordType& relativeX, 
    const CoordType& relativeY, 
    const bool reverseX,
    const bool reverseY, 
    const std::string& nameFrom, 
    const std::string& nameTo
    )
    :relativeX(relativeX), 
    relativeY(relativeY),
    reverseX(reverseX),
    reverseY(reverseY),
    nameFrom(nameFrom),
    nameTo(nameTo)
{}

CoordinateSystem::~CoordinateSystem()
{}

CoordinateSystem::CoordinateSystem(const CoordinateSystem& other)
    :relativeX(other.relativeX), 
    relativeY(other.relativeY),
    reverseX(other.reverseX),
    reverseY(other.reverseY),
    nameFrom(other.nameFrom),
    nameTo(other.nameTo)
{}

CoordinateSystem::CoordinateSystem(CoordinateSystem&& other)
    :relativeX(std::move(other.relativeX)), 
    relativeY(std::move(other.relativeY)),
    reverseX(std::move(other.reverseX)),
    reverseY(std::move(other.reverseY)),
    nameFrom(std::move(other.nameFrom)),
    nameTo(std::move(other.nameTo))
{}

CoordinateSystem& CoordinateSystem::operator=(CoordinateSystem&& other) {
    relativeX = std::move(other.relativeX);
    relativeY = std::move(other.relativeY);
    reverseX = std::move(other.reverseX);
    reverseY = std::move(other.reverseY);
    nameFrom = std::move(other.nameFrom);
    nameTo = std::move(other.nameTo);
    return *this;
}

std::string CoordinateSystem::getNameFrom() const{
    return nameFrom;
}

std::string CoordinateSystem::getNameTo() const {
    return nameTo;
}

std::pair<CoordinateSystem::CoordType, CoordinateSystem::CoordType> CoordinateSystem::translate(const CoordType& x, const CoordType& y) const{
    return std::pair<CoordType, CoordType>(translateX(x), translateY(y));
}

CoordinateSystem::CoordType CoordinateSystem::translateX(const CoordType& x) const {
    CoordType ret;
    if(reverseX) ret = relativeX - x;
    else ret = x - relativeX;

    return ret;
}

CoordinateSystem::CoordType CoordinateSystem::translateY(const CoordType& y) const {
    CoordType ret;
    if(reverseY) ret = relativeY - y;
    else ret = y - relativeY;
 
    return ret;
}

sf::Vector2f CoordinateSystem::translate(const sf::Vector2f& coord) const {
    return sf::Vector2f(translateX(coord.x), translateY(coord.y));
}

b2Vec2 CoordinateSystem::translate(const b2Vec2& coord) const {
    return b2Vec2(translateX(coord.x), translateY(coord.y));
}

#endif