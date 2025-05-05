//
// Created by vladg on 5/4/2025.
//

#ifndef PAWN_H
#define PAWN_H
#include <iostream>
class  pawn {
    std::string color;
    std::pair<int, int> position;
public:
    pawn(std::string color, std::pair<int, int> position) :
    color(color), position(position) {}

    pawn(const pawn &p): color(p.color), position(p.position) {}

    pawn& operator=(const pawn &p) {
        color = p.color;
        position = p.position;
        return *this;
    }
    ~pawn() {}
    friend std::ostream &operator<<(std::ostream &os, const pawn &p) {
        os << p.color<<' '<<p.position.first<<' '<<p.position.second;
        return os;
    }
};

#endif //PAWN_H
