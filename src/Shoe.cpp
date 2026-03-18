#include "Shoe.h"

#include <algorithm>
#include <random>

void Shoe::initialize(const int numberOfDecks) {
    cards.clear();

    for (int deck = 0; deck < numberOfDecks; deck++) {
        for (int value = 1; value <= 9; value++) {
            // Each card value (1-9) appears 4 times per deck (one for each
            // suit)
            for (int suit = 0; suit < 4; suit++) {
                cards.push_back({value});
            }
        }

        // 4 cards with value 10 (10, J, Q, K) * 4 suits = 16 cards per deck
        for (int i = 0; i < 16; i++) {
            cards.push_back({10});
        }
    }
}

void Shoe::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Shoe::draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

int Shoe::remaining() const {
    return cards.size();
}

bool Shoe::needsReshuffle(int numberOfDecks, double penetration) const {
    const int CARDS_PER_DECK = 52;
    int threshold = int(numberOfDecks * (1 - penetration) * CARDS_PER_DECK);
    return remaining() < threshold;
}