//
// Created by vladg on 5/5/2025.
//
#include "Chalet.h" // Include headerul propriei clase
#include "player.h" // Include headerul necesar pentru implementarea calculateRent
#include <iostream>
#include<algorithm>

chalet::chalet(const std::string &name, int price)
    : prices(price, price / 2), name(name) {}

int chalet::calculateRent(const player& owner) const {


    int owned_count = owner.countOwnedChalets(); // Apelăm metoda din player
    switch (owned_count) {
        case 1: return 25;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        default: return 0;
    }
}