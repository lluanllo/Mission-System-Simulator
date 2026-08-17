#pragma once

#include <string>

#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"
#include "common/data/Timestamp.hpp"

namespace Mission_Management {
namespace Common {
    struct ADSBContact
    {
        std::string callsign;
        std::string icao24;

        Position position;
        Velocity velocity;

        Timestamp timestamp;
    };
} }
