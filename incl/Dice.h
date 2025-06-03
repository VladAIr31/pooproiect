//
// Created by vladg on 6/2/2025.
//

#ifndef DICE_H
#define DICE_H
#include "Observer.h" // For Subject
#include <random>
#include <string>
#include <vector> 

class Dice : public Subject {
private:
    std::mt19937 rng; // Mersenne Twister random number generator
    std::uniform_int_distribution<int> dist;

public:
    Dice() : dist(1, 6) {
        // Seed the random number generator
        std::random_device rd;
        rng.seed(rd());
    }

    // Roll the dice and notify observers
    std::pair<int, int> roll() {
        int roll1 = dist(rng);
        int roll2 = dist(rng);
        std::string message = "Dice rolled: " + std::to_string(roll1) + " and " + std::to_string(roll2) +
                              ". Total: " + std::to_string(roll1 + roll2);
        notify(message); // Notify all attached observers
        return {roll1, roll2};
    }
};

#endif //DICE_H
