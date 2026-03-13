#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "GameState.h"

class MonteCarlo {
   public:
    static std::pair<double, double> simulate(const GameState& state);
    static double simulateStandEV(const GameState& simState, int simulations);
    static double simulateHitEV(const GameState& simState, int simulations);
};

#endif
