/*
 * CoordinateSystem.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_COORDINATE_SYSTEM_CC
#define TRAFFIC_SIM_COORDINATE_SYSTEM_CC

#include <iostream>

#include "CoordinateSystem.h"

CoordinateSystemSet::CoordinateSystemSet()
    :systems_()
{
    systems_.emplace("basic", CoordinateSystem(0.0, 0.0, false, false, "NULL", "basic"));
}

CoordinateSystemSet& CoordinateSystemSet::getInstance(){
    static CoordinateSystemSet instance;
    return instance;
}


CoordinateSystemSet::~CoordinateSystemSet()
{}

bool CoordinateSystemSet::addNewSystem(
    const CoordType& relative_X, 
    const CoordType& relative_Y, 
    const bool reverse_X, 
    const bool reverse_Y, 
    const std::string& relative_coord, 
    const std::string& coord_name
    )
{
    if(systems_.find(coord_name) != systems_.end() || systems_.find(relative_coord) == systems_.end())
        return true;
    systems_.emplace(coord_name, CoordinateSystem(relative_X, relative_Y, reverse_X, reverse_Y, relative_coord, coord_name));
    return false;
}

CoordinateSystem CoordinateSystemSet::get(const std::string& coord_name){
    return systems_.at(coord_name);
}

CoordinateSystem CoordinateSystemSet::getReverse(const std::string& coord_name){
    CoordinateSystem to_reverse = get(coord_name);
    
    return CoordinateSystem(
        to_reverse.reverse_X_ ? to_reverse.relative_X_ : -to_reverse.relative_X_,
        to_reverse.reverse_Y_ ? to_reverse.relative_Y_ : -to_reverse.relative_Y_,
        to_reverse.reverse_X_,
        to_reverse.reverse_Y_,
        to_reverse.name_to_,
        to_reverse.name_from_
    );
}




CoordinateSystem::CoordinateSystem(
    const CoordType& relative_X, 
    const CoordType& relative_Y, 
    const bool reverse_X,
    const bool reverse_Y, 
    const std::string& name_from, 
    const std::string& name_to
    )
    :relative_X_(relative_X), 
    relative_Y_(relative_Y),
    reverse_X_(reverse_X),
    reverse_Y_(reverse_Y),
    name_from_(name_from),
    name_to_(name_to)
{}

CoordinateSystem::~CoordinateSystem()
{}

CoordinateSystem::CoordinateSystem(const CoordinateSystem& other)
    :relative_X_(other.relative_X_), 
    relative_Y_(other.relative_Y_),
    reverse_X_(other.reverse_X_),
    reverse_Y_(other.reverse_Y_),
    name_from_(other.name_from_),
    name_to_(other.name_to_)
{}

CoordinateSystem::CoordinateSystem(CoordinateSystem&& other)
    :relative_X_(std::move(other.relative_X_)), 
    relative_Y_(std::move(other.relative_Y_)),
    reverse_X_(std::move(other.reverse_X_)),
    reverse_Y_(std::move(other.reverse_Y_)),
    name_from_(std::move(other.name_from_)),
    name_to_(std::move(other.name_to_))
{}

CoordinateSystem& CoordinateSystem::operator=(CoordinateSystem&& other) {
    relative_X_ = std::move(other.relative_X_);
    relative_Y_ = std::move(other.relative_Y_);
    reverse_X_ = std::move(other.reverse_X_);
    reverse_Y_ = std::move(other.reverse_Y_);
    name_from_ = std::move(other.name_from_);
    name_to_ = std::move(other.name_to_);
    return *this;
}

/*bool CoordinateSystem::operator==(const CoordinateSystem& one, const CoordinateSystem& other) {
    return (one.relative_X_ == other.relative_X_ && one.relative_Y_ == other.relative_Y_ &&
    one.reverse_X_ == other.reverse_X_ && one.reverse_Y_ == other.reverse_Y_ &&
    one.name_from_ == other.name_from_ && one.name_to_ == other.name_to_);
}*/

std::string CoordinateSystem::getNameFrom() const{
    return name_from_;
}

std::string CoordinateSystem::getNameTo() const {
    return name_to_;
}

std::pair<CoordinateSystem::CoordType, CoordinateSystem::CoordType> CoordinateSystem::translate(const CoordType& x, const CoordType& y) const{
    return std::pair<CoordType, CoordType>(translateX(x), translateY(y));
}

CoordinateSystem::CoordType CoordinateSystem::translateX(const CoordType& x) const {
    CoordType ret;
    if(reverse_X_)
        ret = relative_X_ - x;
    else ret = x - relative_X_;

    return ret;
}

CoordinateSystem::CoordType CoordinateSystem::translateY(const CoordType& y) const {
    CoordType ret;
    if(reverse_Y_)
        ret = relative_Y_ - y;
    else ret = y - relative_Y_;
 
    return ret;
}

sf::Vector2f CoordinateSystem::translate(const sf::Vector2f& coord) const {
    return sf::Vector2f(translateX(coord.x), translateY(coord.y));
}

b2Vec2 CoordinateSystem::translate(const b2Vec2& coord) const {
    return b2Vec2(translateX(coord.x), translateY(coord.y));
}

#endif
