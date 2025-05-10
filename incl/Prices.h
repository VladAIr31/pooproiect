//
// Created by vladg on 5/4/2025.
//

#ifndef PRICES_H
#define PRICES_H
#include <iostream>
#include <vector>

//#include "player.h"
class Player;

class Prices {

    int price;
    int sell_price;

public:
    Prices(int p, int sp) : price(p), sell_price(sp) {}

    virtual int get_price() const { return price; }
    virtual int get_sell_price() const { return sell_price; }

    virtual void print(std::ostream &os) const = 0;
    virtual Prices* clone() const = 0;
    virtual int calculateRent(const Player & owner) const = 0;

    virtual ~Prices() = default;

    friend std::ostream &operator<<(std::ostream &os, const Prices &p) {
        p.print(os);
        return os;
    }
};

#endif //PRICES_H
