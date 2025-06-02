#include "Player.h"

#include <iostream>
#include <algorithm>
#include <memory>

#include "Exception.h"
#include "Chalet.h"
#include "Motel.h"

int Player::activePlayers = 0;

Player::Player(const std::string& name, const Pawn& p, int buget)
    : name(name), p(p), buget(buget), cards() {

    activePlayers++;
    std::cout << "Player " << name << " created:\n" << p << std::endl;
}

Player::Player(const Player& other)
    : name(other.name), p(other.p), buget(other.buget), cards(other.cards) {
    ownership.reserve(other.ownership.size());
    for (const auto& prop_ptr : other.ownership) {
        if (prop_ptr) {
            ownership.push_back(std::unique_ptr<Prices>(prop_ptr->clone()));
        } else {
             ownership.push_back(nullptr);
        }
    }
    activePlayers++;
}
Player::~Player() {
    activePlayers--;
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {

        name = other.name;
        p = other.p;
        buget = other.buget;
        cards = other.cards;


        ownership.clear();
        ownership.reserve(other.ownership.size());
        for (const auto& prop_ptr : other.ownership) {
            if (prop_ptr) {
                ownership.push_back(std::unique_ptr<Prices>(prop_ptr->clone()));
            } else {
                ownership.push_back(nullptr);
            }
        }
    }
    return *this;
}


void Player::add_property(std::unique_ptr<Prices> prop) {
    if (!prop) return;

    int cost = prop->get_price();

    if (buget >= cost) {
        buget -= cost;
        std::cout << name << " Buy " << *prop << " for " << cost << std::endl;
        ownership.push_back(std::move(prop));
    } else {
        std::cout << name << ": Insuficent buget (" << buget << ") to buy "
                  << *prop << " (cost: " << cost << ")" << std::endl;

    }

}

std::unique_ptr<Prices> Player::sell_property(int index) {
    if (index < 0 || index >= static_cast<int>(ownership.size()) || !ownership[index]) {
        std::cerr << " Invalid index  (" << index << ") or no proprety for sale" << std::endl;
        return nullptr;
    }

    int sell_value = ownership[index]->get_sell_price();
    buget += sell_value;

    std::unique_ptr<Prices> sold_prop = std::move(ownership[index]);

    ownership.erase(ownership.begin() + index);

    std::cout << name << " Sold: " << *sold_prop << " for " << sell_value << std::endl;
    return sold_prop;
}

int Player::countOwnedChalets() const {
    return std::count_if(ownership.begin(), ownership.end(),
        [](const std::unique_ptr<Prices>& p) {

            return p && dynamic_cast<Chalet*>(p.get()) != nullptr;
        });
}
int Player::countOwnedMotels() const {
    return std::count_if(ownership.begin(), ownership.end(),
        [](const std::unique_ptr<Prices>& p) {
            return p && dynamic_cast<Motel*>(p.get()) != nullptr;
        });
}



void Player::add_card(const Card& c) {
    if (c.get_type() != "Now") {
        cards.push_back(c);
    } else {
    }
}

const std::string& Player::getName() const {
    return name;
}

int Player::getBuget() const {
    return buget;
}

const Pawn& Player::getPawn() const {
    return p;
}

const std::vector<std::unique_ptr<Prices>>& Player::getOwnership() const {
    return ownership;
}

int Player::getActivePlayers() {
    return activePlayers;
}

bool Player::isPlayerNameValid(const std::string& name) {
    return !name.empty() && name.length() < 25;
}

void Player::pay(int amount) {
    if (buget < amount) {

        throw InsufficientFundsError(name, amount, buget);
    }
    buget -= amount;
}

void Player::receive(int amount) {
     if (amount > 0) {
        buget += amount;
        std::cout << name << " Receive " << amount << ". New budget: " << buget << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Player& pa) {
    os << "Player: " << pa.name << ", Buget: " << pa.buget << ", Pawn: " << pa.p << "\n";
    os << "  Cards:\n";
    if (pa.cards.empty()) {
        os << "    None\n";
    } else {
        for (const auto& card : pa.cards) {
            os << "    - " << card << "\n";
        }
    }
    os << "  Properties:\n";
    if (pa.ownership.empty()) {
        os << "    None\n";
    } else {
        int i = 0;
        for (const auto& prop_ptr : pa.ownership) {
            os << "    " << i++ << ": ";
            if (prop_ptr) {
                os << *prop_ptr << "\n";
            } else {
                os << "(Empty slot)\n";
            }
        }
    }
    return os;
}