#include "Baseline.h"

#include <iostream>

#include "Game.h"
#include "MonteCarlo.h"

using namespace std;

const int numberOfTests = 10000;

void Baseline::autoPlayerTurn(GameState& state) {
    while (state.player.value() < 17 ||
           (Rules::dealerHitsSoft17 && state.player.value() == 17 &&
            state.player.isSoft())) {
        state.player.addCard(state.shoe.draw());
    }
};

void Baseline::autoDealerTurn(GameState& state) {
    while (state.dealer.value() < 17 ||
           (Rules::dealerHitsSoft17 && state.dealer.value() == 17 &&
            state.dealer.isSoft())) {
        state.dealer.addCard(state.shoe.draw());
    }
};

void Baseline::run() {
    int wins = 0;
    int loses = 0;
    int pushes = 0;

    GameState state;

    state.shoe.initialize();

    for (int i = 0; i < numberOfTests; i++) {
        if (state.shoe.needsReshuffle()) {
            state.shoe.activeSize == 0;
        };

        Game::dealInitialCards(state);
        autoPlayerTurn(state);

        if (!state.player.isBust()) {
            autoDealerTurn(state);
        }

        Game::determineOutcome(state);
    }
};
