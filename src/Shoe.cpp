#include "Shoe.h"

#include <algorithm>

void Shoe::initialize() {
    activeSize = 0;

    for (int deck = 0; deck < Rules::numberOfDecks; deck++) {
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
    // Fisher-Yates Draw
    thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, activeSize - 1);
    int randomIndex = dist(rng);
    std::swap(cards[randomIndex], cards[activeSize - 1]);
    return cards[--activeSize];
}

int Shoe::remaining() const {
    return activeSize;
}

bool Shoe::needsReshuffle() const {
    int threshold = int(Rules::numberOfDecks * (1 - Rules::penetration) *
                        Rules::cardsPerDeck);
    return remaining() < threshold;
}