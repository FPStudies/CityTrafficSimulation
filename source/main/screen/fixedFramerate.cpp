#ifndef ZPR_TRAFFIC_SIM_FIXED_FRAMERATE_CPP
#define ZPR_TRAFFIC_SIM_FIXED_FRAMERATE_CPP

#include "fixedFramerate.h"

FixedFramerate::FixedFramerate(const Framerate& framerate)
    :setFrame(1.0 / framerate), 
    sumOfDiffTime(), 
    realDiff(0.0),
    countedFramesPerSec(0), 
    countedFramesPerSecPrevious(0), 
    prevIsSet(false)
{}

FixedFramerate::~FixedFramerate()
{}

FixedFramerate::FixedFramerate(const FixedFramerate& other)
    :setFrame(other.setFrame), 
    sumOfDiffTime(other.sumOfDiffTime), 
    realDiff(other.realDiff),
    countedFramesPerSec(other.countedFramesPerSec), 
    countedFramesPerSecPrevious(other.countedFramesPerSecPrevious), 
    prevIsSet(other.prevIsSet)
{}

FixedFramerate::FixedFramerate(FixedFramerate&& other)
    :setFrame(other.setFrame), 
    sumOfDiffTime(std::move(other.sumOfDiffTime)), 
    realDiff(other.realDiff),
    countedFramesPerSec(other.countedFramesPerSec), 
    countedFramesPerSecPrevious(other.countedFramesPerSecPrevious), 
    prevIsSet(other.prevIsSet)
{}

FixedFramerate& FixedFramerate::operator=(FixedFramerate&& other){
    setFrame = other.setFrame;
    sumOfDiffTime = std::move(other.sumOfDiffTime);
    realDiff = other.realDiff;
    countedFramesPerSec = other.countedFramesPerSec;
    countedFramesPerSecPrevious = other.countedFramesPerSecPrevious;
    prevIsSet = other.prevIsSet;
    return *this;
}

void FixedFramerate::checkTime(){
    if(setFrame == 0.0f) return;
    if(!prevIsSet){
        prevIsSet = true;
        setPoint();
        return;
    }

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<Framerate> diff;
    while((diff = now - prevoiusTime).count() <= setFrame) {
        now = std::chrono::steady_clock::now();
    }

    realDiff = diff.count();

    sumOfDiffTime += diff.count();
    ++countedFramesPerSec;
    if(sumOfDiffTime >= 1.0) {
        sumOfDiffTime = 0.0;
        countedFramesPerSecPrevious = countedFramesPerSec;
        countedFramesPerSec = 0;
    }

    setPoint();
}

void FixedFramerate::setFramerate(const Framerate& framerate){
    setFrame = framerate;
}

void FixedFramerate::setPoint(){
    prevoiusTime = std::chrono::steady_clock::now();
}

void FixedFramerate::reset(){
    setFrame = 0.0f;
}

unsigned int FixedFramerate::getRealFramerate() const{
    return countedFramesPerSecPrevious;
}

FixedFramerate::Framerate FixedFramerate::getFramerate() const{
    return setFrame;
}

FixedFramerate::Framerate FixedFramerate::getRealDiff() const{
    return realDiff;
}

#endif