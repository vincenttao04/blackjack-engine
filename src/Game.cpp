#include "Game.h"

void Game::dealInitialCards(GameState& state) {
    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());

    state.player.addCard(state.shoe.draw());
    state.dealer.addCard(state.shoe.draw());
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
