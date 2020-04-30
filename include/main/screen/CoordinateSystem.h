/*
 * CoordinateSystem.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_COORDINATE_SYSTEM_H
#define TRAFFIC_SIM_COORDINATE_SYSTEM_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

/**
 * @brief Provides a unified coordinate system.
 * Stores all provided coordinate systems.
 * 
 * @details The first coordinate system is created in constructor with a name "basic".
 * Other coordinate systems can be defined in relation to him.
 * 
 * For now it does not support rotation.
 * 
 */
class CoordinateSystem;

class CoordinateSystemSet{
    using CoordType = float;

    std::map<std::string, CoordinateSystem> systems_;
    CoordinateSystemSet();

public:
    
    static CoordinateSystemSet& getInstance();
    ~CoordinateSystemSet();
    CoordinateSystemSet(const CoordinateSystemSet& other) = delete;
    CoordinateSystemSet(CoordinateSystemSet&& other) = delete;
    CoordinateSystemSet& operator=(CoordinateSystemSet&& other) = delete;
    CoordinateSystemSet& operator=(CoordinateSystemSet& other) = delete;

    bool addNewSystem(
        const CoordType& relative_X, 
        const CoordType& relative_Y, 
        const bool reverse_X, // the reverse affects relativeX
        const bool reverse_Y, // the reverse affects relativeY
        const std::string& relative_coord, 
        const std::string& coord_name
        );

    CoordinateSystem get(const std::string& coord_name);
    CoordinateSystem getReverse(const std::string& coord_name);

};


/**
 * @brief Helper class that can be used to translate one coordinate system to another.
 * Can be created only by CoordinateSystemSet class.
 * 
 */
class CoordinateSystem{
    friend class CoordinateSystemSet;
    using CoordType = float;

    CoordType relative_X_, relative_Y_;
    bool reverse_X_, reverse_Y_;
    std::string name_from_, name_to_;

    CoordinateSystem(
        const CoordType& relative_X, 
        const CoordType& relative_Y, 
        const bool reverse_X,
        const bool reverse_Y, 
        const std::string& name_from, 
        const std::string& name_to
        );

public:
    CoordinateSystem() = delete;
    ~CoordinateSystem();
    CoordinateSystem(const CoordinateSystem& other);
    CoordinateSystem(CoordinateSystem&& other);
    CoordinateSystem& operator=(CoordinateSystem&& other);
    //friend bool operator==(const CoordinateSystem& one, const CoordinateSystem& other);

    std::pair<CoordType, CoordType> translate(const CoordType& x, const CoordType& y) const;
    CoordType translateX(const CoordType& x) const;
    CoordType translateY(const CoordType& y) const;
    sf::Vector2f translate(const sf::Vector2f& coord) const;
    b2Vec2 translate(const b2Vec2& coord) const;

    std::string getNameFrom() const; // name of the relative coordinate
    std::string getNameTo() const; // the coordinate name

};

#endif
