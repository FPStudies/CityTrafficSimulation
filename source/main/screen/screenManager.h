#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

/*
Trzeba traktować tę klasę jako środek do przejścia między różnymi 
stanami programu. 

*/

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
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

    //std::map<std::pair<ScreenID, std::string>, ScreenInteface> screens;

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

    bool addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name);

    ScreenID getScreenID(const std::string& name);
    std::string getScreenName(const ScreenID& ID);


    bool setScreen(const ScreenID& ID);
    bool setScreen(const std::string& name);


    void mainLoop(sf::RenderWindow & window, const ScreenInteface& startID);
};


#endif