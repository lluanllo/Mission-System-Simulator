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
                LOG_MISSION_INFO(
                    "Track {} updated: lat={}, lon={}, altitude={}",
                    event.track.id,
                    event.track.position.latitude,
                    event.track.position.longitude,
                    event.track.position.altitude
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