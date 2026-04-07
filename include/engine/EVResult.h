#ifndef EVRESULT_H
#define EVRESULT_H

#include <limits>

#include "Action.h"

struct EVResult {
    double stand = std::numeric_limits<double>::lowest();
    double hit = std::numeric_limits<double>::lowest();
    double doubleDown = std::numeric_limits<double>::lowest();
    double split = std::numeric_limits<double>::lowest();
    double surrender = std::numeric_limits<double>::lowest();

    double ev(Action action) const {
        switch (action) {
            case Action::Stand:
                return stand;
            case Action::Hit:
                return hit;
            case Action::Double:
                return doubleDown;
            case Action::Split:
                return split;
            case Action::Surrender:
                return surrender;
        }
        return std::numeric_limits<double>::lowest();
    }

    Action bestAction() const {
        Action best = Action::Stand;
        double bestEV = stand;
        if (hit > bestEV) {
            bestEV = hit;
            best = Action::Hit;
        }
        if (doubleDown > bestEV) {
            bestEV = doubleDown;
            best = Action::Double;
        }
        if (split > bestEV) {
            bestEV = split;
            best = Action::Split;
        }
        if (surrender > bestEV) {
            bestEV = surrender;
            best = Action::Surrender;
        }
        return best;
    }

    double bestEV() const {
        return ev(bestAction());
    }
};

#endif