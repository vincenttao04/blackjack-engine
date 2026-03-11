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
    char action = 'h';

    while (action != 's') {
        cout << "Player value: " << state.player.value() << endl;

        if (state.player.isBust()) {
            cout << "Player busts" << endl;
            break;
        };

        while (true) {
            cout << "Hit (h) or Stand (s): " << endl;
            cin >> action;

            if (action == 'h') {
                playerHit(state);
                break;
            } else if (action == 's') {
                break;
            }

            cout << "Invalid input" << endl;
        }
    };
};

void Game::playDealer(GameState& state) {
    while (state.dealer.value() < 17) {
        state.dealer.addCard(state.shoe.draw());
    }
};

Outcome Game::determineOutcome(const GameState& state) {
    if (state.player.isBust()) {
        return Outcome::DealerWin;
    };

    if (state.dealer.isBust()) {
        return Outcome::PlayerWin;
    };

    if (state.player.value() > state.dealer.value()) {
        return Outcome::PlayerWin;
    };

    if (state.dealer.value() > state.player.value()) {
        return Outcome::DealerWin;
    };

    return Outcome::Push;
};

void Game::playerHit(GameState& state) {
    state.player.addCard(state.shoe.draw());
};

void Game::playRound(GameState& state) {
    dealInitialCards(state);

    cout << "Dealer showing: " << state.dealer.cards[0].value << endl;

    playerTurn(state);

    if (!state.player.isBust()) {
        Game::playDealer(state);
        cout << "Dealer value: " << state.dealer.value() << endl;
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
