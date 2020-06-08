


#include "action/NextScreen.h"

using namespace Trigger::Action;

NextScreen* NextScreen::clone_impl() const{
    return new NextScreen(*this);
}

std::unique_ptr<NextScreen> NextScreen::clone() const{
    return std::unique_ptr<NextScreen>(this->clone_impl());
}

NextScreen::NextScreen(const ScreenID& ID)
: screen_ID_(ID)
{}

NextScreen::~NextScreen() = default;

NextScreen::NextScreen(const NextScreen& other)
: screen_ID_(other.screen_ID_)
{}

NextScreen::NextScreen(const NextScreen&& other)
: screen_ID_(std::move(other.screen_ID_))
{}

void NextScreen::trigger(){
    ScreenInteface::requestForNextScreen(screen_ID_);
}

bool NextScreen::equals(const Interface& other) const{
    if(typeid(NextScreen) == typeid(other) && (dynamic_cast<const NextScreen&>(other).screen_ID_) == (this->screen_ID_))
        return true;
    return false;
}