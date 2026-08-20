#pragma once

#include <cstdint>
#include <unordered_map>

#include "common/tracking/Track.hpp"
#include "common/sensor/RadarContact.hpp"

namespace Mission_Management {
namespace Tracking {

    class TrackManager
    {
    public:
        Common::Track ProcessRadarContact(const Common::RadarContact& contact);

        const std::unordered_map<std::uint64_t, Common::Track>& GetTracks() const;

    private:
        std::uint64_t GenerateTrackId();

        std::unordered_map<std::uint64_t, Common::Track> m_Tracks;
        std::uint64_t m_NextTrackId = 1;
    };

} }