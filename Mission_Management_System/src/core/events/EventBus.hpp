#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "core/events/Event.hpp"
#include "core/core.hpp"

namespace Mission_Management {
namespace Core {

    template<typename EventType>
    class EventWrapper : public Event {
    public:
        explicit EventWrapper(EventType e)
            : event(std::move(e))
        {
        }

        EventType event;

        std::type_index GetType() const override {
            return typeid(EventType);
        }
    };

    class EventBus {
    public:
        template<typename EventType>
        using EventHandler = std::function<void(const EventType&)>;

        template<typename EventType>
        void Subscribe(EventHandler<EventType> handler) {
            std::lock_guard<std::mutex> lock(m_SubscriptionMutex);
            m_Subscribers[typeid(EventType)].push_back([handler](const Event& baseEvent) {
                const auto& wrapper = static_cast<const EventWrapper<EventType>&>(baseEvent);
                handler(wrapper.event);
            });
        }

        template<typename EventType>
        void Publish(EventType event) {
            auto queuedEvent = CreateScope<EventWrapper<EventType>>(std::move(event));

            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ std::move(queuedEvent) });
        }

        void Process();

        void Clear();

    private:
        struct QueuedEvent {
            Scope<Event> event;
        };

        using Subscription = std::function<void(const Event&)>;

        std::unordered_map<std::type_index, std::vector<Subscription>> m_Subscribers;
        std::queue<QueuedEvent> m_EventQueue;

        std::mutex m_QueueMutex;
        std::mutex m_SubscriptionMutex;
    };

}
}