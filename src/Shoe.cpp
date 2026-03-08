#include "Shoe.h"

#include <algorithm>
#include <random>

Card Shoe::draw() {
  Card card = cards.back();
  cards.pop_back();
  return card;
}
