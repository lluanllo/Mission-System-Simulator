#include "Log.hpp"

namespace Mission_Management {

    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init() {
        spdlog::set_pattern("%^%v%$");
        
        s_Logger = spdlog::stdout_color_mt("System");
        s_Logger->set_level(spdlog::level::trace);
    }
}