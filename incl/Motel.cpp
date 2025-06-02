
// Created by vladg on 5/5/2025.
//
#include "Motel.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

Motel::Motel(const std::string &name, int price)
    : Prices(price, price / 2), name(name) {}

int Motel::calculateRent(const Player& owner) const {
    int owned_count = owner.countOwnedMotels();
    switch (owned_count) {
        case 1: return 100;
        case 2: return 200;
        case 3: return 500;
        default: return 0;
    }
}