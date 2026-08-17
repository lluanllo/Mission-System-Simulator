#pragma once

#include "Log/Log.hpp"
#include "core/ModuleManager.hpp"

namespace Mission_Management {

	class Application {
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		void Stop();

	private:
		ModuleManager m_ModuleManager;
		bool m_Running = false;
	};
}