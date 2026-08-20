#include "ModuleManager.hpp"
#include "ApplicationContext.hpp"

namespace Mission_Management {
namespace Core {

    ModuleManager::ModuleManager(ApplicationContext& context)
        : m_Context(context) {
    }

    void ModuleManager::AddModule(Ref<IModule> module) {
        m_Modules.push_back(module);
    }

    void ModuleManager::Init() {
        for (auto& module : m_Modules) {
            module->OnInit(m_Context);
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
} }
