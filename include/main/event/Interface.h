/*
 * Interface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_EVENT_INTERFACE_CPP
#define TRAFFIC_SIM_MAIN_EVENT_INTERFACE_CPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace Event{

    class Interface{
    public:
        enum class Type: uint8_t{
            Normal,
            Toggle
        };

    private:
        virtual Interface* clone_impl() const = 0;

    public:
        Interface() = default;
        virtual ~Interface() = default;        

        virtual Type getType() const{
            return Type::Normal;
        }

        /**
         * @brief Do some action based on the event.
         * 
         * @param window Where the event was fetched.
         * @param event Fetched event.
         */
        virtual void run(sf::RenderWindow& window, const sf::Event& event) = 0;

        /**
         * @brief Simple method to copy object.
         * Return the same object type as your higher class.
         * 
         * @return Interface* 
         */
        std::unique_ptr<Interface> clone() const{
            return std::unique_ptr<Interface>(this->clone_impl());
        }

        /**
         * @brief Method to check if the two events are the same.
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        virtual bool equals(const Interface& other) const = 0;

        Interface(const Interface&) = delete;
        Interface(const Interface&&) = delete;

    };

}

#endif
