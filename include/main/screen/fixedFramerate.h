#ifndef ZPR_TRAFFIC_SIM_FIXED_FRAMERATE_H
#define ZPR_TRAFFIC_SIM_FIXED_FRAMERATE_H

#include <utility>
#include <chrono>

class FixedFramerate{
    // not using sf::setFramerateLimit, because it uses sleep

    using Framerate = float;

    Framerate setFrame;
    Framerate sumOfDiffTime; // for 1 second
    Framerate realDiff;
    unsigned int countedFramesPerSec;
    unsigned int countedFramesPerSecPrevious;
    std::chrono::_V2::steady_clock::time_point prevoiusTime;
    bool prevIsSet;

public:
    FixedFramerate(const Framerate& framerate = 0.0);
    ~FixedFramerate();
    FixedFramerate(const FixedFramerate& other);
    FixedFramerate(FixedFramerate&& other);
    FixedFramerate& operator=(FixedFramerate&& other);

    void setFramerate(const Framerate& framerate);
    unsigned int getRealFramerate() const;
    Framerate getFramerate() const;
    Framerate getRealDiff() const;

    void checkTime();
    void setPoint();
    void reset();
};

#endif