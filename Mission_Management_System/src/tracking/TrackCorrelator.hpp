#pragma once

#include <cstdint>
#include <unordered_map>

#include "common/sensor/SensorData.hpp"
#include "common/tracking/Track.hpp"
#include "tracking/CorrelationResult.hpp"

namespace Mission_Management {
namespace Tracking {

    class TrackCorrelator
    {
    public:
        // Umbral de score mínimo para aceptar correlación.
        TrackCorrelator(double thresholdScore = 0.7)
            : m_ThresholdScore(thresholdScore) {}

        CorrelationResult FindMatch(
            const Common::SensorData& sensorData,
            const std::unordered_map<std::uint64_t, Common::Track>& tracks) const;

        double ThresholdScore() const { return m_ThresholdScore; }

    private:
        double m_ThresholdScore;
    };

} }