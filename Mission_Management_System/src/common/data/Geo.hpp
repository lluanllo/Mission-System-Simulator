#pragma once

#include <cmath>
#include "common/data/Position.hpp"

namespace Mission_Management {
namespace Common {

    // Constante portable (evita dependencia de M_PI, que no está garantizada en <cmath> de todas las plataformas)
    constexpr double Pi = 3.14159265358979323846;

    // APROXIMACIÓN GEOGRÁFICA HAVERSINE (km)
    // ⚠ Esto es una aproximación de simulación, NO un modelo de navegación aeronáutica certificado.
    double ApproximateDistanceKm(const Position& a, const Position& b)
    {
        constexpr double EarthRadiusKm = 6371.0;
        constexpr double Deg2Rad = Pi / 180.0;

        const double lat1 = a.latitude * Deg2Rad;
        const double lat2 = b.latitude * Deg2Rad;
        const double dLat = (b.latitude - a.latitude) * Deg2Rad;
        const double dLon = (b.longitude - a.longitude) * Deg2Rad;

        const double h =
            std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
            std::cos(lat1) * std::cos(lat2) *
            std::sin(dLon / 2.0) * std::sin(dLon / 2.0);

        return 2.0 * EarthRadiusKm * std::asin(std::sqrt(h));
    }

} }