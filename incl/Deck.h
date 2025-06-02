//
// Created by vladg on 6/2/2025.
//

#ifndef DECK_H
#define DECK_H
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <stdexcept> // For std::out_of_range

template <typename T>
class Deck {
private:
    std::vector<T> cards;

public:
    // Constructor
    Deck() = default;

    // Add a card to the deck
    void addCard(const T& card) {
        cards.push_back(card);
    }

    // Shuffle the deck
    void shuffle() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    }

    // Draw a card from the top of the deck
    T drawCard() {
        if (cards.empty()) {
            throw std::out_of_range("Deck is empty, no more cards to draw.");
        }
        T card = cards.back(); // Get card from the "top" (end of vector)
        cards.pop_back();     // Remove card from the deck
        return card;
    }

    // Get the number of cards in the deck
    size_t size() const {
        return cards.size();
    }

    // Check if the deck is empty
    bool isEmpty() const {
        return cards.empty();
    }

    // Display the cards in the deck (for debugging/demonstration)
    void print(std::ostream& os) const {
        os << "Deck contains " << cards.size() << " cards:\n";
        for (const auto& card : cards) {
            os << "  - " << card << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Deck<T>& deck) {
        deck.print(os);
        return os;
    }
};
#endif //DECK_H
