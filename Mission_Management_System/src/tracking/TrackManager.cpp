#include "TrackManager.hpp"
#include "common/sensor/SensorObservation.hpp"

namespace Mission_Management {
namespace Tracking {

    namespace {
        Common::Timestamp GetTimestamp(const Common::SensorData& data)
        {
            switch (data.type)
            {
            case Common::SensorType::Radar:
                return data.payload.radar.timestamp;
            case Common::SensorType::ADSB:
                return data.payload.adsb.timestamp;
            case Common::SensorType::AIS:
                return data.payload.ais.timestamp;
            default:
                return {};
            }
        }
    }

    Common::Track TrackManager::Process(
        const Common::SensorData& data,
        const TrackCorrelator& correlator)
    {
        auto match = correlator.FindMatch(data, m_Tracks);

        if (match.has_value())
        {
            auto& track = m_Tracks.at(*match);
            UpdateTrack(track, data);
            return track;
        }

        auto track = CreateTrack(data);
        m_Tracks.emplace(track.id, track);
        return track;
    }

    Common::Track TrackManager::CreateTrack(const Common::SensorData& data)
    {
        const Common::Position& pos = Common::GetPosition(data);
        const Common::Velocity& vel = Common::GetVelocity(data);

        Common::Track t{};
        t.id = GenerateTrackId();
        t.position = pos;
        t.velocity = vel;
        t.identification = Common::Identification::Unknown;
        t.threatLevel = Common::ThreatLevel::Unknown;
        t.trackState = Common::TrackState::Tentative;
        t.updateCount = 1;
        t.lastSensor = data.type;
        t.lastUpdate = GetTimestamp(data);
        t.predictedPosition = pos;
        t.history.push_back({ pos, t.lastUpdate });

        return t;
    }

    void TrackManager::UpdateTrack(Common::Track& track, const Common::SensorData& data)
    {
        const Common::Position& pos = Common::GetPosition(data);
        const Common::Velocity& vel = Common::GetVelocity(data);

        track.position = pos;
        track.velocity = vel;
        track.lastSensor = data.type;
        const Common::Timestamp timestamp = GetTimestamp(data);

        // Doctrina de estado (prototipo, no doctrina operacional real):
        // 1 contacto => Tentative, >= 3 => Confirmed
        track.updateCount++;
        if (track.updateCount >= 3)
            track.trackState = Common::TrackState::Confirmed;

        // Estela temporal (track trail)
        TrackPredictor predictor;
        track.predictedPosition = predictor.Predict(track, timestamp);
        track.lastUpdate = timestamp;
        track.history.push_back({ pos, track.lastUpdate });
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