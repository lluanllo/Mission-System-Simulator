#include "FusionModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/TrackUpdatedEvent.hpp"
#include "common/events/TrackPredictionUpdatedEvent.hpp"
#include "common/sensor/ADSBContact.hpp"

#include <string_view>
#include <variant>

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
        if (!m_Context)
            return;

        const auto predictedTracks = m_TrackManager.PredictWithoutMeasurement(dt);
        for (const auto& track : predictedTracks)
        {
            Common::TrackPredictionUpdatedEvent trackEvent;
            trackEvent.track = track;
            m_Context->eventBus.Publish(trackEvent);
        }
    }

    void FusionModule::OnStop() {
        LOG_CORE_INFO("Fusion stopped");
    }

    void FusionModule::OnShutdown() {
        LOG_CORE_INFO("Fusion shutdown");
    }

    namespace {
        constexpr std::string_view SensorName(Common::SensorType type)
        {
            switch (type)
            {
            case Common::SensorType::Radar: return "Radar";
            case Common::SensorType::ADSB:  return "ADS-B";
            case Common::SensorType::AIS:   return "AIS";
            case Common::SensorType::IFF:   return "IFF";
            case Common::SensorType::EOIR:  return "EO/IR";
            default:                        return "Unknown";
            }
        }
    }

    void FusionModule::OnSensorDataReceived(const Common::SensorDataReceivedEvent& event) {
        const auto correlation = m_Correlator.FindMatch(event.data, m_TrackManager.GetTracks());
        Common::Track track = m_TrackManager.Process(event.data, correlation);

        if (!correlation.matched) {
            LOG_FUSION_INFO("{} contact created Track {}", SensorName(event.data.type), track.id);
        }
        else {
            LOG_FUSION_INFO("{} correlated with Track {} | score={:.2f}", SensorName(event.data.type), track.id, correlation.score);
        }

        if (const auto* adsb = std::get_if<Common::ADSBContact>(&event.data.payload))
        {
            LOG_FUSION_INFO("Track {} identification updated: {} / {}", track.id, adsb->callsign, adsb->icao24);
        }

        Common::TrackUpdatedEvent trackEvent;
        trackEvent.track = track;
        m_Context->eventBus.Publish(trackEvent);
    }

} }