#include "Application.hpp"
#include <thread>
#include <chrono>

namespace Mission_Management {

	struct TestEvent : Core::TypedEvent<TestEvent> {
		int value;
		TestEvent(int v) : value(v) {}
	};

	Application::Application()
		: m_Context(m_EventBus),
		  m_ModuleManager(m_Context)
	{
		Log::Init();
		LOG_CORE_INFO("Initializing Application...");

		// Register testing modules
		// m_ModuleManager.AddModule(Core::CreateRef<Sensors::RadarModule>());
		// m_ModuleManager.AddModule(Core::CreateRef<Fusion::FusionModule>());

		m_EventBus.Subscribe<TestEvent>([](const TestEvent& event) {
			LOG_CORE_INFO("Subscriber A received TestEvent: {}", event.value);
		});

		m_EventBus.Subscribe<TestEvent>([](const TestEvent& event) {
			LOG_CORE_INFO("Subscriber B received TestEvent: {}", event.value);
		});

		LOG_CORE_INFO("Publishing TestEvent(42)...");
		m_EventBus.Publish(TestEvent{ 42 });

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
			m_Context.eventBus.Process();

			// Just to prevent infinite loop for testing
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			if (++simulatedFrames >= 100) {
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