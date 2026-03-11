#include <iostream>

#include "Game.h"
#include "Hand.h"
#include "Rules.h"
#include "Shoe.h"

using namespace std;

int main() {
    Rules rules;
    GameState state;

    state.shoe.initialize(rules.numberOfDecks);
    state.shoe.shuffle();

    Game::dealInitialCards(state);

    cout << "Player value: " << state.player.value() << endl;
    cout << "Dealer showing: " << state.dealer.cards[0].value << endl;

    Game::playDealer(state);

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

    return 0;
}