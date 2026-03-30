#ifndef BACKTEST_H
#define BACKTEST_H

#include "GameState.h"

class Backtest {
   public:
    static void run();

   private:
    static void autoPlayerTurn(GameState& state);
    static void autoDealerTurn(GameState& state);
    static void printResults(int wins, int loses, int pushes);
};

#endif