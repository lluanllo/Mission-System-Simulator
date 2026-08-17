#pragma once

#include "common/sensor/SensorType.hpp"
#include "common/sensor/RadarContact.hpp"
#include "common/sensor/ADSBContact.hpp"
#include "common/sensor/AISContact.hpp"

namespace Mission_Management {
namespace Common {
    struct SensorPayload {
        RadarContact radar;
        ADSBContact adsb;
        AISContact ais;

        SensorPayload(const RadarContact& r) : radar(r) {}
        SensorPayload(const ADSBContact& a) : adsb(a) {}
        SensorPayload(const AISContact& a) : ais(a) {}
        SensorPayload() = default;
    };

    struct SensorData
    {
        SensorType type;
        SensorPayload payload;
    };
} }
