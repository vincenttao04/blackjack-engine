#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

struct Hand {
    std::vector<Card> cards;

    void addCard(const Card& card);
    int value() const;
    bool isBust() const;
};

#endif