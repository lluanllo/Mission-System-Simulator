#pragma once

#include "Log/Log.hpp"
#include "core/ModuleManager.hpp"
#include "core/events/EventBus.hpp"
#include "core/ApplicationContext.hpp"

namespace Mission_Management {

	class Application {
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		void Stop();

	private:
		Core::EventBus m_EventBus;
		Core::ApplicationContext m_Context;
		Core::ModuleManager m_ModuleManager;
		bool m_Running = false;
	};
}