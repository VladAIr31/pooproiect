//
// Created by vladg on 6/2/2025.
//

#ifndef MYFIND_H
#define MYFIND_H
#include <vector>
#include <algorithm> // For std::find_if
#include <optional>  // For std::optional

template<typename T, typename Predicate>
std::optional<T> findInCollection(const std::vector<T> &collection, Predicate pred) {
    auto it = std::find_if(collection.begin(), collection.end(), pred);
    if (it != collection.end()) {
        return *it; // Return the found element
    }
    return std::nullopt; // Return an empty optional if not found
}

#endif //MYFIND_H
