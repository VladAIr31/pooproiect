//
// Created by vladg on 5/4/2025.
//

#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>
#include "Prices.h"

class Hotel : public Prices {

public:
    Hotel() : Prices(500, 200) {}

    void print(std::ostream &os) const override {
        os << "Hotel: " << get_price() << ' ' << get_sell_price();
    }
};

#endif //HOTEL_H
