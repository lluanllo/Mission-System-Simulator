#include "TrackCorrelator.hpp"
#include "common/data/Geo.hpp"
#include "common/sensor/SensorObservation.hpp"

#include <limits>

namespace Mission_Management {
namespace Tracking {

    std::optional<std::uint64_t> TrackCorrelator::FindMatch(
        const Common::SensorData& sensorData,
        const std::unordered_map<std::uint64_t, Common::Track>& tracks) const
    {
        const Common::Position& observed = Common::GetPosition(sensorData);

        std::uint64_t bestId = 0;
        double bestDist = std::numeric_limits<double>::infinity();
        bool hasCandidate = false;

        for (const auto& pair : tracks)
        {
            const Common::Track& t = pair.second;
            const double d = Common::ApproximateDistanceKm(t.position, observed);

            if (d < m_ThresholdKm && d < bestDist)
            {
                bestDist = d;
                bestId = pair.first;
                hasCandidate = true;
            }
        }

        return hasCandidate ? std::optional<std::uint64_t>(bestId)
                            : std::nullopt;
    }

} }