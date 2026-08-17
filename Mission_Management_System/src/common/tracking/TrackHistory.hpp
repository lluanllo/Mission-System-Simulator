#pragma once
#include <vector>
#include "common/data/Position.hpp"
#include "common/data/Timestamp.hpp"

namespace Mission_Management {
namespace Common {
    struct TrackHistoryPoint
    {
        Position position;
        Timestamp timestamp;
    };

    struct TrackHistory
    {
        std::vector<TrackHistoryPoint> points;
    };
} }