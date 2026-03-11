#include "Game.h"

#include <iostream>

using namespace std;

void Game::dealInitialCards(GameState& state) {
    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());
};

void Game::playerTurn(GameState& state) {
    while (true) {
        cout << "Player value: ";
        for (int i = 0; i < state.player.cards.size(); i++) {
            cout << state.player.cards[i].value << " ";
        };
        cout << "| " << state.player.value() << endl;

        if (state.player.isBust()) {
            cout << "Player busts" << endl;
            break;
        };

        char action = 'h';

        while (true) {
            cout << "Hit (h) or Stand (s): " << endl;
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
    cout << "Dealer value: " << state.dealer.cards[0].value << " "
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
    dealInitialCards(state);

    cout << "Dealer showing: " << state.dealer.cards[0].value << " ?" << endl;

    playerTurn(state);

    if (!state.player.isBust()) {
        Game::playDealer(state);
    }

    Outcome result = Game::determineOutcome(state);

    if (result == Outcome::PlayerWin) {
        cout << "Player wins" << endl;
    };

    if (result == Outcome::DealerWin) {
        cout << "Dealer wins" << endl;
    };

    if (result == Outcome::Push) {
        cout << "Push" << endl;
    };
};
