#ifndef GAME_H
#define GAME_H

#include "GameState.h"

enum class Outcome { DealerWin, PlayerWin, Push };

class Game {
   public:
    static void dealInitialCards(GameState& state);
    static void playerTurn(GameState& state);
    static void playDealer(GameState& state);
    static Outcome determineOutcome(const GameState& state);
    static void playerHit(GameState& state);
    static void playRound(GameState& state);
};

#endif