/*
 * SetTemplate.hpp
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SET_TEMPLATE_HPP
#define TRAFFIC_SIM_SET_TEMPLATE_HPP

#include <list>
#include <memory>


namespace Utils{

    template<typename Interface>
    class SetTemplate{

    protected:
    //typedef typename std::list<std::shared_ptr<Interface>> Container;
        using Container = std::list<std::shared_ptr<Interface>>;

        Container objects_;

        void addFast(const std::shared_ptr<Interface>& obj){
            objects_.push_back(obj);
        }

        bool findInstance(const std::shared_ptr<Interface>& obj, typename Container::iterator& it){
            for(it = objects_.begin(); it != objects_.end();  ++it){
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
        : objects_(other.objects_)
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
         * @param event_object 
         * @return true If the operation was unsuccessful. This object was not there.
         * @return false Otherwise.
         */
        bool remove(const std::shared_ptr<Interface>& obj){
            typename Container::iterator it;
            if(findInstance(obj, it)) {
                objects_.erase(it);
                return false;
            }
            return true;
        }

        bool empty() const{
            return objects_.empty();
        }

        Container& getAll() const{
            return objects_;
        }

        const Container& getAllConst() const{
            return objects_;
        }

        Container getAllCopy() const{
            return objects_;
        }

    };
}

#endif
