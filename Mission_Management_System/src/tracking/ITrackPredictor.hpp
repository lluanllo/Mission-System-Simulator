#pragma once

#include "common/data/Position.hpp"
#include "common/tracking/Track.hpp"

namespace Mission_Management {
namespace Tracking {

	class ITrackPredictor
	{
	public:
		virtual ~ITrackPredictor() = default;

		virtual Common::Position Predict(
			const Common::Track& track,
			double deltaTime) const = 0;
	};

} }
