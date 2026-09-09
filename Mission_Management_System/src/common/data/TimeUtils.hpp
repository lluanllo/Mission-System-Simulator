#pragma once

#include "common/data/Timestamp.hpp"

namespace Mission_Management {
    namespace Common {

        // Devuelve la diferencia en segundos entre dos timestamps
        double SecondsBetween(const Timestamp& a, const Timestamp& b);
    }
}