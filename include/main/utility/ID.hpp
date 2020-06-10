/*
 * ID.hpp
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_ID_HPP
#define TRAFFIC_SIM_ID_HPP

#include <limits.h>
#include <memory>

namespace Utils{

    /**
     * @brief Template of the ID class. Every other ID use this.
     * 
     * @tparam T 
     */
    template<typename T>
    class ID{

    private:
        enum class State{
                INVALID,
                VALID
            };

        State state_;
        int my_ID_;
        static int global_ID_;


        ID(State state) // always State::Valid
        : state_(State::VALID), my_ID_(global_ID_++)
        {}

    public:

        ID() // Always State::Invalid
        : state_(State::INVALID), my_ID_(INT_MIN)
        {}


        virtual ~ID() {}


        ID(const ID& other)
        : state_(other.state_), my_ID_(other.my_ID_)
        {}


        /**
         * @brief Create a new ScreenID in this object. 
         * 
         * @details It will have a unique identifier.
         * This can be performed only if this object has an invalid identifier.
         * Valid identifiers will not be affected by this.
         * 
         * @return true If identifier was valid and operation was not performed.
         * @return false Otherwise.
         */
        bool createNew(){
            if(state_ == State::INVALID){
                my_ID_ = global_ID_++;
                state_ = State::VALID;

                return false;
            }

            return true;
        }

        /**
         * @brief Creates a new valid identifier.
         * 
         * @return ScreenID A new identifier.
         */
        static ID newID(){
            return ID(State::VALID);
        }
        
        bool isValid() const{
            if(state_ == State::VALID)
                return true;
            return false;
        }

        friend bool operator==(const ID& s1, const ID& s2){
            return s1.my_ID_ == s2.my_ID_;
        }

        friend bool operator!=(const ID& s1, const ID& s2){
            return !(s1 == s2);
        }

        friend bool operator<(const ID& s1, const ID& s2){
            return s1.my_ID_ < s2.my_ID_;
        }

        /**
         * @brief Return an intiger that identifies this object.
         * 
         * @return int 
         */
        int operator* () const{
            return my_ID_;
        }

        struct less{
            bool operator() (const ID& s1, const ID& s2) const{
                return s1.my_ID_ < s2.my_ID_;
            }
        };

    };


    template<typename T>
    int ID<T>::global_ID_ = 0;
}


#endif
