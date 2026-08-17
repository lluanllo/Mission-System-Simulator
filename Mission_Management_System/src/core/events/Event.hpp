#pragma once

#include <typeindex>

namespace Mission_Management {
namespace Core {

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual std::type_index GetType() const = 0;
    };

    template<typename T>
    class TypedEvent : public Event
    {
    public:
        std::type_index GetType() const override
        {
            return typeid(T);
        }
    };

} }