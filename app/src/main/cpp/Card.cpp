//
// Created by guy-pc on 17/09/2019.
//

#include "Card.h"

Card::Card(int n, int shap) : num(n) , shape_id((Shapes)shap) {
    if (num>10 || num ==1) {
        switch (num) {
            case 11:
                name = "Jack" + intToShape(shap);
                symbol ='J';
                xmlName = "j_" + intToLetter(shap);
                break;
            case 12:
                name = "Dama" + intToShape(shap);
                symbol = 'Q';
                xmlName = "q_" + intToLetter(shap);
                break;
            case 13:
                name = "King" + intToShape(shap);
                symbol = 'K';
                xmlName = "k_" + intToLetter(shap);
                break;
            case 1:
                name = "Ace" + intToShape(shap);
                symbol = 'A';
                xmlName = "a_" + intToLetter(shap);
                break;
            default:
                string exceptionMessage("num > 13");
                throw (PckErr(exceptionMessage));
        }
    } else {
        symbol = 'N';
        name = std::to_string(num) + intToShape(shap);
        xmlName = std::to_string(num) + "_" + intToLetter(shap);
    }
    if (num == 1) {
        worth = 14;
    } else {
        worth = num;
    }
    shape = intToShape(shap);
    color = intToColor(shap);
}

Card::Card() {
    symbol = 'n';
    num = 0;
    name = "null";
    shape = "circle";
    shape_id = HEARTS;
    color = "blue";
}

string Card::intToShape(int n) const {
    switch (n) {
        case 0:
            return  "♥";
        case 1:
            return  "♦";
        case 2:
            return  "♠";
        case 3:
            return  "♣";
        default:
            string exceptionMessage("4 > shape_id < 0 - intToShape");
            throw (PckErr(exceptionMessage));
    }
}

string Card::intToColor(int n) const {
    if (n == 0 || n == 1) {
        return "red";
    }
    if (n == 2 || n == 3) {
        return "black";
    }
    string exceptionMessage("4 > shape_id < 0 - intToColor");
    throw (PckErr(exceptionMessage));
}

std::ostream &operator<<(std::ostream &os, const Card& c) {
    if (c.num < 11 && c.num != 1)
        os << std::to_string(c.num) + c.shape;
    else
        os << c.symbol + c.shape;
//    os << endl << "xml: " << c.getXml();
    return os;
}

int Card::getNumOfCard() const{
    return num;
}

int Card::getShapeOfCard() const{
    return shape_id;
}

bool Card::operator>(const Card &other)  const{
    return this->worth > other.worth;
}

bool Card::operator<(const Card &other)  const{
    return this->worth < other.worth;
}

bool Card::operator==(const Card &other)  const{
    return this->worth == other.worth;
}

bool Card::operator>=(const Card &other)  const{
    return this->worth >= other.worth;
}

bool Card::operator<=(const Card &other)  const{
    return this->worth <= other.worth;
}

bool Card::operator!=(const Card &other)  const{
    return this->worth != other.worth;
}

string Card::intToLetter(int n) const {
    switch (n) {
        case 0:
            return  "h";
        case 1:
            return  "m";
        case 2:
            return  "l";
        case 3:
            return  "t";
        default:
            string exceptionMessage("4 > shape_id < 0 - intToShape");
            throw (PckErr(exceptionMessage));
    }
}

string Card::getXml() const {
    return xmlName;
}

