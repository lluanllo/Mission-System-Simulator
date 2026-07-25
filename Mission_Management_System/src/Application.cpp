#include "Application.hpp"
#include "core/DummyModules.hpp"
#include <thread>
#include <chrono>

namespace Mission_Management {

	Application::Application() {
		Log::Init();
		LOG_CORE_INFO("Initializing Application...");

		// Register testing modules
		m_ModuleManager.AddModule(std::make_shared<DummySensorModule>());
		m_ModuleManager.AddModule(std::make_shared<DummyUIModule>());

		m_ModuleManager.Init();
	}

	Application::~Application() {
	}

	void Application::Run() {
		LOG_CORE_INFO("Starting Application...");
		m_ModuleManager.Start();

		m_Running = true;
		int simulatedFrames = 0;

		while (m_Running) {
			m_ModuleManager.Update(0.016); // Simulate ~60FPS delta time
			
			// Just to prevent infinite loop for testing
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			if (++simulatedFrames >= 3) {
				Stop();
			}
		}

		LOG_CORE_INFO("Stopping Application...");
		m_ModuleManager.Stop();
		m_ModuleManager.Shutdown();
	}

	void Application::Stop() {
		m_Running = false;
	}

}