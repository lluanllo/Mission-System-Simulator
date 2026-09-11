#pragma once

#include "sensors/SensorModule.hpp"
#include "core/ApplicationContext.hpp"
#include "core/events/EventBus.hpp"
#include "Log/Log.hpp"
#include "common/events/SensorDataReceivedEvent.hpp"

#include <chrono>
#include <utility>

namespace Mission_Management {
namespace Sensors {

	class ADSBModule : public SensorModule
	{
	public:
		void OnInit(Core::ApplicationContext& context) override
		{
			m_Context = &context;
			LOG_SENSOR_INFO("ADS-B initialized");
		}

		void OnStart() override
		{
			LOG_SENSOR_INFO("ADS-B started");
		}

		void OnUpdate(double dt) override
		{
			m_Accumulator += dt;

			if (m_Accumulator < 0.7)
				return;

			m_Accumulator = 0.0;

			Common::ADSBContact contact{
				"3465812",
				"IBE1234",
				{ 40.416801, -3.703799, 5000.0 },
				{ 250.0, 90.0, 0.0 },
				std::chrono::steady_clock::now()
			};

			Common::SensorData data{
				Common::SensorType::ADSB,
				contact
			};

			LOG_SENSOR_INFO("ADS-B contact generated: ICAO24={}, callsign={}, lat={:.6f}, lon={:.6f}",
				contact.icao24,
				contact.callsign,
				contact.position.latitude,
				contact.position.longitude);

			if (m_Context)
			{
				Common::SensorDataReceivedEvent event;
				event.data = std::move(data);
				m_Context->eventBus.Publish(std::move(event));
			}
		}

		void OnStop() override
		{
			LOG_SENSOR_INFO("ADS-B stopped");
		}

		void OnShutdown() override
		{
			LOG_SENSOR_INFO("ADS-B shutdown");
		}

		Common::SensorType GetSensorType() const override
		{
			return Common::SensorType::ADSB;
		}

	private:
		Core::ApplicationContext* m_Context = nullptr;
		double m_Accumulator = 0.0;
	};

} }
