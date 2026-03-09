#include <iostream>

#include "Hand.h"
#include "Rules.h"
#include "Shoe.h"

using namespace std;

int main() {
    Rules rules;
    Shoe shoe;

    shoe.initialize(rules.numberOfDecks);
    shoe.shuffle();

    Hand dealer;
    Hand player;

    dealer.addCard(shoe.draw());
    player.addCard(shoe.draw());
    player.addCard(shoe.draw());

    cout << "dealer's hand total: " << dealer.value() << endl;
    cout << "player's hand total: " << player.value() << endl;

    return 0;
}