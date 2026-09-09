#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "common/tracking/Track.hpp"
#include "common/sensor/RadarContact.hpp"
#include "tracking/TrackPredictor.hpp"
#include "tracking/TrackCorrelator.hpp"

namespace Mission_Management {
namespace Tracking {

    class TrackManager
    {
    public:
        // Punto de entrada único del pipeline.
        // correlator decide "¿a qué track?"; el manager decide "¿crear o actualizar?".
        Common::Track Process(
            const Common::SensorData& data,
            const TrackCorrelator& correlator);

        std::vector<Common::Track> PredictWithoutMeasurement(double deltaTime);

        const std::unordered_map<std::uint64_t, Common::Track>& GetTracks() const;

    private:
        Common::Track CreateTrack(const Common::SensorData& data);
        void          UpdateTrack(Common::Track& track, const Common::SensorData& data);

        std::uint64_t GenerateTrackId();

        std::unordered_map<std::uint64_t, Common::Track> m_Tracks;
        std::uint64_t m_NextTrackId = 1;
        TrackPredictor m_Predictor;
        double m_PredictionHorizonSeconds = 2.0;
    };

} }