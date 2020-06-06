/*
 * View.h
 *
 *      Author: Kordowski Mateusz
 */


#include "View.h"

using namespace Screen;

View::View(const std::string& name, const sf::FloatRect& rect)
: view_(rect), name_(name)
{}


std::shared_ptr<View> View::create(const std::string& name, const sf::FloatRect& rect){
    auto tmp_ptr = new View(name, rect);
    return std::shared_ptr<View>(tmp_ptr);
}

View::~View() = default;

sf::View& View::getView(){
    return view_;
}

const sf::View& View::getView_const() const{
    return view_;
}

std::string& View::getName(){
    return name_;
}

const std::string& View::getName() const{
    return name_;
}

void View::reset(const sf::FloatRect& rect){
    view_.reset(rect);
}
