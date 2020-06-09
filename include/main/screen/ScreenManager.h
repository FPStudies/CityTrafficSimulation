/*
 * ScreenManager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SCREEN_MANAGER_H
#define TRAFFIC_SIM_SCREEN_MANAGER_H

/*
Trzeba traktować tę klasę jako środek do przejścia między różnymi 
stanami programu. 

*/

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <memory>

#include "ScreenInterface.h"
#include "../utility/DoubleKeyManager.hpp"

class ScreenManager: protected Utils::DoubleKeyManager<ScreenID, std::string, ScreenInteface>{
    
    using Inher = Utils::DoubleKeyManager<ScreenID, std::string, ScreenInteface>;
    
public:
    
    ScreenManager();
    ~ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;


    /**
     * @brief Add screen with a name.
     * 
     * @param screen 
     * @param name 
     * @return true If operation was unsuccessful. The screen with that name already exist.
     * @return false Otherwise.
     */
    bool addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name);

    ScreenID getScreenID(const std::string& name) const;
    std::string getScreenName(const ScreenID& ID) const;

    bool remove(const ScreenID& ID);
    bool remove(const std::string& name);
    
    
    /**
     * @brief Loop that manages which screen should be displayed.
     * 
     * @param window An window where the screens will be run.
     * @param start_ID An ID of a starting screen.
     */
    void mainLoop(std::shared_ptr<sf::RenderWindow>& window, const ScreenInteface& start_ID);
    void mainLoop(std::shared_ptr<sf::RenderWindow>& window, const std::string& name);

};


#endif
