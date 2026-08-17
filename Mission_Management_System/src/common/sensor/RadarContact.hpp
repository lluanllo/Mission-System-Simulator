#pragma once

#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"
#include "common/data/Timestamp.hpp"

namespace Mission_Management {
namespace Common {
    struct RadarContact
    {
        Position position;
        Velocity velocity;

        double radarCrossSection;

        Timestamp timestamp;
    };
} }
