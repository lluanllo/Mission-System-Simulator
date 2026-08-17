#include "RadarModule.hpp"
#include "Log/Log.hpp"
#include "core/events/EventBus.hpp"
#include "common/events/SensorDataReceivedEvent.hpp"

namespace Mission_Management {
namespace Sensors {

    void RadarModule::OnInit(Core::ApplicationContext& context) {
        m_Context = &context;
        LOG_SENSOR_INFO("Radar initialized");
    }

    void RadarModule::OnStart() {
        LOG_SENSOR_INFO("Radar started");
    }

    void RadarModule::OnUpdate(double dt) {
        m_Timer += dt;
        if (m_Timer >= 0.5) { // exactly 500 ms simulation
            m_Timer = 0.0;

            Common::RadarContact radarContact{
                { 40.4168, -3.7038, 5000.0 }, // Position
                { 250.0, 90.0, 0.0 },         // Velocity
                12.5,                         // RCS
                std::chrono::steady_clock::now() // Timestamp
            };

            Common::SensorData data{
                Common::SensorType::Radar,
                radarContact
            };

            LOG_SENSOR_INFO("Radar contact generated");

            if (m_Context) {
                Common::SensorDataReceivedEvent event;
                event.data = data;
                m_Context->eventBus.Publish(event);
            }
        }
    }

    void RadarModule::OnStop() {
        LOG_SENSOR_INFO("Radar stopped");
    }

    void RadarModule::OnShutdown() {
        LOG_SENSOR_INFO("Radar shutdown");
    }

} }