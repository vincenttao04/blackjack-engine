#include "MonteCarlo.h"

#include <iostream>
#include <utility>

std::pair<double, double> MonteCarlo::simulate(const GameState& state) {
    GameState simState = state;
    Card card = simState.dealer.cards.back();
    simState.dealer.cards.pop_back();
    simState.shoe.cards.push_back(card);

    double standEV = simulateStandEV(simState, 100);
    double hitEV = simulateHitEV(simState, 100);
    return {standEV, hitEV};
}

double MonteCarlo::simulateStandEV(const GameState& simState, int simulations) {
    double total = 0.0;

    for (int i = 0; i < simulations; i++) {
        GameState runState = simState;
        runState.shoe.shuffle();

        while (runState.dealer.value() < 17) {
            runState.dealer.addCard(runState.shoe.draw());
        }

        int playerValue = runState.player.value();
        int dealerValue = runState.dealer.value();

        if (dealerValue > 21 || playerValue > dealerValue) {
            total += 1.0;
        } else if (playerValue < dealerValue) {
            total -= 1.0;
        } else {
            total += 0.0;
        };

        std::cout << total / (i + 1) << std::endl;
    };

    return total / simulations;
}

double MonteCarlo::simulateHitEV(const GameState& simState, int simulations) {
    double total = 0.0;
    for (int i = 0; i < simulations; i++) {
        GameState runState = simState;
        runState.shoe.shuffle();

        runState.player.addCard(runState.shoe.draw());

        if (runState.player.isBust()) {
            total -= 1.0;
        } else {
            total += 1.0;
        }

        std::cout << total / (i + 1) << std::endl;
    };

    return total / simulations;
}