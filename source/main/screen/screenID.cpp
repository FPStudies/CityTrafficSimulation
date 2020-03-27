#ifndef SCREEN_ID_CPP
#define SCREEN_ID_CPP

#include "screenID.h"

int ScreenID::globalID = 0;

ScreenID::ScreenID(State state)
: state(State::Valid), myID(globalID)
{
    ++globalID;
}

ScreenID::ScreenID()
: state(State::Invalid), myID(INT_MIN)
{}

ScreenID::~ScreenID() {}

ScreenID::ScreenID(const ScreenID& other)
: state(other.state), myID(other.myID)
{}

bool ScreenID::createNew(){
    if(state == State::Invalid){
        myID = globalID++;
        state = State::Valid;

        return false;
    }

    return true;
}

ScreenID ScreenID::newID(){
    return ScreenID(State::Valid);
}

bool ScreenID::isValid() const{
    if(state == State::Valid) return true;
    return false;
}

bool operator==(const ScreenID& s1, const ScreenID& s2){
    return s1.myID == s2.myID;
}

bool operator!=(const ScreenID& s1, const ScreenID& s2){
    return !(s1 == s2);
}

bool operator<(const ScreenID& s1, const ScreenID& s2){
    return s1.myID < s2.myID;
}

int ScreenID::operator* () const{
    return myID;
}

bool ScreenID::less::operator() (const ScreenID& s1, const ScreenID& s2) const{
    return s1.myID < s2.myID;
}

#endif