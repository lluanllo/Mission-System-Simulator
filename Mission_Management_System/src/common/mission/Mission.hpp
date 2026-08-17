#pragma once
#include <vector>
#include "common/mission/Waypoint.hpp"

namespace Mission_Management {
namespace Common {
    struct Mission
    {
        std::vector<Waypoint> route;
    };
} }