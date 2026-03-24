#ifndef HAND_H
#define HAND_H

#include <utility>
#include <array>

#include "Card.h"

struct Hand {
    std::array<Card, 11> cards;
    int activeSize = 0;

   private:
    std::pair<int, int> compute() const;

   public:
    void addCard(const Card& card);
    int value() const;
    bool isSoft() const;
    bool isBust() const;
    bool isBlackjack() const;
    void clear();
};

#endif