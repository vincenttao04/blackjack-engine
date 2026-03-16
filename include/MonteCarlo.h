#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <utility>

#include "GameState.h"

class MonteCarlo {
   public:
    static std::pair<double, double> simulate(const GameState& state);

   private:
    static double simulateStand(GameState& state);
    static double simulateHit(GameState& state);
    static double simulateDecision(GameState& state);
};

#endif
