#include "Game.h"

#include <iostream>

#include "engine/MonteCarlo.h"

using namespace std;

static void printHand(const Hand& hand) {
    for (int i = 0; i < hand.activeSize; i++) {
        cout << hand.cards[i].value << " ";
    };
    cout << "| " << hand.value() << endl;
}

void Game::dealInitialCards(GameState& state) {
    state.player.clear();
    state.dealer.clear();

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    // Hole card is the last drawn card, sitting just outside activeSize
    state.holeCardIndex = state.shoe.activeSize;
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

        EVResult ev = MonteCarlo::simulate(state);
        Action recommended = ev.bestAction();

        cout << "Advisor: stand EV = " << ev.stand << ", hit EV = " << ev.hit
             << ", double EV = " << ev.doubleDown << endl;

        if (recommended == Action::Stand) {
            cout << "RECOMMENDATION: " << "STAND" << endl;
        } else if (recommended == Action::Hit) {
            cout << "RECOMMENDATION: " << "HIT" << endl;
        } else {
            cout << "RECOMMENDATION: " << "SAME" << endl;
        }

        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
             << endl;

        cout << "----------------------------------------" << endl;

        while (true) {
            cout << "Hit (h) or Stand (s) or Double (d): ";
            cin >> action;

            if (action == 'h') {
                playerHit(state);
                break;
            }
            if (action == 'd') {
                playerDouble(state);
                return;
            }
            if (action == 's') return;

            cout << "Invalid input" << endl;
        }
    };
};

void Game::playDealer(GameState& state) {
    cout << "Dealer: ";
    printHand(state.dealer);

    while (state.dealer.value() < 17 ||
           (Rules::dealerHitsSoft17 && state.dealer.value() == 17 &&
            state.dealer.isSoft())) {
        state.dealer.addCard(state.shoe.draw());
        cout << "Dealer: ";
        printHand(state.dealer);
    }
};

Outcome Game::determineOutcome(const GameState& state) {
    int playerValue = state.player.value();
    int dealerValue = state.dealer.value();
    bool playerBlackjack = state.player.isBlackjack();
    bool dealerBlackjack = state.dealer.isBlackjack();

    if (playerBlackjack && !dealerBlackjack) return Outcome::PlayerWin;
    if (dealerBlackjack && !playerBlackjack) return Outcome::DealerWin;

    if (state.player.isBust()) return Outcome::DealerWin;
    if (state.dealer.isBust()) return Outcome::PlayerWin;
    if (playerValue > dealerValue) return Outcome::PlayerWin;
    if (dealerValue > playerValue) return Outcome::DealerWin;

    return Outcome::Push;
};

void Game::playerHit(GameState& state) {
    state.player.addCard(state.shoe.draw());
};

void Game::playerDouble(GameState& state) {
    playerHit(state);

    cout << "Player: ";
    printHand(state.player);

    return;
}

void Game::playRound(GameState& state) {
    dealInitialCards(state);

    cout << "Dealer: " << state.dealer.cards[0].value << " ?" << endl;

    playerTurn(state);

    if (!state.player.isBust()) playDealer(state);

    Outcome result = determineOutcome(state);

    cout << "========================================" << endl;
    cout << "SUMMARY" << endl;
    cout << "Player: ";
    printHand(state.player);
    cout << "Dealer: ";
    printHand(state.dealer);

    if (result == Outcome::PlayerWin) cout << "Result: Player wins" << endl;
    if (result == Outcome::DealerWin) cout << "Result: Dealer wins" << endl;
    if (result == Outcome::Push) cout << "Result: Push" << endl;
    cout << "========================================" << endl;
};
