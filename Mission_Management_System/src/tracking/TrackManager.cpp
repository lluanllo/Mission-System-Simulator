#include "TrackManager.hpp"
#include "common/sensor/SensorObservation.hpp"
#include "common/data/TimeUtils.hpp"

#include <chrono>
#include <vector>

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

        track.lastUpdate = timestamp;

        // Estela temporal (track trail)
        track.history.push_back({ pos, track.lastUpdate });

        track.predictedPosition = m_Predictor.Predict(track, m_PredictionHorizonSeconds);
    }

    std::vector<Common::Track> TrackManager::PredictWithoutMeasurement(double deltaTime)
    {
        const Common::Timestamp now{ std::chrono::steady_clock::now() };

        std::vector<Common::Track> updates;
        std::vector<std::uint64_t> droppedTrackIds;

        for (auto& pair : m_Tracks)
        {
            auto& track = pair.second;
            track.predictedPosition = m_Predictor.Predict(track, deltaTime);

            const double secondsSinceUpdate = Common::SecondsBetween(track.lastUpdate, now);
            if (secondsSinceUpdate > 5.0)
            {
                track.trackState = Common::TrackState::Dropped;
                updates.push_back(track);
                droppedTrackIds.push_back(pair.first);
                continue;
            }

            if (secondsSinceUpdate > 2.0)
            {
                track.trackState = Common::TrackState::Lost;
            }
            else if (track.updateCount >= 3)
            {
                track.trackState = Common::TrackState::Confirmed;
            }
            else
            {
                track.trackState = Common::TrackState::Tentative;
            }

            updates.push_back(track);
        }

        for (const std::uint64_t id : droppedTrackIds)
            m_Tracks.erase(id);

        return updates;
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