#include "player.h"

#include <iostream>
#include <algorithm>
#include <memory>

#include "exception.h"
#include "Chalet.h"
#include "motel.h"

int player::activePlayers = 0;

player::player(const std::string& name, const pawn& p, int buget)
    : name(name), p(p), buget(buget), cards() {

    activePlayers++;
    std::cout << "Player " << name << " created:\n" << p << std::endl;
}

player::player(const player& other)
    : name(other.name), p(other.p), buget(other.buget), cards(other.cards) {
    ownership.reserve(other.ownership.size());
    for (const auto& prop_ptr : other.ownership) {
        if (prop_ptr) {
            ownership.push_back(std::unique_ptr<prices>(prop_ptr->clone()));
        } else {
             ownership.push_back(nullptr);
        }
    }
    activePlayers++;
}
player::~player() {
    activePlayers--;
}

player& player::operator=(const player& other) {
    if (this != &other) {

        name = other.name;
        p = other.p;
        buget = other.buget;
        cards = other.cards;


        ownership.clear();
        ownership.reserve(other.ownership.size());
        for (const auto& prop_ptr : other.ownership) {
            if (prop_ptr) {
                ownership.push_back(std::unique_ptr<prices>(prop_ptr->clone()));
            } else {
                ownership.push_back(nullptr);
            }
        }
    }
    return *this;
}


void player::add_property(std::unique_ptr<prices> prop) {
    if (!prop) return;

    int cost = prop->get_price();

    if (buget >= cost) {
        buget -= cost;
        std::cout << name << " cumpara " << *prop << " pentru " << cost << std::endl;
        ownership.push_back(std::move(prop)); // Transferăm ownership-ul în vector
    } else {
        std::cout << name << ": Buget insuficient (" << buget << ") pentru a cumpara "
                  << *prop << " (cost: " << cost << ")" << std::endl;

    }

}

std::unique_ptr<prices> player::sell_property(int index) {
    if (index < 0 || index >= static_cast<int>(ownership.size()) || !ownership[index]) {
        std::cerr << "Index invalid (" << index << ") sau proprietate inexistenta pentru vanzare." << std::endl;
        return nullptr;
    }

    int sell_value = ownership[index]->get_sell_price();
    buget += sell_value;

    // Extrage unique_ptr din vector folosind std::move
    std::unique_ptr<prices> sold_prop = std::move(ownership[index]);

    // Elimină elementul (acum nullptr) din vector
    ownership.erase(ownership.begin() + index);

    std::cout << name << " a vandut: " << *sold_prop << " pentru " << sell_value << std::endl;
    return sold_prop; // Returnează proprietatea vândută (ownership transferat)
}

// Definiția metodei countOwnedChalets
int player::countOwnedChalets() const {
    return std::count_if(ownership.begin(), ownership.end(),
        [](const std::unique_ptr<prices>& p) {
            // Verificăm dacă pointerul nu e null și dacă obiectul este de tip chalet
            // dynamic_cast returnează nullptr dacă conversia eșuează
            return p && dynamic_cast<chalet*>(p.get()) != nullptr;
        });
}
int player::countOwnnedMotels() const {
    return std::count_if(ownership.begin(), ownership.end(),
        [](const std::unique_ptr<prices>& p) {
            return p && dynamic_cast<motel*>(p.get()) != nullptr;
        });
}



void player::add_card(const card& c) {
    if (c.get_type() != "Now") {
        cards.push_back(c);
    } else {
    }
}

const std::string& player::getName() const {
    return name;
}

int player::getBuget() const {
    return buget;
}

const pawn& player::getPawn() const {
    return p;
}

const std::vector<std::unique_ptr<prices>>& player::getOwnership() const {
    return ownership;
}

int player::getActivePlayers() {
    return activePlayers;
}

bool player::isPlayerNameValid(const std::string& name) {
    return !name.empty() && name.length() < 25;
}

void player::pay(int amount) {
    if (buget < amount) {

        throw FonduriInsuficienteError(name, amount, buget);
    }
    buget -= amount;
}

void player::receive(int amount) {
     if (amount > 0) {
        buget += amount;
        std::cout << name << " primeste " << amount << ". Buget nou: " << buget << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const player& pa) {
    os << "Player: " << pa.name << ", Buget: " << pa.buget << ", Pion: " << pa.p << "\n";
    os << "  Carti:\n";
    if (pa.cards.empty()) {
        os << "    Niciuna\n";
    } else {
        for (const auto& card : pa.cards) {
            os << "    - " << card << "\n";
        }
    }
    os << "  Proprietati:\n";
    if (pa.ownership.empty()) {
        os << "    Niciuna\n";
    } else {
        int i = 0;
        for (const auto& prop_ptr : pa.ownership) {
            os << "    " << i++ << ": ";
            if (prop_ptr) {
                os << *prop_ptr << "\n";
            } else {
                os << "(Slot Gol)\n";
            }
        }
    }
    return os;
}