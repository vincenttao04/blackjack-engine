#ifndef RULES_H
#define RULES_H

#include <algorithm>

struct Rules {
    static constexpr int numberOfDecks = 1;
    static constexpr double penetration = 0.75;
    static constexpr bool dealerHitsSoft17 = true;
    static constexpr double blackjackPayout = 1.5;

    static constexpr int cardsPerDeck = 52;
    static constexpr int maxHandSize = std::min(2 * numberOfDecks + 10, 20);
};

#endif