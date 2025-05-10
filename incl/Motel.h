//
// Created by vladg on 5/5/2025.
//

#ifndef MOTEL_H
#define MOTEL_H
#include <iostream>
#include <string>
#include "Prices.h"

class Player;

class Motel : public Prices {
    std::string name;

public:
    Motel(const std::string &name, int price);

    void print(std::ostream &os) const override {
        os << "Motel: " << name << " (Pret: " << get_price()
           << ", Ipoteca: " << get_sell_price() << ")";

    }

    int calculateRent(const Player& owner) const override;

    Prices* clone() const override {
        return new Motel(*this);
    }
};

#endif //MOTEL_H
