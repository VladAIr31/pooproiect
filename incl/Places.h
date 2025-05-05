//
// Created by vladg on 5/4/2025.
//

#ifndef PLACES_H
#define PLACES_H
#include <iostream>
#include "Prices.h"
class place : public prices {
    std::string name;
    int nr_hotels;

public:
    place(const std::string &name, int price)
        : prices(price, (price * 2) / 5), name(name), nr_hotels(0) {}

    void print(std::ostream &os) const override {
        os << "Place: " << name << ' ' << price << ' ' << sell_price << ' ' << nr_hotels;
    }

    int get_nr_hotels() const { return nr_hotels; }

    bool operator==(const place &) const {
        return true;
    }
};

#endif //PLACES_H
