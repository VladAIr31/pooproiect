//
// Created by vladg on 5/4/2025.
//

#ifndef PLACES_H
#define PLACES_H
#include <iostream>
#include <string> // Adăugat pentru std::string
#include "Prices.h"
#include "player.h" // Necesar pentru parametrul owner

class place : public prices {
    std::string name;
    std::string color_group; // Adăugăm grupul de culoare!
    int nr_houses;
    int base_rent;
    int rent_house1, rent_house2, rent_house3, rent_house4;
    int rent_hotel;


public:

    place(const std::string &name, const std::string &color, int price, int base_rent, int rent_hotel)
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
        os << "Locatie [" << color_group << "]: " << name << " (Pret: " << get_price() << ", Ipoteca: " <<get_sell_price() << ")";
        if (nr_houses == 0) {
             os << " - Neamenajat";
        } else if (nr_houses > 0 && nr_houses <= 4) {
            os << " - " << nr_houses << " case";
        } else if (nr_houses == 5) { // Starea 5 reprezintă hotelul
            os << " - Hotel";
        }
    }

    // Implementare calcul chirie
    int calculateRent(const player& owner) const override {

        bool has_color = false;
        ///tod
        if (nr_houses == 0) {
            // Chiria de bază, dublată dacă are monopol și nu sunt case
             return has_color ? base_rent * 2 : base_rent;
        } else if (nr_houses == 1) {
            return rent_house1;
        } else if (nr_houses == 2) {
            return rent_house2;
        } else if (nr_houses == 3) {
            return rent_house3;
        } else if (nr_houses == 4) {
            return rent_house4;
        } else if (nr_houses == 5) { // Starea 5 = hotel
            return rent_hotel;
        }
        return 0; // Ceva nu e ok dacă ajunge aici
    }


    prices* clone() const override {
        return new place(*this);
    }

    // Costul pentru a construi următoarea casă/hotel
    int getBuildingCost() const {

        return 50;
    }

    bool addHouseHotel() {
        if (nr_houses < 5) { // Max 4 case -> 1 hotel
            nr_houses++;
            std::cout << "Construit pe " << name << ". Nivel curent: " << (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " case") << std::endl;
            return true;
        }
        std::cout << "Dezvoltare maxima atinsa pentru " << name << std::endl;
        return false;
    }
     // Metoda pentru a vinde case/hotel
     bool sellHouseHotel() {
         if (nr_houses > 0) {
             nr_houses--;
             // primești înapoi jumătate din costul de construcție
             int refund = getBuildingCost() / 2;
             std::cout << "Vandut imbunatatire pe " << name << ". Nivel curent: "
                       << (nr_houses == 0 ? "Neamenajat" : (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " case"))
                       << ". Primit: " << refund << std::endl;
             //de adaugat refund la banii propritarului
             return true;
         }
         std::cout << "Nicio imbunatatire de vandut pe " << name << std::endl;
         return false;
     }

    int getNrHouses() const { return nr_houses; }
    const std::string& getColorGroup() const { return color_group; }

    bool operator==(const place &other) const {
        return name == other.name && color_group == other.color_group;
    }
};

#endif //PLACES_H
