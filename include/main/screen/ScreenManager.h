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

class ScreenManager{
    struct Pair{
        ScreenID ID_; // copy of ID of the screen
        std::string name_;
        std::shared_ptr<ScreenInteface> screen_;

        Pair(const ScreenID&, const std::string&, const std::shared_ptr<ScreenInteface>&);
        Pair(const Pair&);
    };

    struct Pair2{
        int a_;
    };
    
    struct IndexByID {};
    struct IndexByString {};

    /**
     * @brief Container used to store a Pair stuct with 2 keys.
     * 
     */
    using Container = boost::multi_index_container<
    Pair,
    boost::multi_index::indexed_by<
    boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByID>,
        boost::multi_index::member<Pair, ScreenID, &Pair::ID_>
    >,
    boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByString>,
        boost::multi_index::member<Pair, std::string, &Pair::name_>
    >>
    >;

    Container screens_;

    bool nameExist(const std::string& name);

public:
    ScreenManager();
    ~ScreenManager();
    ScreenManager(const ScreenManager&) = delete;

    /**
     * @brief Add screen with a name.
     * 
     * @param screen 
     * @param name 
     * @return true If operation was unsuccessful. The screen with that name already exist.
     * @return false Otherwise.
     */
    bool addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name);

    ScreenID getScreenID(const std::string& name);
    std::string getScreenName(const ScreenID& ID);


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
