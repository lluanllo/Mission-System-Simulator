#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Mission_Management {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

#define MM_LOG_TRACE(...)    ::Mission_Management::Log::GetLogger()->trace(__VA_ARGS__)
#define MM_LOG_INFO(...)     ::Mission_Management::Log::GetLogger()->info(__VA_ARGS__)
#define MM_LOG_WARN(...)     ::Mission_Management::Log::GetLogger()->warn(__VA_ARGS__)
#define MM_LOG_ERROR(...)    ::Mission_Management::Log::GetLogger()->error(__VA_ARGS__)
#define MM_LOG_CRITICAL(...) ::Mission_Management::Log::GetLogger()->critical(__VA_ARGS__)
#define MM_LOG_FATAL(...)    ::Mission_Management::Log::GetLogger()->critical(__VA_ARGS__)
#define MM_LOG_DEBUG(...)    ::Mission_Management::Log::GetLogger()->debug(__VA_ARGS__)

}