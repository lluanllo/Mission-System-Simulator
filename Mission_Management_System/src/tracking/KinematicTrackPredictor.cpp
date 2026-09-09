#include "KinematicTrackPredictor.hpp"

#include <cmath>

namespace Mission_Management {
namespace Tracking {

	Common::Position KinematicTrackPredictor::Predict(
		const Common::Track& track,
		double deltaTime) const
	{
		if (deltaTime <= 0.0)
			return track.position;

		constexpr double Pi = 3.14159265358979323846;
		constexpr double KnotsToMetersPerSecond = 1852.0 / 3600.0;
		constexpr double MetersPerDegree = 111320.0;

		const double speedMs = track.velocity.speed * KnotsToMetersPerSecond;
		const double distanceMeters = speedMs * deltaTime;

		const double headingRad = track.velocity.heading * Pi / 180.0;
		const double northMeters = std::cos(headingRad) * distanceMeters;
		const double eastMeters = std::sin(headingRad) * distanceMeters;

		Common::Position predicted = track.position;
		predicted.latitude += northMeters / MetersPerDegree;

		const double latitudeRad = predicted.latitude * Pi / 180.0;
		const double lonDenominator = MetersPerDegree * std::cos(latitudeRad);
		if (std::abs(lonDenominator) > 1e-9)
			predicted.longitude += eastMeters / lonDenominator;

		predicted.altitude += track.velocity.climbRate * (deltaTime / 60.0);
		return predicted;
	}

} }
