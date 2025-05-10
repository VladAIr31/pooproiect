//
// Created by vladg on 5/4/2025.
//

#ifndef PLACES_H
#define PLACES_H
#include <iostream>
#include <string>
#include "Prices.h"
#include "Player.h"

class Place : public Prices {
    std::string name;
    std::string color_group;
    int nr_houses;
    int base_rent;
    int rent_house1, rent_house2, rent_house3, rent_house4;
    int rent_hotel;


public:

    Place(const std::string &name, const std::string &color, int price, int base_rent, int rent_hotel)
        : prices(price, price / 2), // Prețul de vânzare/ipotecă = jumătate din preț
          name(name),
          color_group(color),
          nr_houses(0),
          rent_house1(base_rent*2),
          rent_house2(base_rent*5/2),
          rent_house3(base_rent*3),
          rent_house4(base_rent*7/2),
          base_rent(base_rent),
          rent_hotel(rent_hotel)
          {}

    void print(std::ostream &os) const override {
        os << "Location [" << color_group << "]: " << name << " (Price: " << get_price() << ", mortgage: " <<get_sell_price() << ")";
        if (nr_houses == 0) {
             os << " - No houses";
        } else if (nr_houses > 0 && nr_houses <= 4) {
            os << " - " << nr_houses << " case";
        } else if (nr_houses == 5) {
            os << " - Hotel";
        }
    }

    int calculateRent(const Player& owner) const override {

        bool has_color = false;
        ///tod
        if (nr_houses == 0) {

             return has_color ? base_rent * 2 : base_rent;
        } else if (nr_houses == 1) {
            return rent_house1;
        } else if (nr_houses == 2) {
            return rent_house2;
        } else if (nr_houses == 3) {
            return rent_house3;
        } else if (nr_houses == 4) {
            return rent_house4;
        } else if (nr_houses == 5) {
            return rent_hotel;
        }
        return 0;
    }


    Prices* clone() const override {
        return new Place(*this);
    }

    int getBuildingCost() const {

        return 50;
    }

    bool addHouseHotel() {
        if (nr_houses < 5) { // Max 4 houses -> 1 hotel
            nr_houses++;
            std::cout << "Build on " << name << ". curent level: " << (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " houses") << std::endl;
            return true;
        }
        std::cout << "Maxim " << name << std::endl;
        return false;
    }
     bool sellHouseHotel() {
         if (nr_houses > 0) {
             nr_houses--;
             int refund = getBuildingCost() / 2;
             std::cout << "Sell house/hotel " << name << "lv: "
                       << (nr_houses == 0 ? "No houses" : (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " houses"))
                       << "refund money: " << refund << std::endl;

             return true;
         }
         std::cout << "No house to sell" << name << std::endl;
         return false;
     }

    int getNrHouses() const { return nr_houses; }
    const std::string& getColorGroup() const { return color_group; }

    bool operator==(const Place &other) const {
        return name == other.name && color_group == other.color_group;
    }
};

#endif //PLACES_H
