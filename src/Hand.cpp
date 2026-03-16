#include "Hand.h"

std::pair<int, int> Hand::compute() const {
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

    return {total, aceCount};
}

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

int Hand::value() const {
    return compute().first;  // {total, aceCount}
}

bool Hand::isSoft() const {
    auto [total, aceCount] = compute();
    return aceCount > 0 && total <= 21;
}

bool Hand::isBust() const {
    return value() > 21;
}

void Hand::clear() {
    cards.clear();
}