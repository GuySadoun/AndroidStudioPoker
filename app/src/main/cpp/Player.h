//
// Created by guy-pc on 17/09/2019.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <string>
#include "Card.h"
#include "Hand.h"

using std::string;

class PlyrErr : public std::exception {
public:
    PlyrErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "PlyrErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class Player {
    double chips;
    const string name;
    vector<const Card*> my_hand;
    std::shared_ptr<Hand> final_hand;
public:
    Player(string name, std::shared_ptr<Hand> finalHand);
    explicit Player(string name);
    ~Player() = default;
    Player(Player&) = delete;
    vector<const Card*> getHand() const;
    std::shared_ptr<Hand> getFinalHand() const;
    const string getName() const;
    vector<const Card*> getCards() const;
    bool putChips(double sum, bool* pBoolean);
    void getChips(double pot);
    void setFinalHand(std::shared_ptr<Hand> best);
    void throwCards();
    void getCard(const Card* card1);

    // compare players
    bool operator > (const Player& player2) const;
    bool operator <= (const Player& player2) const;
    bool operator == (const Player& player2) const;
    bool operator < (const Player& player2) const;
    bool operator >= (const Player& player2) const;
    bool operator != (const Player& player2) const;
};


#endif //POKER_PLAYER_H
