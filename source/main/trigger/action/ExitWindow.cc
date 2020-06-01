


#include "action/ExitWindow.h"

using namespace Trigger::Action;

ExitWindow* ExitWindow::clone_impl() const{
    return new ExitWindow(*this);
}

std::unique_ptr<ExitWindow> ExitWindow::clone() const{
    return std::unique_ptr<ExitWindow>(this->clone_impl());
}

ExitWindow::ExitWindow(sf::Window& window)
: window_(window)
{}

ExitWindow::~ExitWindow() = default;

ExitWindow::ExitWindow(const ExitWindow& other)
: window_(other.window_)
{}

ExitWindow::ExitWindow(const ExitWindow&& other)
: window_(other.window_)
{}

void ExitWindow::trigger(){
    window_.close();
}

bool ExitWindow::equals(const Interface& other) const{
    if(typeid(ExitWindow) == typeid(other) && &(dynamic_cast<const ExitWindow&>(other).window_) == &(this->window_))
        return true;
    return false;
}