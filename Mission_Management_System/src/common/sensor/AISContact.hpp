#pragma once

#include <string>

#include "common/data/Position.hpp"
#include "common/data/Timestamp.hpp"

namespace Mission_Management {
namespace Common {
    struct AISContact
    {
        std::string mmsi;

        Position position;

        double course;
        double speed;

        Timestamp timestamp;
    };
} }
