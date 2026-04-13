#include "engine/MonteCarlo.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

GameState MonteCarlo::prepareSimState(const GameState& state) {
    GameState simState = state;

    // Move hole card back into shoe for simulation
    swap(simState.shoe.cards[simState.holeCardIndex],
         simState.shoe.cards[simState.shoe.activeSize]);
    simState.shoe.activeSize++;
    simState.dealer.activeSize--;

    return simState;
}

EVResult MonteCarlo::simulate(const GameState& state) {
    GameState simState = prepareSimState(state);

    const int minSimulations = 10000;
    const int maxSimulations = 100000;
    const double epsilon = 0.001;

    const int detectedThreads = thread::hardware_concurrency();
    const int threadCount = (detectedThreads <= 1) ? 1 : detectedThreads;

    double totalHit = 0.0;
    double totalStand = 0.0;
    double totalDouble = 0.0;
    EVResult ev;

    if (threadCount == 1) {
        // Single core path
        double prevStand = 0.0, prevHit = 0.0, prevDouble = 0.0;
        int n = 0;

        while (n < maxSimulations) {
            GameState hitState = simState;
            GameState standState = simState;
            GameState doubleState = simState;

            totalHit += simulateHit(hitState);
            totalStand += simulateStand(standState);
            totalDouble += simulateDouble(doubleState);
            n++;

            if (n % 500 == 0) {
                double currentHit = totalHit / n;
                double currentStand = totalStand / n;
                double currentDouble = totalDouble / n;

                if (n >= minSimulations &&
                    abs(currentHit - prevHit) < epsilon &&
                    abs(currentStand - prevStand) < epsilon &&
                    abs(currentDouble - prevDouble) < epsilon) {
                    break;
                }

                prevHit = currentHit;
                prevStand = currentStand;
                prevDouble = currentDouble;
            }
        }

        ev.hit = totalHit / n;
        ev.stand = totalStand / n;
        ev.doubleDown = totalDouble / n;
    } else {
        // Multi core path
        const int simulationsPerThread = maxSimulations / threadCount;
        mutex mtx;

        auto worker = [&](int simulationsPerThread) {
            double localHitEV = 0.0;
            double localStandEV = 0.0;
            double localDoubleEV = 0.0;

            for (int i = 0; i < simulationsPerThread; i++) {
                GameState hitState = simState;
                GameState standState = simState;
                GameState doubleState = simState;

                localHitEV += simulateHit(hitState);
                localStandEV += simulateStand(standState);
                localDoubleEV += simulateDouble(doubleState);
            };

            // Lock shared data
            lock_guard<mutex> locK(mtx);
            totalHit += localHitEV;
            totalStand += localStandEV;
            totalDouble += localDoubleEV;
        };

        vector<thread> threadPool;
        for (int i = 0; i < threadCount; i++)
            threadPool.emplace_back(worker, simulationsPerThread);
        for (auto& thread : threadPool) thread.join();

        int total = simulationsPerThread * threadCount;
        ev.hit = totalHit / total;
        ev.stand = totalStand / total;
        ev.doubleDown = totalDouble / total;
    }

    return ev;
}

double MonteCarlo::simulateStand(GameState& state) {
    while (state.dealer.value() < 17 ||
           (Rules::dealerHitsSoft17 && state.dealer.value() == 17 &&
            state.dealer.isSoft())) {
        state.dealer.addCard(state.shoe.draw());
    }

    // Check for blackjack, after dealer's turn is completed
    if (state.player.isBlackjack() && !state.dealer.isBlackjack())
        return Rules::blackjackPayout;

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

    if (state.player.isBust()) return -1.0;

    return simulateDecision(state);
}

double MonteCarlo::simulateDecision(GameState& hitState) {
    if (hitState.player.value() >= 21) return simulateStand(hitState);

    GameState standState = hitState;
    GameState nextHitState = hitState;

    double standEV = simulateStand(standState);
    double hitEV = simulateHit(nextHitState);

    return std::max(standEV, hitEV);
}

double MonteCarlo::simulateDouble(GameState& state) {
    state.player.addCard(state.shoe.draw());

    if (state.player.isBust()) return -2.0;

    return 2 * simulateStand(state);
}