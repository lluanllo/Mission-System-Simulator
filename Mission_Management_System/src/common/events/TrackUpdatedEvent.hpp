#pragma once

#include "core/events/Event.hpp"
#include "common/tracking/Track.hpp"

namespace Mission_Management {
namespace Common {

    struct TrackUpdatedEvent
        : public Core::TypedEvent<TrackUpdatedEvent>
    {
        Track track;
    };

} }