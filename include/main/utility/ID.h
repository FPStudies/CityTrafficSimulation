#ifndef ZPR_TRAFFIC_SIM_ID_H
#define ZPR_TRAFFIC_SIM_ID_H

#include <limits.h>
#include <memory>

template<typename T>
class ID{

private:
    enum class State{
            Invalid,
            Valid
        };

    State state;
    int myID;
    static int globalID;


    ID(State state) // always State::Valid
    : state(State::Valid), myID(globalID++)
    {}

public:

    ID() // Always State::Invalid
    : state(State::Invalid), myID(INT_MIN)
    {}


    virtual ~ID() {}


    ID(const ID& other)
    : state(other.state), myID(other.myID)
    {}


    /**
     * @brief Create a new ScreenID in this object. 
     * 
     * @details It will have a unique identifier.
     * This can be performed only f this object have invalid identifier.
     * Valid identifiers will not be affected by this.
     * 
     * @return true If identifier was valid and operation was not performed.
     * @return false Otherwise.
     */
    bool createNew(){
        if(state == State::Invalid){
            myID = globalID++;
            state = State::Valid;

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
        return ID(State::Valid);
    }
    
    bool isValid() const{
        if(state == State::Valid) return true;
        return false;
    }

    friend bool operator==(const ID& s1, const ID& s2){
        return s1.myID == s2.myID;
    }

    friend bool operator!=(const ID& s1, const ID& s2){
        return !(s1 == s2);
    }

    friend bool operator<(const ID& s1, const ID& s2){
        return s1.myID < s2.myID;
    }

    /**
     * @brief Return an intiget that identifies this object.
     * 
     * @return int 
     */
    int operator* () const{
        return myID;
    }

    struct less{
        bool operator() (const ID& s1, const ID& s2) const{
            return s1.myID < s2.myID;
        }
    };

};


template<typename T>
int ID<T>::globalID = 0;



#endif