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

    Game::startRound(state);

    return 0;
}