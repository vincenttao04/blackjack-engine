#include "Baseline.h"

#include <iostream>

#include "Game.h"
#include "MonteCarlo.h"

using namespace std;

const int numberOfTests = 10000;

void Baseline::autoPlayerTurn(GameState& state) {
    while (state.player.value() < 17 ||
           (state.player.value() == 17 && state.player.isSoft())) {
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

void Baseline::printResults(int wins, int loses, int pushes) {
    double winRate = 100.0 * wins / numberOfTests;
    double loseRate = 100.0 * loses / numberOfTests;
    double pushRate = 100.0 * pushes / numberOfTests;
    double netEV = (double)(wins - loses) / numberOfTests;

    cout << "========================================" << endl;
    cout << "BACKTEST RESULTS (" << numberOfTests << " rounds)" << endl;
    cout << "========================================" << endl;
    cout << "Wins:   " << wins << " (" << winRate << "%)" << endl;
    cout << "Losses: " << loses << " (" << loseRate << "%)" << endl;
    cout << "Pushes: " << pushes << " (" << pushRate << "%)" << endl;
    cout << "Net EV: " << netEV << endl;
    cout << "========================================" << endl;
}

void Baseline::run() {
    int wins = 0;
    int loses = 0;
    int pushes = 0;

    GameState state;

    state.shoe.initialize();

    for (int i = 0; i < numberOfTests; i++) {
        if (state.shoe.needsReshuffle()) {
            state.shoe.initialize();
        };

        Game::dealInitialCards(state);
        autoPlayerTurn(state);

        if (!state.player.isBust()) {
            autoDealerTurn(state);
        }

        Outcome result = Game::determineOutcome(state);

        if (result == Outcome::PlayerWin) {
            wins++;
        };

        if (result == Outcome::DealerWin) {
            loses++;
        };

        if (result == Outcome::Push) {
            pushes++;
        };

        // Print progress every 10% of tests completed
        if ((i + 1) % (numberOfTests / 10) == 0) {
            cout << "Completed " << (i + 1) << "/" << numberOfTests << " tests"
                 << endl;
        }
    }

    printResults(wins, loses, pushes);

    return;
};
