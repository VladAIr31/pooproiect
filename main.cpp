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
    card(const std::string &type,  const std::string &use) :
    type(type), use(use) {}
    friend std::ostream &operator<<(std::ostream &os, const card &c) {
        os << c.type<<' '<<c.use;
        return os;
    }
    bool operator==(const card &) const {
        return true;
    }
    std::string get_type() const&  { return type; }
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
    int nr_hotels;
public:
    place( const std::string &name, int price):
    name(name),
    price(price), sell_price((price*2)/5),
    nr_hotels()
    {}
    friend std::ostream &operator<<(std::ostream &os, const place &p) {
        os<<p.name<<' '<<p.price<<' '<<p.sell_price<<' '<<p.nr_hotels;
        return os;
    }
    int get_price()  const{ return price; }
    int get_sell_price()  const{ return sell_price; }
    bool operator==(const place &) const {
        return true;
    }

};

class player {
    std::string name;
    pawn p;
    int buget;
    std::vector<card> cards;
    std::vector<place> ownership;
public:
    player(const std::string& name, const pawn& p, int buget)
       : name(name), p(p), buget(buget), cards(), ownership() {}
    friend std::ostream &operator<<(std::ostream &os, const player &p) {
        os<<p.name<<' '<<p.buget<<' '<<p.p;
        for (auto const  &card : p.cards) {
            os<<' '<<card;
        }
            for (auto const  &own : p.ownership) {
                os<<' '<<own;
            }




        return os;
    }
    void add_card(const card& c) {
        if (c.get_type()!="Now")
        cards.push_back(c);
    }
    void add_place (const  place& p) {
        int price=p.get_price();
        if (buget>=price)
            ownership.push_back(p), buget=buget-price;
        else std::cout << "You are broke" << std::endl;


    }
    void usecard ( const card & c) {
        cards.erase(find(cards.begin(), cards.end(), c));
    }
    void sell_place (const place& p) {
        int price=p.get_sell_price();
        buget+=price;
        ownership.erase(find(ownership.begin(), ownership.end(), p));

    }
};



int main() {
    pawn A("green",{1,2});
    player one("Marcel",A,5000);
    chalet sus("Susai",500);
    card Power("Special","Now");
    place Su("Suceava",3000);
    std::cout<<A<<'\n'<<one<<'\n'<<sus<<'\n'<<Power<<'\n'<<Su<<'\n';
    one.add_card(Power);
    one.add_place(Su);
    std::cout<<one<<'\n';
    one.usecard(Power);
    std::cout<<one<<'\n';
    one.sell_place(Su);
    std::cout<<one<<'\n';





    return 0;
}
