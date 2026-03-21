#ifndef SHOE_H
#define SHOE_H

#include <array>

#include "Card.h"

const int MAX_SIZE = 52;
struct Shoe {
    std::array<Card, MAX_SIZE> cards;

    void initialize(int numberOfDecks);
    void shuffle();
    Card draw();
    int remaining() const;
    bool needsReshuffle(int numberOfDecks, double penetration) const;
};

#endif