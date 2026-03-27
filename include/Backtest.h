#ifndef BACKTEST_H
#define BACKTEST_H

#include "GameState.h"

class Backtest {
   public:
    static void run();

   private:
    static void autoPlayerTurn(GameState& state);
};

#endif