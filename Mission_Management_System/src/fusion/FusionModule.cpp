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

    void FusionModule::OnSensorDataReceived(const Common::SensorDataReceivedEvent& event) {
        LOG_CORE_INFO("Fusion: Sensor data received");

        // Fusion es agnóstico al sensor: lo que llegue va a correlator -> manager
        size_t oldSize = m_TrackManager.GetTracks().size();

        Common::Track track = m_TrackManager.Process(event.data, m_Correlator);

        if (oldSize < m_TrackManager.GetTracks().size()) {
            LOG_FUSION_INFO("Track {} created", track.id);
        }
        else {
            LOG_FUSION_INFO("Track {} updated", track.id);
        }

        Common::TrackUpdatedEvent trackEvent;
        trackEvent.track = track;
        m_Context->eventBus.Publish(trackEvent);
    }

} }