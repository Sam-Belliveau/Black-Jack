#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

#include "Deck.hpp"
#include "Hand.hpp"
#include "Card.hpp"

struct Player
{
  Player(Player& in) : hand{in.hand} {}

  template<std::size_t I>
  Player(Deck<I>& deck)
  {
    hand.reset();
    hand.pushCard(deck.getCard());
    hand.pushCard(deck.getCard());
  }

  bool hit()
  {
    std::cout << "(" << hand.getValue() << ") Another Card? [y/N]: ";

    std::string answer = "";
    std::getline(std::cin, answer);

    if(answer.empty()) return false;
    return (answer[0] == 'y' || answer[0] == 'Y' || answer[0] == '1');
  }

  Hand hand;
};

#endif
