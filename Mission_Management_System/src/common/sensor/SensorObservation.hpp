#pragma once

#include "common/sensor/SensorData.hpp"
#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"

namespace Mission_Management {
namespace Common {

    // Extracción unificada de la posición observada,
    // sin dispersar la lógica de "qué campo del payload" por todo el pipeline.
    inline const Position& GetPosition(const SensorData& data)
    {
        switch (data.type)
        {
            case SensorType::Radar: return data.payload.radar.position;
            case SensorType::ADSB:  return data.payload.adsb.position;
            case SensorType::AIS:   return data.payload.ais.position;
            // IFF / EOIR: añadir aquí cuando los implementes
            default:
                throw std::runtime_error("SensorObservation: unknown SensorType");
        }
    }

    // Velocidad (knots / heading / climbRate). AIS no lleva Velocity en su struct actual,
    // así que devolvemos {speed, course, 0} a partir de sus campos propios.
    inline Velocity GetVelocity(const SensorData& data)
    {
        switch (data.type)
        {
            case SensorType::Radar: return data.payload.radar.velocity;
            case SensorType::ADSB:  return data.payload.adsb.velocity;
            case SensorType::AIS:   return Velocity{ data.payload.ais.speed, data.payload.ais.course, 0.0 };
            default:
                throw std::runtime_error("SensorObservation: unknown SensorType");
        }
    }

} }