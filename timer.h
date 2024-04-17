//
// Created by stefan on 17.04.24.
//

#ifndef EMBEDDED_LAB_TIMER_H
#define EMBEDDED_LAB_TIMER_H


#include <iostream>
#include <chrono>

class Timer {
private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point start_;
public:
    // Overloaded Constructors
    explicit Timer(const std::string &name);

    explicit Timer(const char *name);

    ~Timer();


};


#endif //EMBEDDED_LAB_TIMER_H
