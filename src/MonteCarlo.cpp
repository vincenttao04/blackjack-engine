#include "MonteCarlo.h"

double MonteCarlo::simulateStandEV(const GameState& state, int simulations) {
    double total = 0.0;

    for (int i = 0; i < simulations; i++) {
        GameState simState = state;

        while (simState.dealer.value() < 17) {
            simState.dealer.addCard(simState.shoe.draw());
        }

        int playerValue = simState.player.value();
        int dealerValue = simState.dealer.value();

        if (dealerValue > 21 || playerValue > dealerValue) {
            total += 1.0;
        } else if (playerValue < dealerValue) {
            total -= 1.0;
        } else {
            total += 0.0;
        };
    };

    return total / simulations;
}