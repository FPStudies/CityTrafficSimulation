
#include "thread/Draw.h"

Thread::Draw::Draw(const std::shared_ptr<sf::RenderWindow>& window, ::Draw::Manager& drawManager, ::Synch::Loop& loopSynch, Communication& comm)
: ::Thread::Inteface(comm),
window_(window),
draw_manager_(drawManager),
loop_synch_(loopSynch)
{}

Thread::Draw::~Draw() = default;

void Thread::Draw::operator()(){
    while(window_->isOpen() && thread_communication_.is_active_){
        loop_synch_.enter();
        
        window_->clear();
        draw_manager_.drawAll();
        window_->display();    
    }
}