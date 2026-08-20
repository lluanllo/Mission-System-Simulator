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
        m_Running = true;
        m_WorkerThread = std::thread(&RadarModule::RunSimulation, this);
    }

    void RadarModule::OnUpdate(double dt) {
        // Nothing here, handled by thread
    }

    void RadarModule::RunSimulation() {
        while (m_Running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if (!m_Running) break;

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
        m_Running = false;
        if (m_WorkerThread.joinable()) {
            m_WorkerThread.join();
        }
    }

    void RadarModule::OnShutdown() {
        LOG_SENSOR_INFO("Radar shutdown");
    }

} }