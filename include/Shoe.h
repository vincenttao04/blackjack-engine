#ifndef SHOE_H
#define SHOE_H

#include <vector>

#include "Card.h"

struct Shoe {
    std::vector<Card> cards;

    void initialize(int numberOfDecks);
    void shuffle();
    Card draw();
    int remaining() const;
    bool needsReshuffle(int numberOfDecks, double penetration) const;
};

#endif