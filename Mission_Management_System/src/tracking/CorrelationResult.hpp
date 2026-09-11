#pragma once

#include <cstdint>

namespace Mission_Management {
namespace Tracking {

	struct CorrelationResult
	{
		bool matched = false;
		std::uint64_t trackId = 0;
		double score = 0.0;
	};

} }
