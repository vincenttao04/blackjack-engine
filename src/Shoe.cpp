#include "Shoe.h"

#include <algorithm>

void Shoe::initialize(const int numberOfDecks) {
    activeSize = 0;

    for (int deck = 0; deck < numberOfDecks; deck++) {
        for (int value = 1; value <= 9; value++) {
            // Each card value (1-9) appears 4 times per deck (one for each
            // suit)
            for (int suit = 0; suit < 4; suit++) {
                cards[activeSize++] = {value};
            }
        }

        // 4 cards with value 10 (10, J, Q, K) * 4 suits = 16 cards per deck
        for (int i = 0; i < 16; i++) {
            cards[activeSize++] = {10};
        }
    }
}

Card Shoe::draw() {
    std::uniform_int_distribution<int> dist(0, activeSize - 1);
    int randomIndex = dist(rng);
    std::swap(cards[randomIndex], cards[activeSize - 1]);
    return cards[--activeSize];
}

int Shoe::remaining() const {
    return cards.size();
}

bool Shoe::needsReshuffle(int numberOfDecks, double penetration) const {
    const int CARDS_PER_DECK = 52;
    int threshold = int(numberOfDecks * (1 - penetration) * CARDS_PER_DECK);
    return remaining() < threshold;
}