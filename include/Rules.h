#ifndef RULES_H
#define RULES_H

struct Rules {
    static constexpr int numberOfDecks = 1;
    static constexpr double penetration = 0.75;
    static constexpr bool dealerHitsSoft17 = true;
    static constexpr double blackjackPayout = 1.5;
};

#endif