#include "FusionModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/TrackUpdatedEvent.hpp"

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

} }