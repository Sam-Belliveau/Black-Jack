#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <iostream>
#include <chrono>
#include <thread>

#include "Hand.hpp"
#include "Card.hpp"

struct Robot
{
  Robot(Robot& in) : hand{in.hand} {}

  template<std::size_t I>
  Robot(Deck<I>& deck)
  {
    hand.reset();
    hand.pushCard(deck.getCard());
    hand.pushCard(deck.getCard());
  }

  bool hit()
  {
    if(min == 0) min = 16;

    std::cout << "(" << hand.getValue() << ") Another Card? (Thinking...)\r"
      << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if(hand.getValue() < 17 && hand.getValue() == min)
    {
      std::cout << "(" << hand.getValue() << ") Another Card? Yes          \n"
        << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      return true;
    } else if(hand.getValue() < min)
    {
      std::cout << "(" << hand.getValue() << ") Another Card? Yes          \n"
        << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      return true;
    } else
    {
      std::cout << "(" << hand.getValue() << ") Another Card? No           \n"
        << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      return false;
    }
  }

  std::size_t min = 17;
  Hand hand;
};

#endif
