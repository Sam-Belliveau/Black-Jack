#ifndef HAND_HPP
#define HAND_HPP

#include <cstdint>
#include <iostream>
#include "Deck.hpp"
#include "Card.hpp"

class Hand
{
public:
  static const std::size_t goal_val = 21;

public:
  void reset()
  {
    for(Card i : cards) i = Card();
    count = 0;
  }

  void pushCard(const Card in)
  { if(count <= goal_val) cards[count++] = in; }

  std::size_t getValue()
  {
    std::size_t total = 0;
    for(Card i : cards)
      total += i.getValue();

    for(std::size_t i = 0; i < count && total > goal_val; i++)
      if(cards[i].getType() == Card::Ace)
        total -= 10;

    return total;
  }

  Card getCard(const std::size_t i) const
  {
    if(i < count) return cards[i];
    else return cards[count-1];
  }

  std::size_t getCount() const
  { return count; }

private:
  Card cards[goal_val+1] = { Card() }; // 21 Aces could theoretically happen
  std::size_t count = 0;
};

#endif
