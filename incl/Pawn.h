//
// Created by vladg on 5/4/2025.
//

#ifndef PAWN_H
#define PAWN_H
#include <iostream>
class  Pawn {
    std::string color;
    std::pair<int, int> position;
public:
    Pawn(std::string color, std::pair<int, int> position) :
    color(color), position(position) {}

    Pawn(const Pawn &p): color(p.color), position(p.position) {}

    Pawn& operator=(const Pawn &p) {
        color = p.color;
        position = p.position;
        return *this;
    }
    ~Pawn() {}
    friend std::ostream &operator<<(std::ostream &os, const Pawn &p) {
        os << p.color<<' '<<p.position.first<<' '<<p.position.second;
        return os;
    }
};

#endif //PAWN_H
