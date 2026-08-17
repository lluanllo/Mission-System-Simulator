#pragma once

#include "core/events/Event.hpp"
#include "common/sensor/SensorData.hpp"

namespace Mission_Management {
namespace Common {

    struct SensorDataReceivedEvent
        : public Core::TypedEvent<SensorDataReceivedEvent>
    {
        SensorData data;
    };

} }