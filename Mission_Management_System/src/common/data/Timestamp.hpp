#pragma once

#include <chrono>

namespace Mission_Management {
namespace Common {
    struct Timestamp {
        using Clock = std::chrono::steady_clock;
        using TimePoint = Clock::time_point;

        Timestamp() = default;
        Timestamp(TimePoint value) : time(value) {}

        TimePoint time{};
    };

} }
