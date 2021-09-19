#include "dealer.h"

void Dealer::hit(std::vector<int> & hand){
    hand.push_back(deck.pullCard());
}

int Dealer::handScore(std::vector<int> & hand){
    int score = 0;
    int aces = 0;
    for (int i : hand){
        score += i;
        if (i == 1){
            aces++;
        }
    }
    if (aces){
        for (int j = 0; j < aces; j++){
            if (score <= 21 - 10) score += 10;
        }
    }
    return score;
}

void Dealer::printHand(std::vector<int> & hand, bool hiddenCard){
    for (int card : hand){
        std::cout << "_______" << "   ";
    } 
    std::cout << std::endl;
    for (int card : hand){
        std::cout << "|     |" << "   ";
    }
    std::cout << std::endl;
    for (int card : hand){
        if (hiddenCard){
            std::cout << "| ??? |" << "   ";
            hiddenCard = false;
        } else {
            if (card == 1){
                std::cout << "| ACE |" << "   ";
            } else if (card == 10) {
                std::cout << "|  " << card << " |" << "   ";
            } else {
                std::cout << "|  " << card << "  |" << "   ";
            }
        }
    }
    std::cout << std::endl;
    for (int card : hand){
       std::cout << "|     |" << "   "; 
    }
    std::cout << std::endl;
    for (int card : hand){
        std::cout << "‾‾‾‾‾‾‾" << "   ";
    }
    std::cout << std::endl;
}