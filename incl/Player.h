//
// Created by vladg on 5/4/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Observer.h"
#include "Card.h"
#include "Pawn.h"
#include "Prices.h"


class Player : public Observer  {
private:
    std::string name;
    Pawn p;
    int buget;
    std::vector<Card> cards;
    // Folosim unique_ptr pentru a gestiona proprietățile polimorfice
    std::vector<std::unique_ptr<Prices>> ownership;
    static int activePlayers;

public:
    // Constructor
    Player(const std::string& name, const Pawn& p, int buget);


    Player(const Player& other);

    Player& operator=(const Player& other);

    // Destructor
    ~Player() ;

    // Metode pentru gestionarea proprietăților
    void add_property(std::unique_ptr<Prices> prop);
    std::unique_ptr<Prices> sell_property(int index);

    int countOwnedChalets() const;
    int countOwnedMotels() const;


    // Metode pentru carduri
    void add_card(const Card& c);



    const std::string& getName() const;
    int getBuget() const;
    const Pawn& getPawn() const; // Getter adăugat pentru pion
    const std::vector<std::unique_ptr<Prices>>& getOwnership() const; // Getter pentru proprietăți

    // Metode pentru modificarea bugetului
    void pay(int amount);
    void receive(int amount);

    static int getActivePlayers();
    static  bool isPlayerNameValid(const std::string& name);
    void update(const std::string& eventMessage) override {
        std::cout << "Player " << name << " received event: " << eventMessage << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& pa);
};

std::ostream& operator<<(std::ostream& os, const Player& pa);
#endif //PLAYER_H
