#include "TrackCorrelator.hpp"
#include "common/data/Geo.hpp"
#include "common/sensor/SensorObservation.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace Mission_Management {
namespace Tracking {

    namespace {
        double Clamp01(double value)
        {
            return std::max(0.0, std::min(1.0, value));
        }

        double HeadingDifference(double a, double b)
        {
            double diff = std::fmod(std::fabs(a - b), 360.0);
            if (diff > 180.0)
                diff = 360.0 - diff;
            return diff;
        }
    }

    CorrelationResult TrackCorrelator::FindMatch(
        const Common::SensorData& sensorData,
        const std::unordered_map<std::uint64_t, Common::Track>& tracks) const
    {
        const Common::Position& observedPosition = Common::GetPosition(sensorData);
        const Common::Velocity& observedVelocity = Common::GetVelocity(sensorData);

        CorrelationResult bestResult{};
        double bestScore = 0.0;

        for (const auto& pair : tracks)
        {
            const Common::Track& track = pair.second;
            if (track.trackState == Common::TrackState::Dropped)
                continue;

            constexpr double PositionScaleKm = 5.0;
            const double distanceKm = Common::ApproximateDistanceKm(track.predictedPosition, observedPosition);
            const double positionScore = Clamp01(1.0 - (distanceKm / PositionScaleKm));

            const double speedDiff = std::fabs(track.velocity.speed - observedVelocity.speed);
            const double speedScore = Clamp01(1.0 - (speedDiff / 50.0));

            const double headingDiff = HeadingDifference(track.velocity.heading, observedVelocity.heading);
            const double headingScore = Clamp01(1.0 - (headingDiff / 180.0));

            const double totalScore = (positionScore * 0.5) + (speedScore * 0.25) + (headingScore * 0.25);

            if (totalScore > bestScore)
            {
                bestScore = totalScore;
                bestResult.trackId = pair.first;
                bestResult.score = totalScore;
                bestResult.matched = totalScore >= m_ThresholdScore;
            }
        }

        if (!bestResult.matched)
            return {};

        return bestResult;
    }

} }