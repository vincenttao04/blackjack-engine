#include <iostream>

#include "Game.h"
#include "Hand.h"
#include "Rules.h"
#include "Shoe.h"

using namespace std;

int main() {
    GameState state;

    // Configure game rules
    state.rules.numberOfDecks = 1;
    state.rules.penetration = 0.75;
    state.rules.dealerHitsSoft17 = false;  // unused
    state.rules.blackjackPayout = 1.5;     // unused

    state.shoe.initialize(state.rules.numberOfDecks);
    state.shoe.shuffle();

    cout << "========================================" << endl;
    cout << "               BLACKJACK" << endl;
    cout << "========================================" << endl;
    cout << "Number of decks: " << state.rules.numberOfDecks << endl;
    cout << "----------------------------------------" << endl;

    char playAgain = 'y';
    int count = 1;

    while (playAgain == 'y') {
        if (state.shoe.remaining() <
            (int(state.rules.numberOfDecks * (1 - state.rules.penetration) *
                 52))) {
            state.shoe.initialize(state.rules.numberOfDecks);
            state.shoe.shuffle();
            cout << "Reshuffling..." << endl;
        }

        cout << "Round " << count << ": " << state.shoe.remaining()
             << " cards remaining" << endl;

        Game::playRound(state);

        while (true) {
            cout << "Play again? (y/n): ";
            cin >> playAgain;

            if (playAgain == 'y' || playAgain == 'n') {
                break;
            }

            cout << "Invalid input" << endl;
        };

        count++;
    };

    return 0;
}