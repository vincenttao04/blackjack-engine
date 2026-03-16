#ifndef HAND_H
#define HAND_H

#include <utility>
#include <vector>

#include "Card.h"

struct Hand {
    std::vector<Card> cards;

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