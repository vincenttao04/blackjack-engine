#include "Hand.h"

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

int Hand::value() const {
    int total = 0;
    int aceCount = 0;

    for (const Card& card : cards) {
        if (card.value == 1) {
            aceCount++;
            total += 11;
        } else {
            total += card.value;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}

bool Hand::isBust() const {
    return value() > 21;
}