#pragma once

#include <cstdint>
#include <optional>
#include <string>
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
        Position predictedPosition;
        Velocity velocity;

        Identification identification;
        ThreatLevel threatLevel;

        TrackState trackState;

        std::uint32_t updateCount = 0;   // contactos consecutivos asociado -> Confirmed

        SensorType lastSensor;
        std::vector<SensorType> sources;

        std::optional<std::string> icao24;

        Timestamp lastUpdate;

        std::vector<TrackHistoryPoint> history; // estela temporal del objetivo
    };
} }
