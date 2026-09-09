#pragma once

#include "IModule.hpp"
#include "core.hpp"
#include <vector>

namespace Mission_Management {
namespace Core {
    class ApplicationContext;

    class ModuleManager {
    public:
        explicit ModuleManager(ApplicationContext& context);

        void AddModule(Ref<IModule> module);

        void Init();
        void Start();
        void Update(double dt);
        void Stop();
        void Shutdown();

    private:
        ApplicationContext& m_Context;
        std::vector<Ref<IModule>> m_Modules;
    };
}
}
