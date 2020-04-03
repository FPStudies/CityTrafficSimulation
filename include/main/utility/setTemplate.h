#ifndef ZPR_TRAFFIC_SIM_SET_TEMPLATE_H
#define ZPR_TRAFFIC_SIM_SET_TEMPLATE_H

#include <list>
#include <memory>

template<typename Interface>
class SetTemplate{

protected:
//typedef typename std::list<std::shared_ptr<Interface>> Container;
    using Container = std::list<std::shared_ptr<Interface>>;

    Container objects;

    void addFast(const std::shared_ptr<Interface>& obj){
        objects.push_back(obj);
    }

    bool findInstance(const std::shared_ptr<Interface>& obj, typename Container::iterator& it){
        for(it = objects.begin(); it != objects.end();  ++it){
            if(*it == obj) {
                return false;
            }
        }
        return true;
    }

public:
    SetTemplate() {}

    virtual ~SetTemplate() {}

    SetTemplate(const SetTemplate& other) 
    : objects(other.objects)
    {}

    SetTemplate(const std::shared_ptr<Interface>& obj){
        addFast(obj);
    }




    void add(const std::shared_ptr<Interface>& obj){
        addFast(obj);
    }

    /**
     * @brief Add new event object to the set.
     * 
     * @param event The object that have implemented an event interface.
     * @return true If the operation was unsuccessful. There was already the same event object in the set.
     * @return false Otherwise.
     */
    bool addNew(const std::shared_ptr<Interface>& obj){
        typename Container::iterator it;
        if(!findInstance(obj, it)) {
            addFast(obj);
            return false;
        }
        return true;
    }
    

    /**
     * @brief Remove an event from the set.
     * 
     * @param eventObject 
     * @return true If the operation was unsuccessful. This object was not there.
     * @return false Otherwise.
     */
    bool remove(const std::shared_ptr<Interface>& obj){
        typename Container::iterator it;
        if(findInstance(obj, it)) {
            objects.erase(it);
            return false;
        }
        return true;
    }

    bool empty() const{
        return objects.empty();
    }

    Container getAll() const{
        return objects;
    }

};


#endif