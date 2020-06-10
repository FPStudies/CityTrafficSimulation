/*
 * FixedFramerate.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_FIXED_FRAMERATE_H
#define TRAFFIC_SIM_MAIN_SCREEN_FIXED_FRAMERATE_H

#include <utility>
#include <chrono>

/**
 * @brief Used to synchronize the frequency with which frames are generated.
 * Instead of sleep that use SFML this class uses active waiting.
 * 
 */
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

    /**
     * @brief Set the framerate.
     * Framerate set to 0.0 will do nothing.
     * 
     * @param framerate 
     */
    void setFramerate(const Framerate& framerate);

    /**
     * @brief Get the real framerate in which frames are generated.
     * It always has a lower value than the set framerate.
     * 
     * @details It counts and return how many frames were displayed in the last one second.
     * 
     * @return unsigned int 
     */
    unsigned int getRealFramerate() const;

    /**
     * @brief Get the set framerate.
     * 
     * @return Framerate 
     */
    Framerate getFramerate() const;

    /**
     * @brief Get the real difference in time between two last frames.
     * 
     * @return Framerate 
     */
    Framerate getRealDiff() const;

    /**
     * @brief Used to synchronize framerate.
     * It will loop until the next frame.
     * 
     */
    void checkTime();

    /**
     * @brief Set the previous time as now.
     */
    void setPoint();

    /**
     * @brief Set framerate to 0.0.
     * 
     */
    void reset();
};

#endif
