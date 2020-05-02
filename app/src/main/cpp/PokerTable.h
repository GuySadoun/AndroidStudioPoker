//
// Created by guy-pc on 17/09/2019.
//

#ifndef POKER_POKERTABLE_H
#define POKER_POKERTABLE_H

#include "DeckOfCards.h"
#include "Player.h"
#include "Hand.h"
#include <vector>

using std::vector;

class TblErr : public std::exception {
public:
    TblErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "TblErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class PokerTable {
    DeckOfCards deck_of_cards;
    vector<int> is_sit_taken;
    vector<const Card*> burned;
    vector<const Card*> flop;
    const Card* river;
    const Card* turn;
    double pot;
    int dealer;
    int small_blind_size;
    int big_blind;
    int players_on_table;
    std::shared_ptr<Hand> bestHand(Player* player);
    vector<Player*> calcPotWinner();

protected:
    vector<Player*> table;

public:
    PokerTable();
    vector<const Card*> getFlop() const;
    const Card* getTurn() const;
    const Card* getRiver() const;
    bool isSitOpen(int i) const;
    void dealCards();
    void openFlop();
    void openTurn();
    void openRiver();
    void endRound();
    void sitPlayer(int i, Player *p);
    void playerGotUp(int i, Player *p);

    // DEBUG!!
    void setBoard(Card* board[]);
    std::shared_ptr<Hand> checkBestHand(Player* player);
};

#endif //POKER_POKERTABLE_H