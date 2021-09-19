#include <iostream>
#include "deck.h"


class Dealer
{
private:
    Deck deck;
public:
    void hit(std::vector<int> & hand);
    int handScore(std::vector<int> & hand);
    void printHand(std::vector<int> & hand, bool hiddenCard);
};