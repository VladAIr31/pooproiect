//
// Created by vladg on 5/4/2025.
//

#ifndef CHALET_H
#define CHALET_H
#include <iostream>
#include <string>
#include "Prices.h" // Include clasa de bază

class player;

class chalet : public prices {
    std::string name;

public:
    chalet(const std::string &name, int price);

    void print(std::ostream &os) const override {
        os << "Cabana: " << name << " (Pret: " << get_price()
           << ", Ipoteca: " << get_sell_price() << ")";

    }

    int calculateRent(const player& owner) const override;

    prices* clone() const override {
        return new chalet(*this);
    }
};


#endif //CHALET_H
