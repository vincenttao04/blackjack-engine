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

    cout << "Dealer showing: " << state.dealer.cards[0].value << endl;

    while (true) {
        cout << "Player value: " << state.player.value() << endl;
        cout << "Hit (h) or Stand (s): ";

        if (state.player.isBust()) {
            cout << "Player busts" << endl;
            break;
        };

        char action;
        cin >> action;

        if (action == 'h') {
            state.player.addCard(state.shoe.draw());
        } else if (action == 's') {
            break;
        }
    };

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

    return 0;
}