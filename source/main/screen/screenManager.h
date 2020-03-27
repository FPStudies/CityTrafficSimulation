#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

/*
Trzeba traktować tę klasę jako środek do przejścia między różnymi 
stanami programu. 

*/

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <memory>

#include "screenInterface.h"

class ScreenManager{
    struct Pair{
        ScreenID ID; // copy of ID of the screen
        std::string name;
        std::shared_ptr<ScreenInteface> screen;

        Pair(const ScreenID&, const std::string&, const std::shared_ptr<ScreenInteface>&);
        Pair(const Pair&);
    };

    struct Pair2{
        int a;
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
        boost::multi_index::member<Pair, ScreenID, &Pair::ID>
    >,
    boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByString>,
        boost::multi_index::member<Pair, std::string, &Pair::name>
    >>
    >;

    Container screens;

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
     * @param startID An ID of a starting screen.
     */
    void mainLoop(sf::RenderWindow & window, const ScreenInteface& startID);
};


#endif