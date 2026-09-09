#include "TimeUtils.hpp"
#include <chrono>
#include <cmath> 

namespace Mission_Management {
    namespace Common {
        double SecondsBetween(const Timestamp& a, const Timestamp& b) {
            const auto duration = b.time - a.time;
            return std::chrono::duration<double>(duration).count();
        }
    }
}