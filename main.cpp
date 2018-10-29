#include <iostream>
#include <chrono>
#include <thread>

#include "Card.hpp"
#include "Deck.hpp"
#include "Hand.hpp"

#include "Player.hpp"
#include "Robot.hpp"

const char* Header   = "\033[30m\033[47m";
const char* GoUpLine = "\x1b[1A";
const char* Reset    = "\033[0m";

template<std::size_t I, class T>
int playGame(Deck<I> &d, T& player)
{
  std::size_t card_num = 1;
  for(; card_num <= 2; card_num++)
    std::cout << card_num << ") " << player.hand.getCard(card_num-1).getStr() << '\n';

  for(bool hit; hit = player.hit();)
  {
    const Card card = d.getCard();
    std::cout << GoUpLine << card_num++ << ") " << card.getStr() <<'\n';
    player.hand.pushCard(card);

    if(player.hand.getValue() > Hand::goal_val)
    {
      std::cout << Header << "Bust!" << Reset <<
        " (" << player.hand.getValue() << ")\n\n";
      return 0;
    }
  }

  std::cout << GoUpLine << Header << "Final Score:" << Reset << ' '
    << player.hand.getValue() << "                            \n\n";
  return player.hand.getValue();
}

int main()
{
  Deck<1> d;
  std::size_t money = __rdtsc()%100 + 150;
  std::cout << "Balance: " << money << "$\n";
  while(money)
  {
    d.reset();
    d.shuffle();

    Player human(d);
    Robot robot(d);

    std::size_t bet = -1;
    while(bet > money || bet == 0)
    {
      std::cout << "Set Your Wager: ";
      std::string answer = "0";
      std::getline(std::cin, answer);
      bet = std::atoll(answer.c_str());
    }
    std::cout << "\n";

    std::cout << Header << "PLAYER'S DECK:" << Reset << std::endl;
    const int pv = playGame(d, human);

    bool Double = false;
		if(bet << 1 <= money && pv)
		{
			std::cout << "Double Wager? ("
				<< bet << "$ -> " << (bet << 1) << "$)" << "[y/N]: ";

			std::string answer = "";
			std::getline(std::cin, answer);

			if (
				answer.empty() ||
				(answer[0] == 'y' || answer[0] == 'Y' || answer[0] == '1')
			) bet <<= 1;
		}

    std::this_thread::sleep_for(std::chrono::milliseconds(1250));

    robot.min = pv ? pv : 16;
    std::cout << '\n' << Header << "ROBOT'S DECK:" << Reset << std::endl;
    const int rv = playGame(d, robot);
    std::this_thread::sleep_for(std::chrono::milliseconds(1250));

    if(pv == rv) { std::cout << "Tie, Split Bet!\n";  money -= bet >> 1; }
    if(pv <  rv) { std::cout << "Robot Wins!\n";  money -= bet; }
    if(pv >  rv) { std::cout << "Player Wins!\n"; money += bet; }
    std::cout << "\nBalance: " << money << "$\n";
  }

  std::cout << "You Lose!\n";
  return 0;
}
