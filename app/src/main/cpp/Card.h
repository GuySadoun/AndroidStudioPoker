//
// Created by guy-pc on 17/09/2019.
//

#ifndef POKER_CARD_H
#define POKER_CARD_H

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

typedef enum {HEARTS, DIAMONDS, SPADES, CLUBS} Shapes;

class PckErr : public std::exception {
public:
    PckErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "PckErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class Card {
    int worth;
    int num;
    Shapes shape_id;
    string name;
    string shape;
    string color;
    char symbol;
    string xmlName;

    string intToShape(int n) const ;
    string intToColor(int n) const ;
    string intToLetter(int n) const ;
public:
    string getXml() const ;
    Card(int n, int shap);
    Card();
    int getNumOfCard() const;
    int getShapeOfCard() const;
    friend std::ostream& operator<<(std::ostream& os, const Card& c);
    bool operator >(const Card& other) const;
    bool operator <(const Card& other) const;
    bool operator ==(const Card& other) const;
    bool operator >=(const Card& other) const;
    bool operator <=(const Card& other) const;
    bool operator !=(const Card& other) const;
};
std::ostream& operator<<(std::ostream& os, const Card& c);
#endif //POKER_CARD_H
