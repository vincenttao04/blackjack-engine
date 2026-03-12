#include <iostream>

#include "Game.h"
#include "Hand.h"
#include "Rules.h"
#include "Shoe.h"

using namespace std;

int main() {
    GameState state;

    // Configure game rules
    state.rules.numberOfDecks = 6;
    state.rules.dealerHitsSoft17 = false;  // unused
    state.rules.blackjackPayout = 1.5;     // unused

    state.shoe.initialize(state.rules.numberOfDecks);
    state.shoe.shuffle();

    char playAgain = 'y';

    while (playAgain == 'y') {
        Game::playRound(state);

        while (true) {
            cout << "Play again? (y/n): ";
            cin >> playAgain;

            if (playAgain == 'y' || playAgain == 'n') {
                break;
            }

            cout << "Invalid input" << endl;
        };
    };

    return 0;
}