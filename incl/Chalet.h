//
// Created by vladg on 5/4/2025.
//

#ifndef CHALET_H
#define CHALET_H
#include <iostream>
#include "Prices.h"


class chalet : public prices {
    std::string name;

public:
    chalet(const std::string &name, int price)
        : prices(price, price * 3 / 10), name(name) {}

    void print(std::ostream &os) const override {
        os << "Chalet: " << name << ' ' << price << ' ' << sell_price;
    }
};


#endif //CHALET_H
