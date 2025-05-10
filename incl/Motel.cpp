//
// Created by vladg on 5/5/2025.
//
#include "motel.h" // Include headerul propriei clase
#include "player.h" // Include headerul necesar pentru implementarea calculateRent
#include <iostream>
#include<algorithm>

Motel::Motel(const std::string &name, int price)
    : Prices(price, price / 2), name(name) {}

int motel::calculateRent(const Player& owner) const {


    int owned_count = owner.countOwnnedMotels();
    switch (owned_count) {
        case 1: return 100;
        case 2: return 200;
        case 3: return 500;
        default: return 0;
    }
}
