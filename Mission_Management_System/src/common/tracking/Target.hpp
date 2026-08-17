#pragma once
#include <cstdint>
#include "common/tracking/Track.hpp"

namespace Mission_Management {
namespace Common {
    struct Target
    {
        std::uint64_t targetId;
        Track primaryTrack;
    };
} }