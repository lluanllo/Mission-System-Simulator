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
        m_Accumulator += dt;

        if (m_Accumulator < 0.5)
            return;

        m_Accumulator = 0.0;

        Common::RadarContact contact{
            { m_TargetLatitude, m_TargetLongitude, m_TargetAltitude }, // Position
            { 250.0, 90.0, 0.0 },                                      // Velocity (250 kt, rumbo 90°)
            12.5,                                                     // RCS
            std::chrono::steady_clock::now()                         // Timestamp
        };

        // Avance del objetivo entre barridos (magnitudes de prueba, no cinemática real aún)
        m_TargetLatitude += 0.0001;
        m_TargetLongitude += 0.0002;

        Common::SensorData data{
            Common::SensorType::Radar,
            contact
        };

        LOG_SENSOR_INFO("Radar contact generated: lat={}, lon={}, alt={}", 
            contact.position.latitude, 
            contact.position.longitude, 
            contact.position.altitude);

        if (m_Context) {
            Common::SensorDataReceivedEvent event;
            event.data = data;
            m_Context->eventBus.Publish(event);
        }
    }

    void RadarModule::OnStop() {
        LOG_SENSOR_INFO("Radar stopped");
    }

    void RadarModule::OnShutdown() {
        LOG_SENSOR_INFO("Radar shutdown");
    }

} }