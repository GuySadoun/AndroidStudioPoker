//
// Created by guy-pc on 17/09/2019.
//

#include <list>
#include "DeckOfCards.h"

DeckOfCards::DeckOfCards()  {
    std::list<Card*> shuffle_helper;
    for (int i = 0; i < 52 ; ++i) {
        if (i%2==0)
            shuffle_helper.push_back(new Card((i / 4 + 1), (i % 4)));
        else
            shuffle_helper.push_front(new Card((i / 4 + 1), (i % 4)));
    }
    std::list<Card*>::const_iterator it;
    // create shuffled deck of cards
    for (int i = 1; i <= 52 ; ++i) {
        int random = gen_random(52-i);
        it = shuffle_helper.begin();
        for (int j = 0; j < random; ++j) {
            it++;
        }
        deck.push(*it);
        shuffle_helper.remove(*it);
    }
    cards_left = 52;
}

const Card& DeckOfCards::getCardByReference() {
    Card *card = deck.top();
    deck.pop();
    cards_left--;
    return *card;
}

int DeckOfCards::gen_random(int k) {
    int res;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis1(0, k); //generate num from [0, k]
    res = dis1(gen);
    return res;
}

DeckOfCards::~DeckOfCards() {
    while (!deck.empty()) {
        delete deck.top();
        deck.pop();
        cards_left--;
    }
}

const Card *DeckOfCards::getCardByPointer() {
    Card *card = deck.top();
    deck.pop();
    cards_left--;
    return card;
}

int DeckOfCards::cardsLeft() const {
    return cards_left;
}
