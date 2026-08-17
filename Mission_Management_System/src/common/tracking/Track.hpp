#pragma once

#include <cstdint>

#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"
#include "common/data/Timestamp.hpp"
#include "common/tracking/Identification.hpp"
#include "common/tracking/ThreatLevel.hpp"
#include "common/sensor/SensorType.hpp"

namespace Mission_Management {
namespace Common {
    struct Track
    {
        std::uint64_t id;

        Position position;
        Velocity velocity;

        Identification identification;
        ThreatLevel threatLevel;

        SensorType lastSensor;

        Timestamp lastUpdate;
    };
} }
