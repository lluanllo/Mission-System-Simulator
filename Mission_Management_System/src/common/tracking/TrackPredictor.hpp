#pragma once

#include "common/tracking/Track.hpp"
#include "common/data/Timestamp.hpp"
#include "common/data/TimeUtils.hpp" // Para SecondsBetween

namespace Mission_Management {
    namespace Tracking {
        class TrackPredictor {
            public:
                // Predicción cinemática simple: posición + velocidad * deltaTiempo
                Common::Position Predict(
                    const Common::Track& track,
                    const Common::Timestamp& timestamp
                ) const;
        };
    }
}