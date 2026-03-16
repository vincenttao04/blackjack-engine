#include "Game.h"

#include <iostream>

#include "MonteCarlo.h"

using namespace std;

static void printHand(const Hand& hand) {
    for (int i = 0; i < hand.cards.size(); i++) {
        cout << hand.cards[i].value << " ";
    };
    cout << "| " << hand.value() << endl;
}

void Game::dealInitialCards(GameState& state) {
    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());
};

void Game::playerTurn(GameState& state) {
    char action = 'h';

    while (true) {
        cout << "Player: ";
        printHand(state.player);

        if (state.player.isBust()) {
            cout << "Player busts" << endl;
            break;
        };

        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
             << endl;
        auto [standEV, hitEV] = MonteCarlo::simulate(state);
        cout << "Advisor: stand EV = " << standEV << ", hit EV = " << hitEV
             << endl;

        if (standEV > hitEV) {
            cout << "RECOMMENDATION: " << "STAND" << endl;
        } else if (hitEV > standEV) {
            cout << "RECOMMENDATION: " << "HIT" << endl;
        } else {
            cout << "RECOMMENDATION: " << "SAME" << endl;
        }

        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
             << endl;

        cout << "----------------------------------------" << endl;

        while (true) {
            cout << "Hit (h) or Stand (s): ";
            cin >> action;

            if (action == 'h') {
                playerHit(state);
                break;
            }
            if (action == 's') {
                return;
            }

            cout << "Invalid input" << endl;
        }
    };
};

void Game::playDealer(GameState& state) {
    cout << "Dealer: ";
    printHand(state.dealer);

    while (state.dealer.value() < 17) {
        state.dealer.addCard(state.shoe.draw());
        cout << "Dealer: ";
        printHand(state.dealer);
    }
};

Outcome Game::determineOutcome(const GameState& state) {
    int playerValue = state.player.value();
    int dealerValue = state.dealer.value();

    if (state.player.isBust()) {
        return Outcome::DealerWin;
    };

    if (state.dealer.isBust()) {
        return Outcome::PlayerWin;
    };

    if (playerValue > dealerValue) {
        return Outcome::PlayerWin;
    };

    if (dealerValue > playerValue) {
        return Outcome::DealerWin;
    };

    return Outcome::Push;
};

void Game::playerHit(GameState& state) {
    state.player.addCard(state.shoe.draw());
};

void Game::playRound(GameState& state) {
    state.player.clear();
    state.dealer.clear();

    dealInitialCards(state);

    cout << "Dealer: " << state.dealer.cards[0].value << " ?" << endl;

    playerTurn(state);

    if (!state.player.isBust()) {
        Game::playDealer(state);
    }

    Outcome result = Game::determineOutcome(state);

    cout << "========================================" << endl;
    if (result == Outcome::PlayerWin) {
        cout << "Result: Player wins" << endl;
    };

    if (result == Outcome::DealerWin) {
        cout << "Result: Dealer wins" << endl;
    };

    if (result == Outcome::Push) {
        cout << "Result: Push" << endl;
    };
    cout << "========================================" << endl;
};
