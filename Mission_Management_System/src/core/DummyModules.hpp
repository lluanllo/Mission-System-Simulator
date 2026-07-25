#pragma once

#include "core/IModule.hpp"
#include "Log/Log.hpp"

namespace Mission_Management {

    class DummySensorModule : public IModule {
    public:
        void OnInit() override { LOG_SENSOR_INFO("OnInit called."); }
        void OnStart() override { LOG_SENSOR_INFO("OnStart called."); }
        void OnUpdate(double dt) override { LOG_SENSOR_INFO("OnUpdate called with dt = {}", dt); }
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
