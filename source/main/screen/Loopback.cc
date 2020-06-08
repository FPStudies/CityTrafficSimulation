

#include "Loopback.h"

using namespace Screen;

Loopback::Loopback() = default;

Loopback::~Loopback() = default;

bool Loopback::isAnyoneWaiting(){
    if(request_for_next_screen_.empty()) return false;

    return true;
}

void Loopback::requestForNextScreen(const ScreenID& ID){
    request_for_next_screen_.push_back(ID);
}

void Loopback::clearAll(){
    request_for_next_screen_.clear();
}