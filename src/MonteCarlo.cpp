#include "MonteCarlo.h"

#include <thread>

std::pair<double, double> MonteCarlo::simulate(const GameState& state) {
    GameState simState = state;

    // Hide dealer's hole card and return it to the deck
    Card card = simState.dealer.cards.back();
    simState.dealer.cards.pop_back();
    simState.shoe.cards.push_back(card);

    const int simulations = 1000000;
    const int threads = std::thread::hardware_concurrency();
    const int simulationsPerThread = simulations / threads;
    double standEV = 0.0;
    double hitEV = 0.0;

    for (int i = 0; i < simulations; i++) {
        simState.shoe.shuffle();

        GameState standState = simState;
        GameState hitState = simState;

        standEV += simulateStand(standState);
        hitEV += simulateHit(hitState);
    };

    return {standEV / simulations, hitEV / simulations};
}

double MonteCarlo::simulateStand(GameState& state) {
    // Check for blackjack
    if (state.player.isBlackjack() && !state.dealer.isBlackjack()) {
        return state.rules.blackjackPayout;
    }

    while (state.dealer.value() < 17 ||
           (state.rules.dealerHitsSoft17 && state.dealer.value() == 17 &&
            state.dealer.isSoft())) {
        state.dealer.addCard(state.shoe.draw());
    }

    int playerValue = state.player.value();
    int dealerValue = state.dealer.value();

    if (dealerValue > 21 || playerValue > dealerValue) {
        return 1.0;
    } else if (playerValue < dealerValue) {
        return -1.0;
    }

    return 0.0;
}

double MonteCarlo::simulateHit(GameState& state) {
    state.player.addCard(state.shoe.draw());

    if (state.player.isBust()) {
        return -1.0;
    };

    return simulateDecision(state);
}

double MonteCarlo::simulateDecision(GameState& hitState) {
    if (hitState.player.value() >= 21) {
        return simulateStand(hitState);
    }

    GameState standState = hitState;
    GameState nextHitState = hitState;

    double standEV = simulateStand(standState);
    double hitEV = simulateHit(nextHitState);

    return std::max(standEV, hitEV);
}