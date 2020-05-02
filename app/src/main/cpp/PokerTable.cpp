//
// Created by guy-pc on 17/09/2019.
//

#include <memory>
#include <algorithm>
#include <cassert>
#include "PokerTable.h"

using std::vector;
using std::shared_ptr;

bool playerCompare(const Player* lp, const Player* rp) {
    return *lp >= *rp;
}

bool handsCompare(const std::shared_ptr<Hand>& lh, const std::shared_ptr<Hand>& rh) {
    return *lh >= *rh;
}

vector<shared_ptr<Hand>> combinations(const Card* possible_cards[]) {
    vector<shared_ptr<Hand>> possible_hands;
    std::string bitmask(5, 1); // 5 leading 1's
    bitmask.resize(7, 0); // 2 trailing 0's

    // insert hands to vector and permute bitmask
    do {
        vector<const Card*> hand(5);
        int place = 0 ;
        for (int i = 0; i < 7; ++i) // [0..7] possible cards
        {
            if (bitmask[i]) {
                hand[place] = possible_cards[i];
                place++;
            }
        }
        if (place > 5 ) {
            string exceptionMessage("possible hand contains more than 5 cards - bitmask with less than 2 trailin 0's");
            throw (TblErr(exceptionMessage));
        }
        Hand possible = *new Hand(hand);
        possible_hands.push_back(std::make_shared<Hand>(possible));
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return possible_hands;
}

void PokerTable::dealCards() {
    for (auto &player : table) {
        if (player) {
            for (int j = 0; j < 2; ++j) {
                player->getCard(deck_of_cards.getCardByPointer());
            }
        }
    }
}

void PokerTable::openFlop() {
    for (auto &i : flop) {
        i = deck_of_cards.getCardByPointer();
    }
    burned.push_back(deck_of_cards.getCardByPointer());
}

void PokerTable::openTurn() {
    turn = deck_of_cards.getCardByPointer();
    burned.push_back(deck_of_cards.getCardByPointer());
}

void PokerTable::openRiver() {
    river = deck_of_cards.getCardByPointer();
}

vector<Player*> PokerTable::calcPotWinner() {
    vector<Player*> ret_val (9);
    shared_ptr<Hand> final_hand;
    for (auto player : table) {
        if (player) {
            final_hand = bestHand(player);
            player->setFinalHand(final_hand);
            ret_val.insert(ret_val.begin(), player);
        }
    }
    sort(ret_val.begin(), ret_val.end(), playerCompare);
    return ret_val;
}

PokerTable::PokerTable() : small_blind_size(5), big_blind(10), table(9), is_sit_taken(9), players_on_table(0) {
    pot = 0;
    for (int i = 0; i < 3; ++i) {
        flop.push_back(nullptr);
        burned.push_back(nullptr);
    }
    river = nullptr;
    turn = nullptr;
    dealer = -1;
}

shared_ptr<Hand> PokerTable::bestHand(Player *player) {
    // collect all cards to check all combinations
    const Card *possible_cards[7];
    possible_cards[0] = player->getHand().at(0);
    possible_cards[1] = player->getHand().at(1);
    for (int i = 0; i < 3; ++i) {
        possible_cards[i + 2] = flop[i];
    }
    possible_cards[5] = turn;
    possible_cards[6] = river;

    // get all possible hands (7 choose 5 combinations)
    vector<shared_ptr<Hand>> all_possible_hands = combinations(possible_cards);
    sort(all_possible_hands.begin(), all_possible_hands.end(), handsCompare);

    shared_ptr<Hand> best_hand = all_possible_hands.front();
    return best_hand;
}

void PokerTable::sitPlayer(int i, Player *p) {
    if (is_sit_taken[i]) return;
    else table[i] = p;
    is_sit_taken[i] = 1;
    players_on_table++;
}

void PokerTable::playerGotUp(int i, Player *p) {
    if (!is_sit_taken[i]) {
        string exceptionMessage("player got up from empty sit");
        throw (TblErr(exceptionMessage));
    }
    else table[i] = nullptr;
    is_sit_taken[i] = 0;
    players_on_table--;
}

vector<const Card *> PokerTable::getFlop() const {
    return flop;
}

const Card *PokerTable::getTurn() const {
    return turn;
}

const Card *PokerTable::getRiver() const {
    return river;
}

void PokerTable::endRound() {
    vector<Player*> sorted_players = calcPotWinner();
    int winners = 1;
    while (sorted_players[0]->getFinalHand() == sorted_players[winners]->getFinalHand()) winners++;
    if (winners > 1) {
        std::cout << "this is log message: there is " << winners << " winners:" << std::endl;
        for (int i=0 ; i < winners ; i++) {
            std::cout << sorted_players[i]->getName() << std::endl;
            sorted_players[i]->getChips(pot/winners);
        }
    } else {
        std::cout << "the winner is: " << sorted_players.front()->getName();
        sorted_players.front()->getChips(pot);
    }
    for (auto &player : table) {
        if (player) {
            player->throwCards();
        }
    }
    while (table[(++dealer)%9] == nullptr) ;
    dealCards();
}

// Debug Functions
void PokerTable::setBoard(Card *board[]) {
    for (int i = 0; i<3; i++) {
        flop[i] = board[i];
    }
    turn = board[3];
    river = board[4];
}

shared_ptr<Hand> PokerTable::checkBestHand(Player* player) {
    return bestHand(player);
}

bool PokerTable::isSitOpen(int i) const {
    bool ret = table.at(i) == nullptr;
    if (ret) assert(is_sit_taken[i] == 0);
    return ret;
}
