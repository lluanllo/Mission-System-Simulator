#pragma once

namespace Mission_Management {
    class IModule {
    public:
        virtual ~IModule() = default;

        virtual void OnInit() = 0;
        virtual void OnStart() = 0;
        virtual void OnUpdate(double dt) = 0;
        virtual void OnStop() = 0;
        virtual void OnShutdown() = 0;
    };
}
