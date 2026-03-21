#ifndef SHOE_H
#define SHOE_H

#include <array>
#include <random>

#include "Card.h"
#include "Rules.h"

struct Shoe {
    std::array<Card, Rules::numberOfDecks * 52> cards;
    int activeSize = 0;
    std::mt19937 rng{std::random_device{}()};

    void initialize(int numberOfDecks);
    void shuffle();
    Card draw();
    int remaining() const;
    bool needsReshuffle(int numberOfDecks, double penetration) const;
};

#endif