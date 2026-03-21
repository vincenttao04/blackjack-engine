#include "MonteCarlo.h"

#include <iostream>  // temp
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

std::pair<double, double> MonteCarlo::simulate(const GameState& state) {
    GameState simState = state;

    // Return dealer's hole card to the deck
    Card card = simState.dealer.cards.back();
    simState.dealer.cards.pop_back();
    simState.shoe.cards.push_back(card);

    const int simulations = 1000000;
    const int threadCount = thread::hardware_concurrency();
    cout << "Number of threads: " << threadCount << endl;  // temp
    const int simulationsPerThread = simulations / threadCount;
    double standEV = 0.0;
    double hitEV = 0.0;
    mutex mtx;

    auto worker = [&](int simulationsPerThread) {
        double localStandEV = 0.0;
        double localHitEV = 0.0;
        GameState threadState = simState;

        for (int i = 0; i < simulationsPerThread; i++) {
            threadState.shoe.shuffle();
            GameState standState = threadState;
            GameState hitState = threadState;

            localStandEV += simulateStand(standState);
            localHitEV += simulateHit(hitState);
        };

        // Lock shared data
        lock_guard<mutex> locK(mtx);
        standEV += localStandEV;
        hitEV += localHitEV;
    };

    vector<thread> threadPool;
    for (int i = 0; i < threadCount; i++) {
        threadPool.emplace_back(worker, simulationsPerThread);
    };

    for (auto& thread : threadPool) {
        thread.join();
    }

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