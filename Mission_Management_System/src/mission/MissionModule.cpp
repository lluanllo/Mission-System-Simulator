#include "MissionModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/TrackUpdatedEvent.hpp"

#include <string>
#include <vector>

namespace Mission_Management {
namespace Mission {

    namespace {
        const char* SensorName(Common::SensorType sensorType)
        {
            switch (sensorType)
            {
            case Common::SensorType::Radar: return "Radar";
            case Common::SensorType::ADSB:  return "ADS-B";
            case Common::SensorType::AIS:   return "AIS";
            case Common::SensorType::IFF:   return "IFF";
            case Common::SensorType::EOIR:  return "EO/IR";
            default:                        return "Unknown";
            }
        }

        std::string SourcesToString(const std::vector<Common::SensorType>& sources)
        {
            std::string result;
            for (std::size_t i = 0; i < sources.size(); ++i)
            {
                if (i > 0)
                    result += ", ";
                result += SensorName(sources[i]);
            }
            return result;
        }
    }

    void MissionModule::OnInit(Core::ApplicationContext& context) {
        m_Context = &context;
        LOG_MISSION_INFO("Mission initialized");

        m_Context->eventBus.Subscribe<Common::TrackUpdatedEvent>(
            [](const Common::TrackUpdatedEvent& event) {
                Common::TrackState state = event.track.trackState;
                const char* stateName =
                    (state == Common::TrackState::Tentative) ? "TENTATIVE" :
                    (state == Common::TrackState::Confirmed) ? "CONFIRMED" :
                    (state == Common::TrackState::Lost) ? "LOST" : "DROPPED";

                LOG_MISSION_INFO(
                    "Track {} [{}] updated | Position: {:.6f}, {:.6f} | Predicted: {:.6f}, {:.6f} | Heading: {:.1f} deg | Speed: {:.1f} kt | Trail points: {} | Sources: {}",
                    event.track.id,
                    stateName,
                    event.track.position.latitude,
                    event.track.position.longitude,
                    event.track.predictedPosition.latitude,
                    event.track.predictedPosition.longitude,
                    event.track.velocity.heading,
                    event.track.velocity.speed,
                    event.track.history.size(),
                    SourcesToString(event.track.sources)
                );

                if (event.track.icao24.has_value())
                {
                    LOG_MISSION_INFO("Track {} ICAO24: {}", event.track.id, event.track.icao24.value());
                }
            }
        );
    }

    void MissionModule::OnStart() {
        LOG_MISSION_INFO("Mission started");
    }

    void MissionModule::OnUpdate(double dt) {
        // Nothing here yet
    }

    void MissionModule::OnStop() {
        // Nothing here yet
    }

    void MissionModule::OnShutdown() {
        // Nothing here yet
    }

} }