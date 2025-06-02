//
// Created by vladg on 6/2/2025.
//

#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H
#include <memory>
#include <string>
#include <stdexcept> // For std::invalid_argument

#include "Prices.h"
#include "Places.h"
#include "Chalet.h"
#include "Motel.h"
#include "Hotel.h"

enum class PropertyType {
    PLACE,
    CHALET,
    MOTEL,

};

class PropertyFactory {
public:
    static std::unique_ptr<Prices> createProperty(
        PropertyType type,
        const std::string& name,
        int price,
        const std::string& color_group = "", // Specific to Place
        int base_rent = 0,                  // Specific to Place
        int rent_hotel = 0                  // Specific to Place
    );

    static std::unique_ptr<Places> createPlace(const std::string& name, const std::string& color, int price, int base_rent, int rent_hotel);
    static std::unique_ptr<Chalet> createChalet(const std::string& name, int price);
    static std::unique_ptr<Motel> createMotel(const std::string& name, int price);
};

#endif //PROPERTYFACTORY_H
