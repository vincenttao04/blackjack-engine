#ifndef HAND_H
#define HAND_H

#include <array>
#include <utility>

#include "Card.h"
#include "Rules.h"

struct Hand {
    std::array<Card, Rules::maxHandSize> cards;
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