#include "TrackPredictor.hpp"

#include "tracking/KinematicTrackPredictor.hpp"

#include <utility>

namespace Mission_Management {
namespace Tracking {

	TrackPredictor::TrackPredictor()
		: m_Predictor(std::make_unique<KinematicTrackPredictor>())
	{
	}

	TrackPredictor::TrackPredictor(std::unique_ptr<ITrackPredictor> predictor)
		: m_Predictor(std::move(predictor))
	{
	}

	Common::Position TrackPredictor::Predict(
		const Common::Track& track,
		double deltaTime) const
	{
		if (!m_Predictor)
			return track.position;

		return m_Predictor->Predict(track, deltaTime);
	}

} }
