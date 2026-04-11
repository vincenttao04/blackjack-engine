#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "GameState.h"
#include "engine/EVResult.h"

class MonteCarlo {
   public:
    static EVResult simulate(const GameState& state);

   private:
    static GameState prepareSimState(const GameState& state);
    static double simulateStand(GameState& state);
    static double simulateHit(GameState& state);
    static double simulateDecision(GameState& state);
    static double simulateDouble(GameState& state);
};

#endif
