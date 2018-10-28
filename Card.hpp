#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <cstdint>

struct Card
{
public:
  enum Family : uint8_t
  { BlankFam = 0xf, Clubs = 0, Diamonds = 1, Hearts = 2, Spades = 3 };

  enum Type : uint8_t
  {
    BlankType = 0xf,
    Ace = 1,
    t2 = 2, t3 = 3, t4 = 4,
    t5 = 5, t6 = 6, t7 = 7,
    t8 = 8, t9 = 9, t10 = 10,
    Jack = 11,
    Queen = 12,
    King = 13
  };

public: // Constructor
  Card() : family{BlankFam}, type{BlankType} {}
  Card(const Card &in) : family{in.family}, type{in.type} {}
  Card(const Family f, const Type t) : family{f}, type{t} {}

  std::size_t getValue() const
  {
    if(type == BlankType) return 0;
    else if(type >= 2 && type <= 10) return type;
    else if(type == Ace) return 11;
    return 10;
  }

  Family getFamily() const { return Family(family); }
  Type getType() const { return Type(type); }

  std::string getStr() const
  {
    std::string out;
    switch (type) {
      case Type::Ace:   out = "Ace of "; break;
      case Type::t2:    out = "2 of "; break;
      case Type::t3:    out = "3 of "; break;
      case Type::t4:    out = "4 of "; break;
      case Type::t5:    out = "5 of "; break;
      case Type::t6:    out = "6 of "; break;
      case Type::t7:    out = "7 of "; break;
      case Type::t8:    out = "8 of "; break;
      case Type::t9:    out = "9 of "; break;
      case Type::t10:   out = "10 of "; break;
      case Type::Jack:  out = "Jack of "; break;
      case Type::Queen: out = "Queen of "; break;
      case Type::King:  out = "King of "; break;
      default: out = ""; break;
    }

    switch (family) {
      case Family::Clubs:    out += "Clubs"; break;
      case Family::Diamonds: out += "Diamonds"; break;
      case Family::Hearts:   out += "Hearts"; break;
      case Family::Spades:   out += "Spades"; break;
      default: break;
    }

    for(std::size_t i = out.length(); i < 32; ++i)
      out += ' ';

    return out;
  }

private: // Variables
  uint8_t family : 4, type : 4;
};

#endif
