//
// Created by vladg on 6/2/2025.
//
include "Place.h" // Include the corresponding header file

// Constructor definition
Place::Place(const std::string &name, const std::string &color, int price, int base_rent, int rent_hotel)
    : Prices(price, price / 2), // Initialize base class Prices with price and mortgage value (price / 2)
      name(name),
      color_group(color),
      nr_houses(0), // Initialize number of houses to 0
      base_rent(base_rent),
      rent_house1(base_rent * 2),
      rent_house2(base_rent * 5 / 2), // Note: Integer division might truncate, consider floating point if precision is needed
      rent_house3(base_rent * 3),
      rent_house4(base_rent * 7 / 2), // Note: Integer division might truncate
      rent_hotel(rent_hotel)
{}

// print method definition
void Place::print(std::ostream &os) const {
    os << "Location [" << color_group << "]: " << name << " (Price: " << get_price() << ", mortgage: " << get_sell_price() << ")";
    if (nr_houses == 0) {
        os << " - No houses";
    } else if (nr_houses > 0 && nr_houses <= 4) {
        os << " - " << nr_houses << " case"; // "case" should probably be "houses" or "case(s)" for plural
    } else if (nr_houses == 5) {
        os << " - Hotel";
    }
}

// calculateRent method definition
int Place::calculateRent(const Player& owner) const {

    bool has_color = false; // Placeholder: This logic needs to be implemented based on game rules

    if (nr_houses == 0) {
        // If the owner has all properties of this color group, rent might be doubled.
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
    return 0; // Should not be reached if nr_houses is always 0-5
}

// clone method definition for deep copying
Prices* Place::clone() const {
    return new Place(*this); // Returns a new dynamically allocated Place object, copied from *this
}

// getBuildingCost method definition
int Place::getBuildingCost() const {
    return 50; // Fixed cost for building a house/hotel
}

// addHouseHotel method definition
bool Place::addHouseHotel() {
    if (nr_houses < 5) { // Max 4 houses -> 1 hotel (5 houses means it's a hotel)
        nr_houses++;
        std::cout << "Build on " << name << ". Current level: " << (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " houses") << std::endl;
        return true;
    }
    std::cout << "Maximum number of buildings reached on " << name << std::endl;
    return false;
}

// sellHouseHotel method definition
bool Place::sellHouseHotel() {
    if (nr_houses > 0) {
        nr_houses--;
        int refund = getBuildingCost() / 2; // Refund half the building cost
        std::cout << "Sold house/hotel on " << name << ". Level: "
                  << (nr_houses == 0 ? "No houses" : (nr_houses == 5 ? "Hotel" : std::to_string(nr_houses) + " houses"))
                  << ". Refund money: " << refund << std::endl;
        return true;
    }
    std::cout << "No houses to sell on " << name << std::endl;
    return false;
}

// getNrHouses getter definition
int Place::getNrHouses() const {
    return nr_houses;
}

// getColorGroup getter definition
const std::string& Place::getColorGroup() const {
    return color_group;
}

// operator== overload definition
bool Place::operator==(const Place &other) const {
    return name == other.name && color_group == other.color_group;
}