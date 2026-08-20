#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "core/events/Event.hpp"

namespace Mission_Management {
namespace Core {

    class IEventHandler {
    public:
        virtual ~IEventHandler() = default;
        virtual void Execute(const Event& event) = 0;
    };

    template<typename T>
    class EventHandler : public IEventHandler {
    public:
        using HandlerFunc = std::function<void(const T&)>;

        explicit EventHandler(HandlerFunc handler) : m_Handler(handler) {}

        void Execute(const Event& event) override {
            if (event.GetType() == typeid(T)) {
                // static_cast safely casts down to T since typeid matches
                m_Handler(static_cast<const T&>(event));
            }
        }
    private:
        HandlerFunc m_Handler;
    };

    class EventBus
    {
    public:
        template<typename T>
        using Handler = std::function<void(const T&)>;

        template<typename T>
        void Subscribe(Handler<T> handler)
        {
            std::lock_guard<std::mutex> lock(m_HandlersMutex);
            m_Handlers[typeid(T)].push_back(std::make_unique<EventHandler<T>>(handler));
        }

        template<typename T>
        void Publish(const T& event)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push(std::make_unique<T>(event));
        }

        void Process()
        {
            std::queue<std::unique_ptr<Event>> queueCopy;
            {
                std::lock_guard<std::mutex> lock(m_QueueMutex);
                std::swap(queueCopy, m_EventQueue);
            }

            while (!queueCopy.empty()) {
                auto event = std::move(queueCopy.front());
                queueCopy.pop();

                std::vector<IEventHandler*> handlersToCall;
                {
                    std::lock_guard<std::mutex> lock(m_HandlersMutex);
                    auto it = m_Handlers.find(event->GetType());
                    if (it != m_Handlers.end()) {
                        for (auto& handler : it->second) {
                            handlersToCall.push_back(handler.get());
                        }
                    }
                }

                for (auto* handler : handlersToCall) {
                    handler->Execute(*event);
                }
            }
        }

        void Clear()
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            std::queue<std::unique_ptr<Event>> empty;
            std::swap(m_EventQueue, empty);
        }

    private:
        std::mutex m_QueueMutex;
        std::queue<std::unique_ptr<Event>> m_EventQueue;

        std::mutex m_HandlersMutex;
        std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandler>>> m_Handlers;
    };

} }