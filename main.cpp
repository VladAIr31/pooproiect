#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>





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
class card {
    std::string type;
    std::string use;
public:
    card(std::string type, std::string use) :
    type(type), use(use) {}
    friend std::ostream &operator<<(std::ostream &os, const card &c) {
        os << c.type<<' '<<c.use;
        return os;
    }
};


class hotel {
    int price=500;
    int sell_price=200;
public:
    friend std::ostream &operator<<(std::ostream &os, const hotel &h) {
        os << h.price<<' '<<h.sell_price;
        return os;
    }
};

class chalet {
    std::string name;
    int price;
    int sell_price;


public:
    chalet(const std::string &name, int price)
        : name(name), price(price), sell_price(price*3/10) {}
    friend std::ostream &operator<<(std::ostream &os, const chalet &c) {
        os<<c.name<<' '<<c.price<<' '<<c.sell_price;
        return os;
    }

};
class place {
    std::string name;
    int price;
    int sell_price;
    std::vector<hotel> hotels;
public:
    place( const std::string name, int price):
    name(name),
    price(price), sell_price((price*2)/5),
    hotels()
    {}
    friend std::ostream &operator<<(std::ostream &os, const place &p) {
        os<<p.name<<' '<<p.price<<' '<<p.sell_price<<' ';
        for (auto &h : p.hotels) {
            os<<h<<' ';
        }
        return os;
    }



};

class player {
    std::string name;
    pawn p;
    int buget;
    std::vector<card> cards;
public:
    player(const std::string& name, const pawn& p, int buget)
       : name(name), p(p), buget(buget), cards() {}
    friend std::ostream &operator<<(std::ostream &os, const player &p) {
        os<<p.name<<' '<<p.buget<<' '<<p.p;
        for (auto &card : p.cards) {
            os<<' '<<card;
        }
        return os;
    }
};



int main() {
    pawn A("green",{1,2});
    player one("Marcel",A,5000);
    chalet sus("Susai",500);
    card Power("Special","Now");
    std::cout<<A<<' '<<one<<' '<<sus<<' '<<Power;










    return 0;
}
