#include "Backtest.h"

#include <iostream>

#include "Game.h"
#include "GameState.h"
#include "MonteCarlo.h"

using namespace std;

const int numberOfTests = 100;

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

void Backtest::printResults(int wins, int loses, int pushes) {
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

void Backtest::run() {
    int wins = 0;
    int loses = 0;
    int pushes = 0;

    GameState state;

    state.shoe.initialize();

    for (int i = 0; i < numberOfTests; i++) {
        if (state.shoe.needsReshuffle()) {
            state.shoe.initialize();
        };

        state.player.clear();
        state.dealer.clear();

        Game::dealInitialCards(state);
        autoPlayerTurn(state);

        Game::playDealer(state);

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
    }

    printResults(wins, loses, pushes);

    return;
};
