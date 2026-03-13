#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "GameState.h"

class MonteCarlo {
   public:
    static double simulateStandEV(const GameState& state, int simulations);

    static double simulateHitEV(const GameState& state, int simulations);
};

#endif
