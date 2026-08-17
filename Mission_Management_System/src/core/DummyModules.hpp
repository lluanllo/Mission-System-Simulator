#pragma once

#include "core/IModule.hpp"
#include "Log/Log.hpp"
#include "common/sensor/SensorData.hpp"
#include "common/sensor/RadarContact.hpp"

namespace Mission_Management {

    class DummySensorModule : public IModule {
    public:
        void OnInit() override { LOG_SENSOR_INFO("OnInit called."); }
        void OnStart() override { LOG_SENSOR_INFO("OnStart called."); }
        void OnUpdate(double dt) override { 
            using namespace Mission_Management::Common;
            
            RadarContact radarContact{
                { 40.4168, -3.7038, 5000.0 }, // Position
                { 250.0, 90.0, 0.0 },         // Velocity
                12.5,                         // RCS
                std::chrono::steady_clock::now() // Timestamp
            };
            
            SensorData data{
                SensorType::Radar,
                radarContact
            };
            
            const auto& radar = data.payload.radar;
            
            LOG_SENSOR_INFO("Radar contact received: lat={}, lon={}, alt={}", 
                            radar.position.latitude,
                            radar.position.longitude,
                            radar.position.altitude);
        }
        void OnStop() override { LOG_SENSOR_INFO("OnStop called."); }
        void OnShutdown() override { LOG_SENSOR_INFO("OnShutdown called."); }
    };

    class DummyUIModule : public IModule {
    public:
        void OnInit() override { LOG_UI_INFO("OnInit called."); }
        void OnStart() override { LOG_UI_INFO("OnStart called."); }
        void OnUpdate(double dt) override { LOG_UI_INFO("OnUpdate called with dt = {}", dt); }
        void OnStop() override { LOG_UI_INFO("OnStop called."); }
        void OnShutdown() override { LOG_UI_INFO("OnShutdown called."); }
    };

}
