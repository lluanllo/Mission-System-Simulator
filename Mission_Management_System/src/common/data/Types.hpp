#pragma once
#include <cstdint>

namespace Mission_Management {

    enum class Identification {
        Unknown,
        Friendly,
        Hostile,
        Neutral
    };

    enum class ThreatLevel {
        None,
        Low,
        Medium,
        High,
        Severe
    };

    enum class SensorType {
        Radar,
        ADSB,
        AIS,
        IFF,
        EOIR
    };

}