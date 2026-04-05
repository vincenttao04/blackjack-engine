#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Hand.h"
#include "Shoe.h"

struct GameState {
    Hand player;
    Hand dealer;

    Shoe shoe;

    int holeCardIndex = -1;
};

#endif