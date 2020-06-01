

#include "Exit.h"

using namespace Button;

Exit::Exit(sf::Window& window)
: exit_(window)
{
    std::cout << "Button created" << std::endl;
}

Exit::~Exit() = default;

bool Exit::isButtonChoosed(const sf::Vector2i& position){
    if(position.x < 20 && position.y < 20) return true;
    return false;
}

void Exit::actionPressedButton(){
    return;
}
void Exit::actionReleasedButton(){
    exit_.trigger();
}