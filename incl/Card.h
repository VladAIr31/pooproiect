//
// Created by vladg on 5/4/2025.
//

#ifndef CARD_H
#define CARD_H
#include <iostream>
class card {
    std::string type;
    std::string use;
public:
    card(const std::string &type,  const std::string &use) :
    type(type), use(use) {}
    friend std::ostream &operator<<(std::ostream &os, const card &c) {
        os << c.type<<' '<<c.use;
        return os;
    }
    bool operator==(const card &) const {
        return true;
    }
    const std::string& get_type() const  { return type; }
};

#endif //CARD_H
