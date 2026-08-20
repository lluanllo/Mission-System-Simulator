#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "core/core.hpp"

namespace Mission_Management {

	class Log {
	public:
		static void Init();

		inline static Core::Ref<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static Core::Ref<spdlog::logger> s_Logger;
	};

#define LOG_CORE_INFO(fmt, ...)    ::Mission_Management::Log::GetLogger()->info("[Core] " fmt, ##__VA_ARGS__)
#define LOG_SENSOR_INFO(fmt, ...)  ::Mission_Management::Log::GetLogger()->info("[Sensor] " fmt, ##__VA_ARGS__)
#define LOG_FUSION_INFO(fmt, ...)  ::Mission_Management::Log::GetLogger()->info("[Fusion] " fmt, ##__VA_ARGS__)
#define LOG_MISSION_INFO(fmt, ...) ::Mission_Management::Log::GetLogger()->info("[Mission] " fmt, ##__VA_ARGS__)
#define LOG_UI_INFO(fmt, ...)      ::Mission_Management::Log::GetLogger()->info("[UI] " fmt, ##__VA_ARGS__)

}