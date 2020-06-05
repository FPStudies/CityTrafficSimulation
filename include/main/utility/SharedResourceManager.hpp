/*
 * SharedResourceManager.hpp
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_UTILITY_SHARE_RESOURCE_MANAGER_H
#define TRAFFIC_SIM_MAIN_UTILITY_SHARE_RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <iostream> // for std::cerr
#include <mutex>


namespace SharedResource{

enum class State{
    Removed,
    ExpectRemove,
    SetToRemove,
    Remain,
    Unknown
};

template<typename StoredObject>
class Resource{
protected:
    StoredObject object_;
    bool request_for_deleting_;

    Resource() = default;

    Resource(const StoredObject& object)
    : object_(object)
    {}

public: 
    virtual ~Resource() = default;

    // delete, because it would destroy the purpose of the manager
    Resource(const Resource&) = delete;
    Resource(Resource&&) = delete;
    Resource& operator=(Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
    Resource& operator=(Resource&&) = delete;

    void requestRemove() {
        request_for_deleting_ = true;
    }

    bool shouldBeRemoved(){
        return request_for_deleting_;
    }
    void resetRemoveRequest(){
        request_for_deleting_ = false;
    }

    State getState() const{
        if(request_for_deleting_)
            return State::ExpectRemove;
        return State::Remain;
    }

    StoredObject& getResource(){
        return object_;
    }

    const StoredObject& getResource_const() const{
        return object_;
    }
};


// if false, class have no functionality

template<typename StoredWrapper, typename StoredObject, bool = std::is_base_of<Resource<StoredObject>, StoredWrapper>::value>
class Manager {};

template<typename StoredWrapper, typename StoredObject>
class Manager<StoredWrapper, StoredObject, true>{
protected:
    typedef std::map<std::string, std::shared_ptr<StoredWrapper> > MyMap; // used for storing textures

    MyMap map_;
    std::mutex mutex_free_;
    std::mutex mutex_mod_map_;

    static std::mutex mutex_instance_;

public:

    Manager()
    : map_(), mutex_free_(), mutex_mod_map_(), is_freeing_(false)
    {}

    ~Manager() = default;
    Manager(const Manager&) = delete;
    Manager(Manager&& other)
    : map_(std::move(other.map_))
    {}
    
    Manager& operator=(Manager&& other){
        map_ = std::move(other.map_);
        return *this;
    }

    virtual bool load(const std::string& path, const std::string& alias) = 0;

    virtual bool load(const std::string& path) = 0;

    State free(const std::string& name){
        const std::lock_guard<std::mutex> lockMap(mutex_mod_map_);

        auto it = map_.find(name);
        if(it == map_.end())
            return State::Unknown;

        const std::lock_guard<std::mutex> lockFree(mutex_free_);

        if(it->second.use_count() <= 1){
            map_.erase(it);
            return State::Removed;
        }

        if(it->second->request_for_deleting_){
            return State::ExpectRemove;
        }
        else{
            it->second->request_for_deleting_ = true;
            return State::SetToRemove;
        }
    }

    /**
     * @brief Save the object that was created outside this object.
     * It copy the object.
     * 
     * @param name - what name should be given to this object
     * @param object
     * @return true - if saving did not succeeded
     * @return false - if saving did succeeded
     */
    virtual bool save(const std::string& name, const StoredObject& object) = 0;

    /**
     * @brief Get the object by name. 
     * @details If some object is somehow connected with StoredWrapper, then it should have an instance of shared_ptr of this object.
     * Otherwise the SharedResourceManager could delete that object without warning. 
     * 
     * @param name - name of the searched object
     * @return std::shared_ptr<StoredWrapper>
     */
    std::shared_ptr<StoredWrapper> get(const std::string& name){
        const std::lock_guard<std::mutex> lockMap(mutex_mod_map_);
        const std::lock_guard<std::mutex> lockFree(mutex_free_);

        auto it = map_.find(name);
        if(it == map_.end())
            return std::shared_ptr<StoredWrapper>(nullptr);

        return it->second;
        }
};

template<typename StoredWrapper, typename StoredObject>
std::mutex Manager<StoredWrapper, StoredObject, true>::mutex_instance_;

}



#endif
