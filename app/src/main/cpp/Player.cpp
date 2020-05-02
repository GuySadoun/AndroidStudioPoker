//
// Created by guy-pc on 17/09/2019.
//

#include "Player.h"
#include <utility>
#include <cmath>

Player::Player(string name, std::shared_ptr<Hand> finalHand) : name(std::move(name)), final_hand(std::move(finalHand)), my_hand(2) {
    chips = 1000;
}

Player::Player(string name) : name(std::move(name)) {
    chips = 1000;
    for (int i=0 ; i<2 ; i++) {
        my_hand.push_back(nullptr);
    }
}

vector<const Card*> Player::getHand() const {
    return my_hand;
}

void Player::getCard(const Card* card1) {
    if (!my_hand[0])
        my_hand[0] = card1;
    else if (!my_hand[1])
        my_hand[1] = card1;
    else {
        string exceptionMessage("both card aren't null and try to deal");
        throw (PckErr(exceptionMessage));
    }
}

void Player::throwCards() {
    my_hand.at(0) = nullptr;
    my_hand.at(1) = nullptr;
}

bool Player::putChips(double sum, bool* allIn) {
    if (sum > chips) return false;
    *allIn = (floor(sum) == floor(chips));
    chips -= sum;
    return true;
}

void Player::getChips(double pot) {
    chips += pot;
}

void Player::setFinalHand( std::shared_ptr<Hand> best) {
    final_hand = std::move(best);
}

bool Player::operator>(const Player &player2) const {
    return this->final_hand > player2.final_hand;
}

bool Player::operator<=(const Player &player2) const {
    return this->final_hand <= player2.final_hand;
}

bool Player::operator==(const Player &player2) const {
    return this->final_hand == player2.final_hand;
}

bool Player::operator<(const Player &player2) const {
    return this->final_hand < player2.final_hand;
}

bool Player::operator>=(const Player &player2) const {
    return this->final_hand >= player2.final_hand;
}

bool Player::operator!=(const Player &player2) const {
    return this->final_hand != player2.final_hand;
}

vector<const Card*> Player::getCards() const {
    return my_hand;
}

std::shared_ptr<Hand> Player::getFinalHand() const {
    return final_hand;
}

const string Player::getName() const {
    return name;
}

