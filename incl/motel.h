//
// Created by vladg on 5/5/2025.
//

#ifndef MOTEL_H
#define MOTEL_H
#include <iostream>
#include <string>
#include "Prices.h"

class player;

class motel : public prices {
    std::string name;

public:
    motel(const std::string &name, int price);

    void print(std::ostream &os) const override {
        os << "Motel: " << name << " (Pret: " << get_price()
           << ", Ipoteca: " << get_sell_price() << ")";

    }

    int calculateRent(const player& owner) const override;

    prices* clone() const override {
        return new motel(*this);
    }
};

#endif //MOTEL_H
