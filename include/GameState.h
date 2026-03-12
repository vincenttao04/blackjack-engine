#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Hand.h"
#include "Shoe.h"
#include "Rules.h"

struct GameState {
    Hand player;
    Hand dealer;

    Shoe shoe;

    Rules rules;
};

#endif