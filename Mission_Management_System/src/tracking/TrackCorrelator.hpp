#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>

#include "common/sensor/SensorData.hpp"
#include "common/tracking/Track.hpp"

namespace Mission_Management {
namespace Tracking {

    class TrackCorrelator
    {
    public:
        // Umbral de distancia (km). 5 km es un valor razonable para radar a media distancia.
        TrackCorrelator(double thresholdKm = 5.0)
            : m_ThresholdKm(thresholdKm) {}

        // ¿Existe un track compatible con esta observación?
        // Devuelve el id del track con menor distancia (greedy), o std::nullopt si ninguno.
        std::optional<std::uint64_t> FindMatch(
            const Common::SensorData& sensorData,
            const std::unordered_map<std::uint64_t, Common::Track>& tracks) const;

        double ThresholdKm() const { return m_ThresholdKm; }

    private:
        double m_ThresholdKm;
    };

} }