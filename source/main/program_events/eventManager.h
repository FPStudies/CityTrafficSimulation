#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <memory>
#include <list>

#include "eventSet.h"

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
        Active,
        Inactive
    };

private:
    class EventSetInner{
        EventSet eventSet;
        EventManager::State state;

    public:
        EventSetInner(const EventSet& eventSet);
        EventSetInner(const EventSet& eventSet, EventManager::State mode);
        EventSetInner(const EventInterface& event);
        EventSetInner(const EventInterface& event, EventManager::State mode);
        ~EventSetInner();
        EventSetInner(const EventSetInner& events);

        bool isActive() const;
        EventSet& getEventSet();

        void setMode(EventManager::State mode);
        void addEventToSet(const EventInterface& eventObject);
        bool removeEventFromSet(const EventInterface& eventObject);
        bool empty() const;
    };

    typedef std::shared_ptr<EventSetInner> Pointer;
    typedef std::map<std::string, Pointer> Map;
    typedef std::list<Pointer> List;

    /**
     * @brief A boolean to know if the sets are sorted by Active / Inactive.
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
    void addNewEventInterface(const std::string& name, EventManager::State mode, const EventInterface& eventObject);

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
     * @param eventObjectSet Set of events
     */
    void add(const std::string& name, EventManager::State mode, const EventSet& eventObjectSet);    

    /**
     * @brief Adds a new event set.
     * If the event set with that name existed before, it will return a value.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param eventObjectSet Set of events
     * @return true If set with that name existed before.
     * @return false Otherwise.
     */
    bool addNew(const std::string& name, EventManager::State mode, const EventSet& eventObjectSet); // without constructing new name to the collection of sets
    
    /**
     * @brief Adds a new event to the set. If the set with that name do not exist, then
     * it creates a new set.
     * It can be used to adds a new functionality to the existing set.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param eventObject Event that will be put into event set.
     */
    void add(const std::string& name, EventManager::State mode, const EventInterface& eventObject); 

    /**
     * @brief Adds a new event.
     * If the event set with that name existed before, it will return a value.
     * 
     * @param name Identifier
     * @param mode Active / Inactive
     * @param eventObject Event that will be put into event set.
     * @return true If set with that name existed before.
     * @return false Otherwise.
     */
    bool addNew(const std::string& name, EventManager::State mode, const EventInterface& eventObject); 

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
     * @param eventObject 
     * @return true If operation was unsuccessful. It means that there is no event set with that name.
     * @return false Otherwise.
     */
    bool remove(const std::string& name, const EventInterface& eventObject);


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