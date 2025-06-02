//
// Created by vladg on 6/2/2025.
//
#include "PropertyFactory.h"

std::unique_ptr<Prices> PropertyFactory::createProperty(
    PropertyType type,
    const std::string& name,
    int price,
    const std::string& color_group,
    int base_rent,
    int rent_hotel) {

    switch (type) {
        case PropertyType::PLACE:
            if (color_group.empty() || base_rent <= 0) { // rent_hotel can be 0 initially
                throw std::invalid_argument("Missing parameters for Place creation.");
            }
        return std::make_unique<Places>(name, color_group, price, base_rent, rent_hotel);
        case PropertyType::CHALET:
            return std::make_unique<Chalet>(name, price);
        case PropertyType::MOTEL:
            return std::make_unique<Motel>(name, price);

        default:
            throw std::invalid_argument("Unknown property type requested.");
    }
}

std::unique_ptr<Places> PropertyFactory::createPlace(const std::string& name, const std::string& color, int price, int base_rent, int rent_hotel) {
    return std::make_unique<Places>(name, color, price, base_rent, rent_hotel);
}

std::unique_ptr<Chalet> PropertyFactory::createChalet(const std::string& name, int price) {
    return std::make_unique<Chalet>(name, price);
}

std::unique_ptr<Motel> PropertyFactory::createMotel(const std::string& name, int price) {
    return std::make_unique<Motel>(name, price);
}


