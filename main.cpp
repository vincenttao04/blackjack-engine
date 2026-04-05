#include <iostream>
#include <string>

#include "Backtest.h"
#include "Baseline.h"
#include "Game.h"
#include "Hand.h"
#include "Shoe.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--backtest") {
        cout << "========================================" << endl;
        cout << "               BACKTESTS" << endl;
        cout << "========================================" << endl;
        Backtest::run();
    } else if (argc > 1 && string(argv[1]) == "--baseline") {
        cout << "========================================" << endl;
        cout << "               BASELINE" << endl;
        cout << "========================================" << endl;
        Baseline::run();
    } else {
        GameState state;

        state.shoe.initialize();

        cout << "========================================" << endl;
        cout << "               BLACKJACK" << endl;
        cout << "========================================" << endl;
        cout << "Number of decks: " << Rules::numberOfDecks << endl;
        cout << "Penetration: " << Rules::penetration << endl;
        cout << "Dealer hits soft 17: " << Rules::dealerHitsSoft17 << endl;
        cout << "Blackjack payout: " << Rules::blackjackPayout << endl;
        cout << "----------------------------------------" << endl;

        char playAgain = 'y';
        int count = 1;

        while (playAgain == 'y') {
            if (state.shoe.needsReshuffle()) {
                state.shoe.initialize();
                cout << "Reshuffling..." << endl;
            };

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
    }

    return 0;
}