//
// Created by vladg on 5/4/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>


#include "Card.h"
#include "Pawn.h"
#include "Prices.h"


class player {
private:
    std::string name;
    pawn p;
    int buget;
    std::vector<card> cards;
    // Folosim unique_ptr pentru a gestiona proprietățile polimorfice
    std::vector<std::unique_ptr<prices>> ownership;
    static int activePlayers;

public:
    // Constructor
    player(const std::string& name, const pawn& p, int buget);


    player(const player& other);

    player& operator=(const player& other);

    // Destructor
    ~player() ;

    // Metode pentru gestionarea proprietăților
    void add_property(std::unique_ptr<prices> prop);
    std::unique_ptr<prices> sell_property(int index);

    int countOwnedChalets() const;
    int countOwnnedMotels() const;


    // Metode pentru carduri
    void add_card(const card& c);



    const std::string& getName() const;
    int getBuget() const;
    const pawn& getPawn() const; // Getter adăugat pentru pion
    const std::vector<std::unique_ptr<prices>>& getOwnership() const; // Getter pentru proprietăți

    // Metode pentru modificarea bugetului
    void pay(int amount);
    void receive(int amount);

    static int getActivePlayers();
    static  bool isPlayerNameValid(const std::string& name);

    friend std::ostream& operator<<(std::ostream& os, const player& pa);
};

std::ostream& operator<<(std::ostream& os, const player& pa);
#endif //PLAYER_H
