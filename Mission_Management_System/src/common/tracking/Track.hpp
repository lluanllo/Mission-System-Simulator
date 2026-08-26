#pragma once

#include <cstdint>
#include <vector>

#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"
#include "common/data/Timestamp.hpp"
#include "common/tracking/Identification.hpp"
#include "common/tracking/ThreatLevel.hpp"
#include "common/sensor/SensorType.hpp"
#include "common/tracking/TrackState.hpp"
#include "common/tracking/TrackHistory.hpp"

namespace Mission_Management {
namespace Common {
    struct Track
    {
        std::uint64_t id;

        Position position;
        Velocity velocity;

        Identification identification;
        ThreatLevel threatLevel;

        TrackState trackState;

        SensorType lastSensor;

        Timestamp lastUpdate;

        std::vector<TrackHistoryPoint> history; // estela temporal del objetivo
    };
} }
