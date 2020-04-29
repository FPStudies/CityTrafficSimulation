#ifndef ZPR_TRAFFIC_SIM_COORDINATE_SYSTEM_H
#define ZPR_TRAFFIC_SIM_COORDINATE_SYSTEM_H

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

    std::map<std::string, CoordinateSystem> systems;
    CoordinateSystemSet();

public:
    
    static CoordinateSystemSet& getInstance();
    ~CoordinateSystemSet();
    CoordinateSystemSet(const CoordinateSystemSet& other) = delete;
    CoordinateSystemSet(CoordinateSystemSet&& other) = delete;
    CoordinateSystemSet& operator=(CoordinateSystemSet&& other) = delete;
    CoordinateSystemSet& operator=(CoordinateSystemSet& other) = delete;

    bool addNewSystem(
        const CoordType& relativeX, 
        const CoordType& relativeY, 
        const bool reverseX, // the reverse affects relativeX
        const bool reverseY, // the reverse affects relativeY
        const std::string& relativeCoord, 
        const std::string& CoordName
        );

    CoordinateSystem get(const std::string& CoordName);
    CoordinateSystem getReverse(const std::string& CoordName);

};


/**
 * @brief Helper class that can be used to translate one coordinate system to another.
 * Can be created only by CoordinateSystemSet class.
 * 
 */
class CoordinateSystem{
    friend class CoordinateSystemSet;
    using CoordType = float;

    CoordType relativeX, relativeY;
    bool reverseX, reverseY;
    std::string nameFrom, nameTo;

    CoordinateSystem(
        const CoordType& relativeX, 
        const CoordType& relativeY, 
        const bool reverseX,
        const bool reverseY, 
        const std::string& nameFrom, 
        const std::string& nameTo
        );

public:
    CoordinateSystem() = delete;
    ~CoordinateSystem();
    CoordinateSystem(const CoordinateSystem& other);
    CoordinateSystem(CoordinateSystem&& other);
    CoordinateSystem& operator=(CoordinateSystem&& other);

    std::pair<CoordType, CoordType> translate(const CoordType& x, const CoordType& y) const;
    CoordType translateX(const CoordType& x) const;
    CoordType translateY(const CoordType& y) const;
    sf::Vector2f translate(const sf::Vector2f& coord) const;
    b2Vec2 translate(const b2Vec2& coord) const;

    std::string getNameFrom() const; // name of the relative coordinate
    std::string getNameTo() const; // the coordinate name

};

#endif