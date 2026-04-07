#ifndef BACKTEST_H
#define BACKTEST_H

#include <functional>

#include "GameState.h"
#include "engine/Action.h"

class Backtest {
   public:
    using Strategy = std::function<Action(const GameState&)>;
    static void run(Strategy strategy, int rounds = 10000);

   private:
    static void autoPlayerTurn(GameState& state);
    static void autoDealerTurn(GameState& state);
    static void printResults(int wins, int loses, int pushes, int ronuds);
};

namespace Strategy {
Action monteCarlo(const GameState& state);
Action baseline(const GameState& state);
}  // namespace Strategy

#endif