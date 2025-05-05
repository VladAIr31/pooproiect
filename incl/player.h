//
// Created by vladg on 5/4/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Card.h"
#include "Pawn.h"
#include "Places.h"
class player {
    std::string name;
    pawn p;
    int buget;
    std::vector<card> cards;
    std::vector<place> ownership;
public:
    player(const std::string& name, const pawn& p, int buget)
       : name(name), p(p), buget(buget), cards(), ownership() {}
    friend std::ostream &operator<<(std::ostream &os, const player &pa) {
        os<<pa.name<<' '<<pa.buget<<' '<<pa.p;
        for (auto const  &card : pa.cards) {
            os<<' '<<card;
        }
        for (auto const  &own : pa.ownership) {
            os<<' '<<own;
        }




        return os;
    }
    void add_card(const card& c) {
        if (c.get_type()!="Now")
            cards.push_back(c);
    }
    void add_place (const  place& pl) {
        int price=pl.get_price();
        if (buget>=price)
            ownership.push_back(pl), buget=buget-price;
        else std::cout << "You are broke" << std::endl;


    }
    void usecard ( const card & c) {
        cards.erase(find(cards.begin(), cards.end(), c));
    }
    void sell_place (const place& pl) {
        int price=pl.get_sell_price();
        buget+=price;
        ownership.erase(find(ownership.begin(), ownership.end(), pl));

    }
};

#endif //PLAYER_H
