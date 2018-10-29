#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include <cstdint>

/* RANDOM NUMBER STUFF */
#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include <cstdlib>
#include <algorithm>
#include <random>

template<std::size_t decks = 1>
class Deck
{
public:
  static const std::size_t deck_size = 52;
  static const std::size_t card_count = deck_size * decks;

public:
  Deck() : twister(__rdtsc() + time(0)), uni(0, card_count-1)
  { reset(); }

  void reset()
  {
    for(std::size_t i = 0; i < card_count; ++i)
      cards[i] = Card(Card::Family((i / 13) % 4), Card::Type(i%13 + 1));
  }

  /* Make the shuffle as random as possible */
  void shuffle()
  {
    for(std::size_t loop = 0; loop < 0x10000; ++loop)
      for(std::size_t i = 0; i < card_count; ++i)
        std::swap(cards[i], cards[uni(twister)]);
  }

  Card getCard()
  {
    if(size) return cards[--size];
    return Card();
  }

private: // Variables
  Card cards[deck_size] = { Card() };
  std::size_t size = card_count;

private: // Random Numbers
  std::mt19937 twister;
  std::uniform_int_distribution<std::size_t> uni;
};

#endif
