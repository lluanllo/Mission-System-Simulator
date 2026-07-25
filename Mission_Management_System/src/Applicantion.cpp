#include "Core/Mission_management.hpp"

Mission_Management::Application::Application() {
	Mission_Management::Log::Init();
	MM_LOG_INFO("Logger Initialized");
	MM_LOG_DEBUG("Mission Management Application Initialized");
}

Mission_Management::Application::~Application() {
	// Cleanup code here
}

void Mission_Management::Application::Run() {
	while (true) {

	}
}