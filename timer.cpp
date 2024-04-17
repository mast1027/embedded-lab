//
// Created by stefan on 17.04.24.
//

#include "timer.h"

// Constructor for std::string
Timer::Timer(const std::string &name) : name_(name), start_(std::chrono::high_resolution_clock::now()) {}

// Constructor for const char*
Timer::Timer(const char *name) : Timer(std::string(name)) {}  // Delegating to std::string constructor

Timer::~Timer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
    std::cout << "---------> " << name_ << ": " << duration << " microseconds.\n";
}

