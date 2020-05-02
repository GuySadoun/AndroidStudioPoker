//
// Created by guy-pc on 09/10/2019.
//

#ifndef POKER_HAND_H
#define POKER_HAND_H

#include "Card.h"
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <algorithm>

using std::vector;
enum hands {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};

class HndErr : public std::exception {
public:
    HndErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "HndErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class Hand {
    int histogram[14] = {};
    hands hand_type;
    vector<const Card*> sorted_hand;
    int findByAmount(int amount) const;
public:
    Hand(const int hands_arr[], const Card *hand[5], const int histo[]);
    explicit Hand(const vector<const Card *>& cards_vector);

    bool operator > (const Hand& hand2) const;
    bool operator <= (const Hand& hand2) const;
    bool operator == (const Hand& hand2) const;
    bool operator < (const Hand& hand2) const;
    bool operator >= (const Hand& hand2) const;
    bool operator != (const Hand& hand2) const;

    // DEBUG function
    vector<const Card *> getHandArray();
};


#endif //POKER_HAND_H
