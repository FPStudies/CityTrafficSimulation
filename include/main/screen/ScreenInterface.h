/*
 * ScreenInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_SCREEN_INTERFACE_H
#define TRAFFIC_SIM_MAIN_SCREEN_SCREEN_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>
#include <thread>

#include "ScreenID.h"
#include "../utility/Singleton.hpp"

#include "../synchronization/Loop.h"

/**
 * @brief Interface used by all screens.
 * 
 */
class ScreenInterface{

    ScreenID ID_;

protected:

    static std::mutex lock_loopback_data_;

    struct LoopbackData{
        std::atomic<bool> is_anyone_waiting_;
        std::atomic<bool> close_window_;
        std::vector<ScreenID> request_for_next_screen_;

        LoopbackData();
        ~LoopbackData();
    };

    static std::unique_ptr<LoopbackData> received_data_;

    void resetLoopbackData();

    bool isAnyoneWaiting();

    void clearAll();

    void setAsViewed();

    void resetLoopSynch(Synch::Loop& loopSynch, unsigned int newNumberOfThreads, bool save = true);

    void prepareLoopSynch(Synch::Loop& loopSynch);

    void endLoopSynch(Synch::Loop& loopSynch);

public:

    /**
     * @brief It is used to implement the rendering loops or other kind of tasks. Main channel to implement the program actions.
     * @details Main program will nearly always be in the state of screen. The loop will run this method
     * and return the next screen that should be used. If the returned screen ID will be invalid then it will 
     * break loop in screen manager and return to the screen manager's caller.
     * 
     * @param window 
     * @return ScreenID The next identifier of screen that should be used.
     */
    virtual ScreenID run(std::shared_ptr<sf::RenderWindow> & window) = 0;    // it wll return the next screen that should be used

    /**
     * @brief Construct a new Screen Interface object.
     * It is important that the screen should not initialize its resources in creation time.
     * There is special method for that.
     * Not respected can waste the PC resources and even throw an error.
     * 
     */
    ScreenInterface();

    /**
     * @brief Operations that should be performed before launching the screen.
     * Used to allocate resources.
     * 
     * @param window 
     */
    virtual void init(std::shared_ptr<sf::RenderWindow> & window) = 0;

    /**
     * @brief Operations that should be performed after closing the screen.
     * Used to deallocate resources.
     * 
     * @param window 
     */
    virtual void release(std::shared_ptr<sf::RenderWindow> & window) = 0;

    virtual ~ScreenInterface();

    ScreenID getID() const;

    static void requestForNextScreen(const ScreenID& ID);

    static void requestCloseWindow();
};

#endif
