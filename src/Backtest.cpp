#include "Backtest.h"

#include <iostream>

#include "Game.h"

using namespace std;

void Backtest::run() {
    int numberOfTests = 100;
    int winCount = 0;
    int pushCount = 0;
    int loseCount = 0;

    GameState state;

    state.shoe.initialize();

    if (state.shoe.needsReshuffle()) {
        state.shoe.initialize();
        cout << "Reshuffling..." << endl;
    };

    Game::playRound(state);

    return;
};