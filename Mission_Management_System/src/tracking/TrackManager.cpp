#include "TrackManager.hpp"
#include "common/sensor/SensorObservation.hpp"
#include "common/data/TimeUtils.hpp"

#include <algorithm>
#include <chrono>
#include <vector>

namespace Mission_Management {
namespace Tracking {

    namespace {
        Common::Timestamp GetTimestamp(const Common::SensorData& data)
        {
            if (const auto* radar = std::get_if<Common::RadarContact>(&data.payload))
                return radar->timestamp;
            if (const auto* adsb = std::get_if<Common::ADSBContact>(&data.payload))
                return adsb->timestamp;
            if (const auto* ais = std::get_if<Common::AISContact>(&data.payload))
                return ais->timestamp;

            return {};
        }
    }

    Common::Track TrackManager::Process(
        const Common::SensorData& data,
        const CorrelationResult& correlationResult)
    {
        if (correlationResult.matched)
        {
            auto trackIt = m_Tracks.find(correlationResult.trackId);
            if (trackIt != m_Tracks.end())
            {
                UpdateTrack(trackIt->second, data);
                return trackIt->second;
            }
        }

        auto track = CreateTrack(data);
        m_Tracks.emplace(track.id, track);
        return track;
    }

    namespace {
        void RegisterSource(Common::Track& track, Common::SensorType sensorType)
        {
            if (std::find(track.sources.begin(), track.sources.end(), sensorType) == track.sources.end())
                track.sources.push_back(sensorType);
        }

        void UpdateIdentity(Common::Track& track, const Common::SensorData& data)
        {
            if (const auto* adsb = std::get_if<Common::ADSBContact>(&data.payload))
                track.icao24 = adsb->icao24;
        }
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
        RegisterSource(t, data.type);
        UpdateIdentity(t, data);
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
        RegisterSource(track, data.type);
        UpdateIdentity(track, data);
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