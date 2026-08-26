#include "TrackManager.hpp"
#include <cmath>

namespace Mission_Management {
namespace Tracking {

    Common::Track TrackManager::ProcessRadarContact(const Common::RadarContact& contact)
    {
        for (auto& pair : m_Tracks)
        {
            auto& track = pair.second;
            const double latDiff = std::abs(track.position.latitude - contact.position.latitude);
            const double lonDiff = std::abs(track.position.longitude - contact.position.longitude);

            if (latDiff < 0.01 && lonDiff < 0.01)
            {
                track.position = contact.position;
                track.velocity = contact.velocity;
                track.lastSensor = Common::SensorType::Radar;
                track.lastUpdate = contact.timestamp;

                // Varios contactos consecutivos -> Confirmed
                track.trackState = Common::TrackState::Confirmed;

                // Se construye la estela temporal del track
                track.history.push_back({ contact.position, contact.timestamp });

                return track;
            }
        }

        Common::Track track{};

        track.id = GenerateTrackId();
        track.position = contact.position;
        track.velocity = contact.velocity;
        track.identification = Common::Identification::Unknown;
        track.threatLevel = Common::ThreatLevel::Unknown;
        track.trackState = Common::TrackState::Tentative;
        track.lastSensor = Common::SensorType::Radar;
        track.lastUpdate = contact.timestamp;

        // Primer punto de la estela temporal
        track.history.push_back({ contact.position, contact.timestamp });

        m_Tracks.emplace(track.id, track);

        return track;
    }

    const std::unordered_map<std::uint64_t, Common::Track>& TrackManager::GetTracks() const
    {
        return m_Tracks;
    }

    std::uint64_t TrackManager::GenerateTrackId()
    {
        return m_NextTrackId++;
    }

} }