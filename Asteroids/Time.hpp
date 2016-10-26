#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Time = Clock::time_point;
using Duration = Clock::duration;

using namespace std::chrono_literals;

#endif
