#ifndef EVRESULT_H
#define EVRESULT_H

#include <limits>

#include "engine/Action.h"

struct EVResult {
    double stand = std::numeric_limits<double>::lowest();
    double hit = std::numeric_limits<double>::lowest();
    double doubleDown = std::numeric_limits<double>::lowest();
    double split = std::numeric_limits<double>::lowest();
    double surrender = std::numeric_limits<double>::lowest();

    double ev(Action action) const;
    Action bestAction() const;
    double bestEV() const;
};

#endif