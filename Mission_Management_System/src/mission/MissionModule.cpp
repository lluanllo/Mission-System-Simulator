#include "MissionModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/TrackUpdatedEvent.hpp"

namespace Mission_Management {
namespace Mission {

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
                    "Track {} [{}] updated | Position: {:.6f}, {:.6f} | Predicted: {:.6f}, {:.6f} | Heading: {:.1f} deg | Speed: {:.1f} kt | Trail points: {}",
                    event.track.id,
                    stateName,
                    event.track.position.latitude,
                    event.track.position.longitude,
                    event.track.predictedPosition.latitude,
                    event.track.predictedPosition.longitude,
                    event.track.velocity.heading,
                    event.track.velocity.speed,
                    event.track.history.size()
                );
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