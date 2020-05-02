//
// Created by guy-pc on 09/10/2019.
//

#ifndef POKER_TEXASHOLDM_H
#define POKER_TEXASHOLDM_H

#include "PokerTable.h"
#include "Player.h"
#include <string>

enum Action {CHECK, CALL, RAISE, FOLD};

class TexasHoldm {
    PokerTable table;
    int toCall;
public:
    void gamble();
    void playerSit(Player p);
    void dealTable();
    int playerAction(Player p, Action act);
    void finishRound();
};


#endif //POKER_TEXASHOLDM_H
