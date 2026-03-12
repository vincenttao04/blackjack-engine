#include <iostream>

#include "Game.h"
#include "Hand.h"
#include "Rules.h"
#include "Shoe.h"

using namespace std;

int main() {
    GameState state;

    // Configure game rules
    state.rules.numberOfDecks = 6;
    state.rules.dealerHitsSoft17 = false;  // unused
    state.rules.blackjackPayout = 1.5;     // unused

    state.shoe.initialize(state.rules.numberOfDecks);
    state.shoe.shuffle();

    Game::startRound(state);

    return 0;
}