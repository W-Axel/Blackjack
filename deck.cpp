#include "deck.h"

Deck::Deck(){
    reset();
}

void Deck::reset(){
    cards_ptr->clear();
    for (int i=1; i<14; i++){
        for (int n=0; n<4; n++){
            if(i>10){
                cards_ptr->push_back(10);
            } else {
                cards_ptr->push_back(i);
            }
        }
    }
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::shuffle(std::begin(*cards_ptr), std::end(*cards_ptr), generator);
}

int Deck::size(){
    return cards_ptr->size();
}

int Deck::pullCard(){
    if (size() == 0) reset();
    int pulledCard = cards_ptr->back();
    cards_ptr->pop_back();
    return pulledCard;
}
