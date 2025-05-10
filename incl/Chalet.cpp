//
// Created by vladg on 5/5/2025.
//
#include "Chalet.h"
#include "Player.h"
#include <iostream>
#include<algorithm>

Chalet::Chalet(const std::string &name, int price)
    : Prices(price, price / 2), name(name) {}

int Chalet::calculateRent(const Player& owner) const {


    int owned_count = owner.countOwnedChalets();
    switch (owned_count) {
        case 1: return 25;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        default: return 0;
    }
}