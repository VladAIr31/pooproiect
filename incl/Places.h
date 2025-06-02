/ Place.h
#ifndef PLACES_H
#define PLACES_H

#include <iostream>
#include <string>
#include "Prices.h"
#include "Player.h"



class Place : public Prices {
private:
    std::string name;
    std::string color_group;
    int nr_houses;
    int base_rent;
    int rent_house1, rent_house2, rent_house3, rent_house4;
    int rent_hotel;

public:
    // Constructor declaration
    Place(const std::string &name, const std::string &color, int price, int base_rent, int rent_hotel);

    // Override methods from Prices
    void print(std::ostream &os) const override;
    int calculateRent(const Player& owner) const override;
    Prices* clone() const override;

    // Specific methods for Place
    int getBuildingCost() const;
    bool addHouseHotel();
    bool sellHouseHotel();

    // Getters
    int getNrHouses() const;
    const std::string& getColorGroup() const;

    // Operator overload
    bool operator==(const Place &other) const;
};

#endif // PLACES_H