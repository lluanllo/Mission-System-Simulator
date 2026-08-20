#include "EventBus.hpp"

namespace Mission_Management {
namespace Core {

    void EventBus::Process() {
        std::queue<QueuedEvent> pending;
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            std::swap(pending, m_EventQueue);
        }

        while (!pending.empty()) {
            auto queuedResult = std::move(pending.front());
            pending.pop();

            const auto& eventPtr = queuedResult.event;
            std::vector<Subscription> subscriptionsToCall;

            {
                std::lock_guard<std::mutex> lock(m_SubscriptionMutex);
                auto it = m_Subscribers.find(eventPtr->GetType());
                if (it != m_Subscribers.end()) {
                    subscriptionsToCall = it->second;
                }
            }

            for (auto& subscription : subscriptionsToCall) {
                subscription(*eventPtr);
            }
        }
    }

    void EventBus::Clear() {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        std::queue<QueuedEvent> empty;
        std::swap(m_EventQueue, empty);
    }

}
}