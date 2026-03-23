#ifndef SHOE_H
#define SHOE_H

#include <array>
#include <random>

#include "Card.h"
#include "Rules.h"

struct Shoe {
    std::array<Card, Rules::numberOfDecks * Rules::cardsPerDeck> cards;
    int activeSize = 0;
    std::mt19937 rng{std::random_device{}()};

    void initialize();
    Card draw();
    int remaining() const;
    bool needsReshuffle() const;
};

#endif