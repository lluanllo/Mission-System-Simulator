#pragma once

#include "IModule.hpp"
#include <vector>
#include <memory>

namespace Mission_Management {
    class ModuleManager {
    public:
        void AddModule(std::shared_ptr<IModule> module);

        void Init();
        void Start();
        void Update(double dt);
        void Stop();
        void Shutdown();

    private:
        std::vector<std::shared_ptr<IModule>> m_Modules;
    };
}
