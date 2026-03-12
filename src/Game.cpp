#include "Game.h"

#include <iostream>

#include "Rules.h"

using namespace std;

void Game::dealInitialCards(GameState& state) {
    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());
};

void Game::playerTurn(GameState& state) {
    while (true) {
        cout << "Player: ";
        for (int i = 0; i < state.player.cards.size(); i++) {
            cout << state.player.cards[i].value << " ";
        };
        cout << "| " << state.player.value() << endl;

        if (state.player.isBust()) {
            cout << "Player busts" << endl;
            break;
        };

        cout << "----------------------------------------" << endl;

        char action = 'h';

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
    cout << "Dealer: " << state.dealer.cards[0].value << " "
         << state.dealer.cards[1].value << " | " << state.dealer.value()
         << endl;

    while (state.dealer.value() < 17) {
        state.dealer.addCard(state.shoe.draw());
        cout << "Dealer value: ";
        for (int i = 0; i < state.dealer.cards.size(); i++) {
            cout << state.dealer.cards[i].value << " ";
        };
        cout << "| " << state.dealer.value() << endl;
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

void Game::startRound(GameState& state) {
    cout << "========================================" << endl;
    cout << "               BLACKJACK" << endl;
    cout << "========================================" << endl;
    cout << "Number of decks: " << state.rules.numberOfDecks << endl;
    cout << "----------------------------------------" << endl;

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
