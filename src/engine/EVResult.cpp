#include "engine/EVResult.h"

double EVResult::ev(Action action) const {
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

Action EVResult::bestAction() const {
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

double EVResult::bestEV() const {
    return ev(bestAction());
}