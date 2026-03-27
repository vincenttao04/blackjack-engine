#include "Backtest.h"

#include <iostream>

#include "Game.h"
#include "GameState.h"
#include "MonteCarlo.h"

using namespace std;

void Backtest::autoPlayerTurn(GameState& state) {
    while (true) {
        if (state.player.isBust()) {
            break;
        }

        auto [standEV, hitEV] = MonteCarlo::simulate(state);

        if (standEV >= hitEV) {
            state.player.addCard(state.shoe.draw());
        } else {
            return;
        }
    }
};

void Backtest::run() {
    const int numberOfTests = 100;
    int winCount = 0;
    int pushCount = 0;
    int loseCount = 0;

    GameState state;

    state.shoe.initialize();

    for (int i = 0; i < numberOfTests; i++) {
        if (state.shoe.needsReshuffle()) {
            state.shoe.initialize();
            cout << "Reshuffling..." << endl;
        };

        state.player.clear();
        state.dealer.clear();

        Game::dealInitialCards(state);
        autoPlayerTurn(state);

        Game::playDealer(state);

        Outcome result = Game::determineOutcome(state);

        if (result == Outcome::PlayerWin) {
            winCount++;
        };

        if (result == Outcome::DealerWin) {
            loseCount++;
        };

        if (result == Outcome::Push) {
            pushCount++;
        };
    }
    return;
};
