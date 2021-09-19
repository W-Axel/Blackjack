#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <windows.h>
#include "dealer.h"

#define COLOR_DEFAULT 15
#define COLOR_NOTICE 14
#define COLOR_DEALER 12
#define COLOR_PLAYER 9

void setColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printRound(std::vector<int> & player_hand, std::vector<int> & dealer_hand, Dealer & dealer, bool hiddenCard){
    setColor(COLOR_DEALER);
    std::cout << "DEALER HAND:" << std::endl;
    dealer.printHand(dealer_hand, hiddenCard);
    if (!hiddenCard){
        std::cout << "HAND TOTAL: " << dealer.handScore(dealer_hand) << std::endl;
    }
    std::cout << std::endl;
    setColor(COLOR_PLAYER);
    std::cout << "PLAYER HAND:" << std::endl;
    dealer.printHand(player_hand, false);
    std::cout << "HAND TOTAL: " << dealer.handScore(player_hand) << std::endl;
    std::cout << std::endl;
    setColor(COLOR_DEFAULT);
}

void startRound(std::vector<int> & player_hand, std::vector<int> & dealer_hand, Dealer & dealer){
    player_hand.clear();
    dealer_hand.clear();

    dealer.hit(player_hand);
    dealer.hit(dealer_hand);
    dealer.hit(player_hand);
    dealer.hit(dealer_hand);

    printRound(player_hand, dealer_hand, dealer, true);
}


int main(int argc, char const *argv[])
{
    Dealer dealer;
    std::vector<int> player_hand;
    std::vector<int> dealer_hand;
    bool continue_playing = true;
    
    enum GameStates {
        start_round = 1,
        player_turn = 2,
        dealer_turn = 3,
        bust = 4,
        blackjack = 5,
        victory = 6,
        loss = 7,
        end_round = 8
    };

    int next_state = start_round;
    std::string input;

    while (true){
        
        switch (next_state)
        {
        case start_round:
            startRound(player_hand, dealer_hand, dealer);
            if (dealer.handScore(player_hand) == 21) next_state = blackjack;
            else next_state = player_turn;
            break;

        case player_turn:
            std::cout << "HIT / STAND? (h/s) ";
            std::cin >> input;
            std::cout << std::endl;
            if (input == "h"){
                dealer.hit(player_hand);
                printRound(player_hand, dealer_hand, dealer, true);
                if (dealer.handScore(player_hand) > 21){
                    next_state = bust;
                } else if (dealer.handScore(player_hand) == 21){
                    next_state = blackjack;
                }
            } else {
                next_state = dealer_turn;
            }
            break;

        case dealer_turn:
            printRound(player_hand, dealer_hand, dealer, false);
            if (dealer.handScore(dealer_hand) < 17 || !(dealer.handScore(dealer_hand) > dealer.handScore(player_hand))){
                std::cout << "Dealer hits!" << std::endl;
                std::cout << std::endl;
                dealer.hit(dealer_hand);
                next_state = dealer_turn;
            } else {
                if (dealer.handScore(dealer_hand) > 21) {
                    next_state = victory;
                } else if (dealer.handScore(dealer_hand) > dealer.handScore(player_hand)) {
                    next_state = loss;
                } else {
                    next_state = victory;
                }
            }
            break;

        case bust: case blackjack: case victory: case loss:
            setColor(COLOR_NOTICE);
            switch (next_state)
            {
            case bust:
                std::cout << "It's a bust... ｡ﾟ･（>﹏<）･ﾟ｡" << std::endl;
                break;
            case blackjack:
                std::cout << "BLACKJACK! ＼(￣▽￣)／" << std::endl;
                break;
            case victory:
                std::cout << "You win! (ᵔ◡ᵔ)" << std::endl;
                break;
            case loss:
                std::cout << "You lose... (╥﹏╥)" << std::endl;
                break;
            }
            std::cout << std::endl;
            setColor(COLOR_DEFAULT);
            next_state = end_round;
            break;

        case end_round:
            std::cout << "Continue playing? (y/n) ";
            std::cin >> input;
            if (input == "n") return 0;
            else next_state = start_round;
            break;
        }
    }  
    return 0;
}

