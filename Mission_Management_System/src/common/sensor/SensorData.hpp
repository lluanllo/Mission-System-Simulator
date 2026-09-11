#pragma once

#include <variant>

#include "common/sensor/SensorType.hpp"
#include "common/sensor/RadarContact.hpp"
#include "common/sensor/ADSBContact.hpp"
#include "common/sensor/AISContact.hpp"

namespace Mission_Management {
namespace Common {
    using SensorPayload = std::variant<RadarContact, ADSBContact, AISContact>;

    struct SensorData
    {
        SensorType type;
        SensorPayload payload;
    };
} }
