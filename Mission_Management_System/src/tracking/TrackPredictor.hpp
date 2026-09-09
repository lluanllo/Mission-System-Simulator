#pragma once

#include <memory>

#include "tracking/ITrackPredictor.hpp"

namespace Mission_Management {
namespace Tracking {

	class TrackPredictor
	{
	public:
		TrackPredictor();
		explicit TrackPredictor(std::unique_ptr<ITrackPredictor> predictor);

		Common::Position Predict(
			const Common::Track& track,
			double deltaTime) const;

	private:
		std::unique_ptr<ITrackPredictor> m_Predictor;
	};

} }
