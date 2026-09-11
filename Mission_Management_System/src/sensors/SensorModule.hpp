#pragma once

#include "core/IModule.hpp"
#include "common/sensor/SensorType.hpp"

namespace Mission_Management {
namespace Sensors {

	class SensorModule : public Core::IModule
	{
	public:
		virtual ~SensorModule() = default;

		virtual Common::SensorType GetSensorType() const = 0;
	};

} }
