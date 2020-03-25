#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <memory>
#include <list>

#include "eventSet.h"

class EventManager{
    class EventSetInner{
        EventSet eventSet;
        bool active;

    public:
        EventSetInner(const EventSet& eventSet);
        EventSetInner(const EventSet& eventSet, bool mode);
        EventSetInner(const EventInterface& event);
        EventSetInner(const EventInterface& event, bool mode);
        ~EventSetInner();
        EventSetInner(const EventSetInner& events);

        bool isActive() const;
        EventSet& getEventSet();

        void setMode(bool mode);
        void addEventToSet(const EventInterface& eventObject);
        bool removeEventFromSet(const EventInterface& eventObject);
        bool empty() const;
    };

    typedef std::shared_ptr<EventSetInner> Pointer;
    typedef std::map<std::string, Pointer> Map;
    typedef std::list<std::shared_ptr<EventSetInner>> List;

    /**
     * @brief A boolean to know if the sets are sorted by ACTIVE / INACTIVE.
     */
     bool eventsSorted; 

     /**
     * @brief Map names with event sets.
     */
     Map eventsMapNames;
     List eventsSortedList;

    /**
     * @brief Sort list only by binary value. 
     * Computational complexity O(n).
     */
    void sortListBinaryVal();
    bool ifElementMapExist(const std::string& name, Map::iterator& it);
    bool ifElementMapExist(const std::string& name);
    void addNewEventInterface(const std::string& name, bool mode, const EventInterface& eventObject);

public:
    /**
     * @brief Used to set a set mode.
     * Here set will be included in the next render loop.
     * char 0
     */
    static bool ACTIVE;

    /**
     * @brief Used to set a set mode.
     * Here set will NOT be included in the next render loop.
     * char 1
     */
    static bool INACTIVE;

    EventManager();
    ~EventManager();
    EventManager(const EventManager&) = delete;

    /**
     * @brief Adds a new event set.
     * If the event set with that name existed before, it will delete it and change to the new set.
     * 
     * @details Different sets can have part of the same functionality, so it is up to developer to watch out for them.
     * Also it is possible that the same event will have different approach in two or more sets and even in the same set.
     * 
     * @param name 
     * @param mode 
     * @param eventObjectSet 
     */
    void add(const std::string& name, bool mode, const EventSet& eventObjectSet);    

    /**
     * @brief Adds a new event set.
     * If the event set with that name existed before, it will return a value
     * 
     * @param name 
     * @param mode 
     * @param eventObjectSet 
     * @return true if set with that name existed before.
     * @return false otherwise.
     */
    bool addNew(const std::string& name, bool mode, const EventSet& eventObjectSet); // without constructing new name to the collection of sets
    
    /**
     * @brief Adds a new event to the set. If the set with that name do not exist, then
     * it creates a new set.
     * It can be used to adds a new functionality to the existing set.
     * 
     * @param name 
     * @param mode 
     * @param eventObject 
     */
    void add(const std::string& name, bool mode, const EventInterface& eventObject); 
    bool addNew(const std::string& name, bool mode, const EventInterface& eventObject); 

    /**
     * @brief Change mode to ACTIVE / INACTIVE.
     * 
     * @param name 
     * @param mode ACTIVE / INACTIVE in namespace of this class
     */
    void changeMode(const std::string& name, bool mode);

    bool remove(const std::string& name);
    bool remove(const std::string& name, const EventInterface& eventObject);


    /**
     * @brief Run and check occurence in all active events.
     * While using it, it checks if vector is sorted. If not then it performs a simple
     * sort on binary values with computational complexity O(n).
     * Moreover it is assumed that there will be only few sets.
     * 
     * @param window The window where the event occurred.
     * @param event An event that was already fetched from an event stack on this window.
     * There may be a lot of events on stack, so it's recommended to do it in loop.
     */
    void checkEvents(sf::RenderWindow& window, sf::Event& event);
};

#endif