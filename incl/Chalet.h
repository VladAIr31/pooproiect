//
// Created by vladg on 5/4/2025.
//

#ifndef CHALET_H
#define CHALET_H
#include <iostream>
#include <string>
#include "Prices.h" // Include clasa de bază

class Player;

class Chalet : public Prices {
    std::string name;

public:
    Chalet(const std::string &name, int price);

    void print(std::ostream &os) const override {
        os << "Chalet: " << name << " (Price: " << get_price()
           << ", Mortgage: " << get_sell_price() << ")";

    }

    int calculateRent(const Player& owner) const override;

    Prices* clone() const override {
        return new Chalet(*this);
    }
};


#endif //CHALET_H
