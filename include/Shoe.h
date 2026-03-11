#ifndef SHOE_H
#define SHOE_H

#include <vector>

#include "Card.h"

struct Shoe {
    std::vector<Card> cards;

    void initialize(int numOfDecks);
    void shuffle();
    Card draw();
};

#endif