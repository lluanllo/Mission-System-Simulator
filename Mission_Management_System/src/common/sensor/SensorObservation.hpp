#pragma once

#include <stdexcept>
#include <variant>

#include "common/sensor/SensorData.hpp"
#include "common/data/Position.hpp"
#include "common/data/Velocity.hpp"

namespace Mission_Management {
namespace Common {

    // Extracción unificada de la posición observada,
    // sin dispersar la lógica de "qué campo del payload" por todo el pipeline.
    inline const Position& GetPosition(const SensorData& data)
    {
        if (const auto* radar = std::get_if<RadarContact>(&data.payload))
            return radar->position;
        if (const auto* adsb = std::get_if<ADSBContact>(&data.payload))
            return adsb->position;
        if (const auto* ais = std::get_if<AISContact>(&data.payload))
            return ais->position;

        throw std::runtime_error("SensorObservation: unknown SensorPayload");
    }

    // Velocidad (knots / heading / climbRate). AIS no lleva Velocity en su struct actual,
    // así que devolvemos {speed, course, 0} a partir de sus campos propios.
    inline Velocity GetVelocity(const SensorData& data)
    {
        if (const auto* radar = std::get_if<RadarContact>(&data.payload))
            return radar->velocity;
        if (const auto* adsb = std::get_if<ADSBContact>(&data.payload))
            return adsb->velocity;
        if (const auto* ais = std::get_if<AISContact>(&data.payload))
            return Velocity{ ais->speed, ais->course, 0.0 };

        throw std::runtime_error("SensorObservation: unknown SensorPayload");
    }

} }