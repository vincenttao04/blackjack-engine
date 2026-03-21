#ifndef SHOE_H
#define SHOE_H

#include <array>

#include "Card.h"
#include "Rules.h"

struct Shoe {
    std::array<Card, Rules::numberOfDecks> cards;
    int activeSize = 0;

    void initialize(int numberOfDecks);
    void shuffle();
    Card draw();
    int remaining() const;
    bool needsReshuffle(int numberOfDecks, double penetration) const;
};

#endif