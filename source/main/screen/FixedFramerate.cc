/*
 * FixedFramerate.cc
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_FIXED_FRAMERATE_CPP
#define TRAFFIC_SIM_FIXED_FRAMERATE_CPP

#include "FixedFramerate.h"

FixedFramerate::FixedFramerate(const Framerate& framerate)
    :set_frame_(1.0 / framerate), 
    sum_of_diff_time_(), 
    real_diff_(0.0),
    counted_frames_per_sec_(0), 
    counted_frames_per_sec_previous_(0), 
    prev_is_set_(false)
{}

FixedFramerate::~FixedFramerate()
{}

FixedFramerate::FixedFramerate(const FixedFramerate& other)
    :set_frame_(other.set_frame_), 
    sum_of_diff_time_(other.sum_of_diff_time_), 
    real_diff_(other.real_diff_),
    counted_frames_per_sec_(other.counted_frames_per_sec_), 
    counted_frames_per_sec_previous_(other.counted_frames_per_sec_previous_), 
    prev_is_set_(other.prev_is_set_)
{}

FixedFramerate::FixedFramerate(FixedFramerate&& other)
    :set_frame_(other.set_frame_), 
    sum_of_diff_time_(std::move(other.sum_of_diff_time_)), 
    real_diff_(other.real_diff_),
    counted_frames_per_sec_(other.counted_frames_per_sec_), 
    counted_frames_per_sec_previous_(other.counted_frames_per_sec_previous_), 
    prev_is_set_(other.prev_is_set_)
{}

FixedFramerate& FixedFramerate::operator=(FixedFramerate&& other){
    set_frame_ = other.set_frame_;
    sum_of_diff_time_ = std::move(other.sum_of_diff_time_);
    real_diff_ = other.real_diff_;
    counted_frames_per_sec_ = other.counted_frames_per_sec_;
    counted_frames_per_sec_previous_ = other.counted_frames_per_sec_previous_;
    prev_is_set_ = other.prev_is_set_;
    return *this;
}

void FixedFramerate::checkTime(){
    if(set_frame_ == 0.0f) return;
    if(!prev_is_set_){
        prev_is_set_ = true;
        setPoint();
        return;
    }

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<Framerate> diff;
    while((diff = now - prevoius_time_).count() <= set_frame_) {
        now = std::chrono::steady_clock::now();
    }

    real_diff_ = diff.count();

    sum_of_diff_time_ += diff.count();
    ++counted_frames_per_sec_;
    if(sum_of_diff_time_ >= 1.0) {
        sum_of_diff_time_ = 0.0;
        counted_frames_per_sec_previous_ = counted_frames_per_sec_;
        counted_frames_per_sec_ = 0;
    }

    setPoint();
}

void FixedFramerate::setFramerate(const Framerate& framerate){
    set_frame_ = 1.0 / framerate;
}

void FixedFramerate::setPoint(){
    prevoius_time_ = std::chrono::steady_clock::now();
}

void FixedFramerate::reset(){
    set_frame_ = 0.0f;
}

unsigned int FixedFramerate::getRealFramerate() const{
    return counted_frames_per_sec_previous_;
}

FixedFramerate::Framerate FixedFramerate::getFramerate() const{
    return set_frame_;
}

FixedFramerate::Framerate FixedFramerate::getRealDiff() const{
    return real_diff_;
}

#endif