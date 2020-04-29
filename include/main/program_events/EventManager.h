/*
 * EventManager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_EVENT_MANAGER_H
#define TRAFFIC_SIM_EVENT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <memory>
#include <list>

#include "EventSet.h"

/**
 * @brief Stores events that can be active or not.
 * @details Active events will be used in event checking.
 * Events can be added as EventSet or directly.
 * Each set have a name that identify it.
 * Only a set of events can be active or inactive.
 * 
 */
class EventManager{
public:
    /**
     * @brief Used to set the mode.
     * Active event set will be included while checking event.
     * Inactive event set will not be included while checking event.
     * 
     */
    enum class State{
        ACTIVE,
        INACTIVE
    };

private:
    class EventSetInner{
        EventSet event_set_;
        EventManager::State state_;

    public:
        EventSetInner(const EventSet& event_set);
        EventSetInner(const EventSet& event_set, EventManager::State mode);
        EventSetInner(const std::shared_ptr<EventInterface>& event);
        EventSetInner(const std::shared_ptr<EventInterface>& event, EventManager::State mode);
        ~EventSetInner();
        EventSetInner(const EventSetInner& events);

        bool isActive() const;
        EventSet& getEventSet();

        void setMode(EventManager::State mode);
        void addEventToSet(const std::shared_ptr<EventInterface>& event_object);
        bool removeEventFromSet(const std::shared_ptr<EventInterface>& event_object);
        bool empty() const;
    };

    typedef std::shared_ptr<EventSetInner> Pointer;
    typedef std::map<std::string, Pointer> Map;
    typedef std::list<Pointer> List;

    /**
     * @brief A boolean to know if the sets are sorted by Active / Inactive.
     */
     bool events_sorted_; 

     /**
     * @brief Map names with event sets.
     */
     Map events_map_names_;
     List events_sorted_list_;

    /**
     * @brief Sort list only by binary value. 
     * Computational complexity O(n).
     */
    void sortListBinaryVal();
    
    bool ifElementMapExist(const std::string& name, Map::iterator& it);
    bool ifElementMapExist(const std::string& name);
    void addNewEventInterface(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object);

public:

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
     * @param name Identifier
     * @param mode Active / Inactive
     * @param event_object_set Set of events
     */
    void add(const std::string& name, EventManager::State mode, const EventSet& event_object_set);    

    /**
     * @brief Adds a new event set.
     * If the event set with that name existed before, it will return a value.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param event_object_set Set of events
     * @return true If set with that name existed before.
     * @return false Otherwise.
     */
    bool addNew(const std::string& name, EventManager::State mode, const EventSet& event_object_set); // without constructing new name to the collection of sets
    
    /**
     * @brief Adds a new event to the set. If the set with that name do not exist, then
     * it creates a new set.
     * It can be used to adds a new functionality to the existing set.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param event_object Event that will be put into event set.
     */
    void add(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object); 

    /**
     * @brief Adds a new event.
     * If the event set with that name existed before, it will return a value.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param event_object Event that will be put into event set.
     * @return true If set with that name existed before.
     * @return false Otherwise.
     */
    bool addNew(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object); 

    /**
     * @brief Change mode to Active / Inactive.
     * 
     * @param name Identifier
     * @param mode Active / Inactive in namespace of this class
     */
    void changeMode(const std::string& name, EventManager::State mode);

    /**
     * @brief Remove the set of events identified by name.
     * 
     * @param name Identifier
     * @return true If operation was unsuccessful. It means that there is no event set with that name.
     * @return false Otherwise.
     */
    bool remove(const std::string& name);

    /**
     * @brief Remove specific event from the set.
     * 
     * @param name Identifier
     * @param event_object
     * @return true If operation was unsuccessful. It means that there is no event set with that name.
     * @return false Otherwise.
     */
    bool remove(const std::string& name, const std::shared_ptr<EventInterface>& event_object);


    /**
     * @brief Run and check occurence in all active events.
     * While using it, it checks if vector is sorted. If not then it performs a simple
     * sort on binary values with computational complexity O(n) which is not heavy assumed that there will be only several dozens of sets.
     * 
     * @param window The window where the event occurred.
     * @param event An event that was already fetched from an event stack on this window.
     * There may be a lot of events on stack, so it's recommended to do it in loop.
     */
    void checkEvents(sf::RenderWindow& window, sf::Event& event);
};

#endif
