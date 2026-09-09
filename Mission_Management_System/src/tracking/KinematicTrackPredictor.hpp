#pragma once

#include "tracking/ITrackPredictor.hpp"

namespace Mission_Management {
namespace Tracking {

	class KinematicTrackPredictor final : public ITrackPredictor
	{
	public:
		Common::Position Predict(
			const Common::Track& track,
			double deltaTime) const override;
	};

} }
