#ifndef SCREEN_ID_H
#define SCREEN_ID_H

#include <limits.h>
#include <memory>

//#include "screenInterface.h"

class ScreenID{

/**
 * @brief This is to prevent other derived classes to have an control over private constructor.
 * This class is mean only to be inherited by ScreenInterface class.
 * 
 */
friend class ScreenInteface;

private:
    enum class State{
            Invalid,
            Valid
        };

    State state;
    int myID;
    static int globalID;

    ScreenID(State state); // always State::Valid

public:

    ScreenID(); // nice trick, I hope it works. Always State::Invalid
    ~ScreenID();
    ScreenID(const ScreenID& other);

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
    bool createNew();

    /**
     * @brief Creates a new valid identifier.
     * 
     * @return ScreenID A new identifier.
     */
    static ScreenID newID();
    
    bool isValid() const;

    friend bool operator==(const ScreenID& s1, const ScreenID& s2);
    friend bool operator!=(const ScreenID& s1, const ScreenID& s2);
    friend bool operator<(const ScreenID& s1, const ScreenID& s2);

    /**
     * @brief Return an intiget that identifies this object.
     * 
     * @return int 
     */
    int operator* () const;

    struct less{
        bool operator() (const ScreenID& s1, const ScreenID& s2) const;
    };
};

#endif