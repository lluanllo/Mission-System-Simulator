#pragma once

#include "core/IModule.hpp"
#include "core/ApplicationContext.hpp"
#include "common/events/SensorDataReceivedEvent.hpp"
#include "tracking/TrackManager.hpp"
#include "tracking/TrackCorrelator.hpp"

namespace Mission_Management {
namespace Fusion {

    class FusionModule : public Core::IModule {
        public:
            void OnInit(Core::ApplicationContext& context) override;
            void OnStart() override;
            void OnUpdate(double dt) override;
            void OnStop() override;
            void OnShutdown() override;

        private:
            void OnSensorDataReceived(const Common::SensorDataReceivedEvent& event);

            Core::ApplicationContext* m_Context = nullptr;
            Tracking::TrackManager m_TrackManager;
            Tracking::TrackCorrelator m_Correlator{ 0.7 }; // umbral de score
    };

} }