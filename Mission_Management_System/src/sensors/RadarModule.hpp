#pragma once

#include "core/IModule.hpp"
#include "core/ApplicationContext.hpp"
#include <thread>
#include <atomic>

namespace Mission_Management {
namespace Sensors {

    class RadarModule : public Core::IModule
    {
    public:
        void OnInit(Core::ApplicationContext& context) override;
        void OnStart() override;
        void OnUpdate(double dt) override;
        void OnStop() override;
        void OnShutdown() override;

    private:
        Core::ApplicationContext* m_Context = nullptr;
        double m_Accumulator = 0.0;
    };

} }