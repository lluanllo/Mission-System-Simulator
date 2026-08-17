#pragma once

namespace Mission_Management {
namespace Core {
    class EventBus;

    class ApplicationContext
    {
    public:
        explicit ApplicationContext(EventBus& bus)
            : eventBus(bus)
        {
        }

        EventBus& eventBus;
    };
} }