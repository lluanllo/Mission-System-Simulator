#include "FusionModule.hpp"
#include "FusionModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/TrackUpdatedEvent.hpp"
#include "common/sensor/RadarContact.hpp"

namespace Mission_Management {
namespace Fusion {

    void FusionModule::OnInit(Core::ApplicationContext& context) {
        m_Context = &context;
        LOG_CORE_INFO("Fusion initialized");

        m_Context->eventBus.Subscribe<Common::SensorDataReceivedEvent>(
            [this](const Common::SensorDataReceivedEvent& event) {
                this->OnSensorDataReceived(event);
            }
        );
    }

    void FusionModule::OnStart() {
        LOG_CORE_INFO("Fusion started");
    }

    void FusionModule::OnUpdate(double dt) {
        // Nothing here yet
    }

    void FusionModule::OnStop() {
        LOG_CORE_INFO("Fusion stopped");
    }

    void FusionModule::OnShutdown() {
        LOG_CORE_INFO("Fusion shutdown");
    }

    void FusionModule::OnSensorDataReceived(const Common::SensorDataReceivedEvent& event) {
        LOG_CORE_INFO("Fusion: Sensor data received");

        std::uint64_t trackId = 1;
        bool created = false;

        if (m_Tracks.find(trackId) == m_Tracks.end()) {
            Common::Track newTrack;
            newTrack.id = trackId;
            newTrack.identification = Common::Identification::Unknown;
            newTrack.threatLevel = Common::ThreatLevel::Unknown;
            m_Tracks[trackId] = newTrack;
            created = true;
        }

        auto& track = m_Tracks[trackId];

        if (event.data.type == Common::SensorType::Radar) {
            const auto& radarInfo = event.data.payload.radar;
            track.position = radarInfo.position;
            track.velocity = radarInfo.velocity;
            track.lastSensor = Common::SensorType::Radar;
            track.lastUpdate = radarInfo.timestamp;

            if (created) {
                LOG_CORE_INFO("Fusion: Track {} created", trackId);
            } else {
                LOG_CORE_INFO("Fusion: Track {} updated", trackId);
            }

            if (m_Context) {
                Common::TrackUpdatedEvent outEvent;
                outEvent.track = track;
                m_Context->eventBus.Publish(outEvent);
            }
        }
    }

} }