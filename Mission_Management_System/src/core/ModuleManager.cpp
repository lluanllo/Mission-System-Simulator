#include "ModuleManager.hpp"

namespace Mission_Management {
    void ModuleManager::AddModule(std::shared_ptr<IModule> module) {
        m_Modules.push_back(module);
    }

    void ModuleManager::Init() {
        for (auto& module : m_Modules) {
            module->OnInit();
        }
    }

    void ModuleManager::Start() {
        for (auto& module : m_Modules) {
            module->OnStart();
        }
    }

    void ModuleManager::Update(double dt) {
        for (auto& module : m_Modules) {
            module->OnUpdate(dt);
        }
    }

    void ModuleManager::Stop() {
        for (auto& module : m_Modules) {
            module->OnStop();
        }
    }

    void ModuleManager::Shutdown() {
        for (auto& module : m_Modules) {
            module->OnShutdown();
        }
    }
}
