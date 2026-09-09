#include "TrackPredictor.hpp"
#include "common/data/Timestamp.hpp"  // Para diferencia en segundos
#include <cmath> 

namespace Mission_Management {
namespace Tracking {

    Common::Position TrackPredictor::Predict(
        const Common::Track& track,
        const Common::Timestamp& timestamp
    ) const
    {
        // DeltaTiempo en segundos desde último update
        const double deltaSeconds = Common::SecondsBetween(track.lastUpdate, timestamp);
        
        // Cinemática simple: posición + velocidad * tiempo
        return {
            track.position.latitude + track.velocity.speed * deltaSeconds * std::sin(track.velocity.heading),
            track.position.longitude + track.velocity.speed * deltaSeconds * std::cos(track.velocity.heading)
        };
    }
}
}