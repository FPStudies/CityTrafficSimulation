/*
 * MappingTemplate.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAPPING_TEMPLATE_H
#define TRAFFIC_SIM_MAPPING_TEMPLATE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <memory>

#include "../trigger/event/Interface.h"


namespace Control{    

    template<typename TemplateControls, typename ChildClass>
    class MappingTemplate{
        std::map<TemplateControls, std::vector<std::shared_ptr<::Trigger::Event::Interface>> > mapping_;

    public:
        MappingTemplate()
        : mapping_()
        {}

        ~MappingTemplate()
        {}

        MappingTemplate(const MappingTemplate& other)
        : mapping_(other.mapping_)
        {}

        MappingTemplate(MappingTemplate&& other)
        : mapping_(std::move(other.mapping_))
        {}

        MappingTemplate& operator=(MappingTemplate&& other){
            mapping_ = std::move(other.mapping_);
            return *this;
        }

        bool operator==(const MappingTemplate& other) const{
            return mapping_.size() == other.mapping_.size() &&
                std::equal(mapping_.begin(), mapping_.end(), other.mapping_.begin());
        }

        /**
         * @brief Adds a new trigger to the control.
         * 
         * @param control What control event should trigger other event.
         * @param event Shared resource. It can be used in different events.
         * @return true - this control already have this event.
         * @return false - event was added to provided control.
         */
        bool addControl(TemplateControls control, const std::shared_ptr<::Trigger::Event::Interface>& event){
            auto& it = mapping_[control];

            for(auto i = it.cbegin(); i != it.cend(); ++i){
                if((*i) == event)
                    return true;
            }
            it.push_back(event);
            
            return false;
        }

        /**
         * @brief Adds a new trigger to the control.
         * It does not check errors so it is fast.
         * 
         * @param control What control event should trigger other event.
         * @param event Shared resource. It can be used in different events.
         */
        void addControlFast(TemplateControls control, const std::shared_ptr<::Trigger::Event::Interface>& event){
            mapping_[control].push_back(event);
        }

        /**
         * @brief Delete trigger from control.
         * 
         * @param control Where the trigger is.
         * @param event Must be the same trigger as was put.
         * @return true - this control does not have this trigger.
         * @return false - event was deleted from provided control.
         */
        bool removeControl(TemplateControls control, const std::shared_ptr<::Trigger::Event::Interface>& event){
            auto it = mapping_.find(control);
            if(it == mapping_.end()) return true;

            auto i_end = (*it).second.end();
            for(auto i = (*it).second.begin(); i != i_end; ++i){
                if((*i) == event){
                    (*it).second.erase(i);
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief Delete trigger from control.
         * It does not check errors so it is fast.
         * 
         * @param control Where the trigger is.
         * @param event Must be the same trigger as was put.
         */
        void removeControlFast(TemplateControls control, const std::shared_ptr<::Trigger::Event::Interface>& event){
            auto it = mapping_.find(control);
            auto i_end = (*it).second.end();
            for(auto i = (*it).second.begin(); i != i_end; ++i){
                if((*i) == event){
                    (*it).second.erase(i);
                    return;
                }
            }
        }

        /**
         * @brief Remove all of the triggers that were mapped on the provided control.
         * 
         * @param control Where the triggers should be.
         * @return true - control has not had any triggers.
         * @return false - all triggers were removed.
         */
        void removeControl(TemplateControls control){
            auto it = mapping_.find(control);
            if(it == mapping_.end()) return;

            it->second.clear();
        }

        /**
         * @brief Trigger the events assigned to this control.
         * 
         * @param control Where the triggers are.
         */
        void trigger(sf::RenderWindow &window, TemplateControls copyControl, const sf::Event& event){
            auto it = mapping_.find(copyControl);
            if(it == mapping_.end()) return;

            auto i_end = it->second.end();
            for(auto i = it->second.begin(); i != i_end; ++i){
                
                (*i)->trigger(window, event);
            }
        }
        
    };

}



#endif