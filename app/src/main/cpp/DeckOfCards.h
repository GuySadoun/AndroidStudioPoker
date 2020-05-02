//
// Created by guy-pc on 17/09/2019.
//

#ifndef POKER_DECKOFCARDS_H
#define POKER_DECKOFCARDS_H

#include <random>
#include "Card.h"
#include <iostream>
#include <string>
#include <utility>
#include <stack>

using std::string;
using std::cout;
using std::endl;

class DeckOfCards {
    std::stack<Card*> deck;
    int gen_random(int k);
    int cards_left;
public:
    DeckOfCards();
    const Card& getCardByReference (); // NOTICE: card is pop out from deck
    const Card* getCardByPointer ();   // NOTICE: card is pop out from deck
    int cardsLeft () const;
    ~DeckOfCards();
};

#endif //POKER_DECKOFCARDS_H
