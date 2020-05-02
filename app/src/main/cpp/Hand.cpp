//
// Created by guy-pc on 09/10/2019.
//

#include "Hand.h"

int Hand::findByAmount(int amount) const {
    if (amount > 20) {
        for (int i = 1; i < 13; ++i) {
            if (histogram[i] == (amount%20))
                return i;
        }
    } else {
        for (int i = 13; i > 0; --i) {
            if (histogram[i] == amount)
                return i;
        }
    }
    return -1;
}

bool cardCompare(const Card* lh, const Card* rh) {
    return *lh <= *rh;
}

Hand::Hand(const int hands_arr[], const Card **hand, const int histo[]) {

    for (int i = STRAIGHT_FLUSH; i > 0; --i) {
        if (hands_arr[i] > 0) {
            hand_type = (hands) i;
            break;
        }
    }

    for (int h = 1; h < 14; ++h) {
        this->histogram[h] = histo[h];
    }

    for (int j = 0; j < 5; ++j) {
        sorted_hand.insert(sorted_hand.begin(),hand[j]);
    }

    sort(sorted_hand.begin(), sorted_hand.end());
}

Hand::Hand(const vector<const Card*>& cards_vector) {
    int shape_histogram[4] = {0};
    int hands_arr[STRAIGHT_FLUSH + 1] = {0};
    int count_following = 0;
    std::vector<const Card*>::iterator it;
    it = sorted_hand.begin();

    //fill histogram and checks if flush exist
    for (int i = 0; i < 5; ++i) {
        histogram[cards_vector[i]->getNumOfCard()]++;
        it = sorted_hand.insert(it,cards_vector[i]);
        if (++(shape_histogram[cards_vector[i]->getShapeOfCard()]) == 5)
            hands_arr[FLUSH] = 1;
    }

    sort(sorted_hand.begin(), sorted_hand.end(), cardCompare);

    //check if straight, pairs, three or four of kind
    for (int j = 1; j < 14; ++j) {

        if (histogram[j] == 1) {
            count_following++;
        } else {
            count_following = 0;
        }
        if (count_following == 5 || (count_following == 4 && j == 13 && histogram[1] == 1)) { // edge case 10 J Q K A straight
            hands_arr[STRAIGHT]++;
        }


        switch (histogram[j]) {
            case (0):
                break;
            case (1) :
                hands_arr[HIGH_CARD] = 1;
                break;
            case (2) :
                hands_arr[PAIR]++;
                if (hands_arr[PAIR] == 2) {
                    hands_arr[TWO_PAIR] = 1;
                }
                if (hands_arr[THREE_OF_A_KIND]) {
                    hands_arr[FULL_HOUSE] = 1;
                }
                break;
            case (3) :
                hands_arr[THREE_OF_A_KIND] = 1;
                if (hands_arr[PAIR]) {
                    hands_arr[FULL_HOUSE] = 1;
                }
                break;
            case (4) :
                hands_arr[FOUR_OF_A_KIND] = 1;
                break;
            default:
                string exceptionMessage("more then four of a kind");
                throw (HndErr(exceptionMessage));
        }
    }

    if (hands_arr[FLUSH] && hands_arr[STRAIGHT])
        hands_arr[STRAIGHT_FLUSH] = 1;

    for (int type = STRAIGHT_FLUSH; type >= HIGH_CARD; --type) {
        if (hands_arr[type]) {
            hand_type = static_cast<hands>(type);
            break;
        }
    }
}

bool Hand::operator>(const Hand &hand2) const {
    if (this->hand_type > hand2.hand_type)
        return true;
    else if (this->hand_type == hand2.hand_type) {
        switch (hand_type) {
            case STRAIGHT_FLUSH :
                return *sorted_hand.begin() > *hand2.sorted_hand.begin();
            case FOUR_OF_A_KIND :
                if (findByAmount(4) > hand2.findByAmount(4)) {
                    return true;
                } else if (findByAmount(4) == hand2.findByAmount(4)) {
                    return findByAmount(1) > hand2.findByAmount(1);
                }
                return false;
            case FULL_HOUSE :
                if (findByAmount(3) > hand2.findByAmount(3))
                    return true;
                else if (findByAmount(3) == hand2.findByAmount(3))
                    return findByAmount(2) > findByAmount(2);
                return false;
            case FLUSH :
                for (int i = 4; i >= 0; --i) {
                    if (*sorted_hand.at(i) > *hand2.sorted_hand.at(i))
                        return true;
                }
                return false;
            case STRAIGHT :
                return *sorted_hand.begin() > *hand2.sorted_hand.begin();
            case THREE_OF_A_KIND :
                if (findByAmount(3) > hand2.findByAmount(3)) {
                    return true;
                } else if (findByAmount(3) == hand2.findByAmount(3)) {
                    for (int i = 4; i >= 0; --i) {
                        if (*sorted_hand.at(i) > *hand2.sorted_hand.at(i))
                            return true;
                    }
                }
                return false;
            case TWO_PAIR :
                if (findByAmount(2) > hand2.findByAmount(2)) {
                    return true;
                } else if (findByAmount(2) == hand2.findByAmount(2)) {
                    if (findByAmount(22) > hand2.findByAmount(22)) {
                        return true;
                    } else if (findByAmount(22) == hand2.findByAmount(22)) {
                        return findByAmount(1) > hand2.findByAmount(1);
                    }
                }
                return false;
            case PAIR :
                if (findByAmount(2) > hand2.findByAmount(2)) {
                    return true;
                } else if (findByAmount(2) == hand2.findByAmount(2)) {
                    for (int i = 4; i >= 0; --i) {
                        if (*sorted_hand.at(i) > *hand2.sorted_hand.at(i))
                            return true;
                    }
                }
                return false;
            case HIGH_CARD :
                for (int i = 4; i >= 0; --i) {
                    if (*sorted_hand.at(i) > *hand2.sorted_hand.at(i)) {
                        return true;
                    }
                    if (*sorted_hand.at(i) < *hand2.sorted_hand.at(i)) {
                        return false;
                    }
                }
                return false;
        }
    }
    return false;
}

bool Hand::operator<=(const Hand &hand2) const {
    return !(*this > hand2);
}

bool Hand::operator==(const Hand &hand2) const {
    for (int i = 4; i >= 0; --i) {
        if (*sorted_hand.at(i) != *hand2.sorted_hand.at(i))
            return false;
    }
    return true;
}

bool Hand::operator<(const Hand &hand2) const {
    return (!(*this > hand2) && !(*this == hand2));
}

bool Hand::operator>=(const Hand &hand2) const {
    return !(*this < hand2);
}

bool Hand::operator!=(const Hand &hand2) const {
    return !(*this == hand2);
}

vector<const Card *> Hand::getHandArray() {
    return sorted_hand;
}
