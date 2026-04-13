#include "Hand.h"

std::pair<int, int> Hand::compute() const {
    int total = 0;
    int aceCount = 0;

    for (int i = 0; i < activeSize; i++) {
        if (cards[i].value == 1) {
            aceCount++;
            total += 11;
        } else {
            total += cards[i].value;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return {total, aceCount};
}

void Hand::addCard(const Card& card) {
    cards[activeSize++] = card;
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

bool Hand::isBlackjack() const {
    return value() == 21 && activeSize == 2;
}

bool Hand::canDouble() const {
    return activeSize == 2;
}

void Hand::clear() {
    activeSize = 0;
}