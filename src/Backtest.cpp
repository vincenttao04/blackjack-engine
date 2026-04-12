#include "Backtest.h"

#include <iostream>

#include "Game.h"
#include "engine/MonteCarlo.h"

using namespace std;

namespace Strategy {
Action monteCarlo(const GameState& state) {
    return MonteCarlo::simulate(state).bestAction();
}

Action baseline(const GameState& state) {
    return (state.player.value() < 17 ||
            (state.player.value() == 17 && state.player.isSoft()))
               ? Action::Hit
               : Action::Stand;
}
}  // namespace Strategy

void Backtest::autoDealerTurn(GameState& state) {
    while (state.dealer.value() < 17 ||
           (Rules::dealerHitsSoft17 && state.dealer.value() == 17 &&
            state.dealer.isSoft())) {
        state.dealer.addCard(state.shoe.draw());
    }
};

void Backtest::printResults(int wins, int loses, int pushes, int rounds) {
    double winRate = 100.0 * wins / rounds;
    double loseRate = 100.0 * loses / rounds;
    double pushRate = 100.0 * pushes / rounds;
    double netEV = (double)(wins - loses) / rounds;

    cout << "========================================" << endl;
    cout << "BACKTEST RESULTS (" << rounds << " rounds)" << endl;
    cout << "========================================" << endl;
    cout << "Wins:   " << wins << " (" << winRate << "%)" << endl;
    cout << "Losses: " << loses << " (" << loseRate << "%)" << endl;
    cout << "Pushes: " << pushes << " (" << pushRate << "%)" << endl;
    cout << "Net EV: " << netEV << endl;
    cout << "========================================" << endl;
}

void Backtest::run(Strategy strategy, int rounds) {
    int wins = 0, loses = 0, pushes = 0;

    GameState state;
    state.shoe.initialize();

    for (int i = 0; i < rounds; i++) {
        if (state.shoe.needsReshuffle()) {
            state.shoe.initialize();
        };

        Game::dealInitialCards(state);

        while (!state.player.isBust()) {
            Action action = strategy(state);

            if (action == Action::Stand) break;

            if (action == Action::Hit) {
                Game::playerHit(state);
                continue;
            }

            break;
        }

        if (!state.player.isBust()) autoDealerTurn(state);

        Outcome result = Game::determineOutcome(state);
        if (result == Outcome::PlayerWin) wins++;
        if (result == Outcome::DealerWin) loses++;
        if (result == Outcome::Push) pushes++;

        // Print progress every 10% of tests completed
        if ((i + 1) % (rounds / 10) == 0) {
            cout << "Completed " << (i + 1) << "/" << rounds << " tests"
                 << endl;
        }
    }

    printResults(wins, loses, pushes, rounds);

    return;
};
