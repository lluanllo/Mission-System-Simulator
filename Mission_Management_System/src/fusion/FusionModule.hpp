#pragma once

#include "core/IModule.hpp"
#include "core/ApplicationContext.hpp"
#include "common/events/SensorDataReceivedEvent.hpp"

namespace Mission_Management {
namespace Fusion {

    class FusionModule : public Core::IModule
    {
    public:
        void OnInit(Core::ApplicationContext& context) override;
        void OnStart() override;
        void OnUpdate(double dt) override;
        void OnStop() override;
        void OnShutdown() override;

    private:
        void OnSensorDataReceived(const Common::SensorDataReceivedEvent& event);

        Core::ApplicationContext* m_Context = nullptr;
    };

} }