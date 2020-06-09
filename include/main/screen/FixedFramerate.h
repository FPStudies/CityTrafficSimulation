/*
 * FixedFramerate.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_FIXED_FRAMERATE_H
#define TRAFFIC_SIM_MAIN_SCREEN_FIXED_FRAMERATE_H

#include <utility>
#include <chrono>

class FixedFramerate{
    // not using sf::setFramerateLimit, because it uses sleep

    using Framerate = float;

    Framerate set_frame_;
    Framerate sum_of_diff_time_; // for 1 second
    Framerate real_diff_;
    unsigned int counted_frames_per_sec_;
    unsigned int counted_frames_per_sec_previous_;
    std::chrono::steady_clock::time_point prevoius_time_; //std::chrono::_V2::steady_clock::time_point ??
    bool prev_is_set_;

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
