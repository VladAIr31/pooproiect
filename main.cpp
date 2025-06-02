#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "incl/Player.h"
#include "incl/Chalet.h"
#include "incl/Board.h"
#include "incl/Boardconf.h"
#include "incl/Prices.h"
#include "incl/Exception.h"
#include "incl/PropertyFactory.h"

int main() {
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Monopoly Style Board - Single CPP");
window.setFramerateLimit(60);

GameBoard gameBoard;

try {
    Pawn p1_pawn("Red", {0, 0});
    Player p1("Alice", p1_pawn, 500);
    // Initial player:
    std::cout << "Initial player:\n" << p1 << std::endl;

    auto chalet_ptr = std::make_unique<Chalet>("Mountain Cabin", 200);
    p1.add_property(std::move(chalet_ptr)); // Alice buys the cabin
    // After purchase:
    std::cout << "After purchase:\n" << p1 << std::endl;


    int payment1 = 100;
    // Alice tries to pay 100...
    std::cout << "Alice tries to pay " << payment1 << "..." << std::endl;
    p1.pay(payment1);
    // Payment successful. Remaining budget:
    std::cout << "Payment successful. Remaining budget: " << p1.getBuget() << std::endl;

    int payment2 = 1000;
    // Alice tries to pay 1000...
    std::cout << "\nAlice tries to pay " << payment2 << "..." << std::endl;
    p1.pay(payment2);

    // This line should not appear if payment 2 fails.
    std::cout << "This line should not appear if payment 2 fails." << std::endl;

} catch (const InsufficientFundsError& e) {
    // !!! Payment Error !!!
    std::cerr << "\n!!! Payment Error !!!\n";
    // Details:
    std::cerr << "Details: " << e.what() << std::endl;


}

// Continuing execution after the try/catch block...
std::cout << "\nContinuing execution after the try/catch block...\n" << std::endl;




std::string potentialName = "Player1_Valid";
if (Player::isPlayerNameValid(potentialName)) {
    // 'Player1_Valid' is a valid name.
    std::cout << "'" << potentialName << "' is a valid name.\n";
    Pawn p1_pawn("Blue", {0,0});
    Player p1(potentialName, p1_pawn, 1500);

    Pawn p2_pawn("Green", {0,0});
    Player p2("Player2", p2_pawn, 1500);

    // Current number of active players:
    std::cout << "Current number of active players: " << Player::getActivePlayers() << std::endl;

    {
        Pawn p3_pawn("Yellow", {0,0});
        Player p3 = p1;
        // Current number of active players (after copy):
        std::cout << "Current number of active players (after copy): " << Player::getActivePlayers() << std::endl;
    }

    // Current number of active players (after exiting block):
    std::cout << "Current number of active players (after exiting block): " << Player::getActivePlayers() << std::endl;

} else {
    // 'Player1_Valid' is NOT a valid name.
    std::cout << "'" << potentialName << "' is NOT a valid name.\n";
}


// Number of active players at the end of main (before return)
std::cout << "Number of active players at the end of main (before return): " << Player::getActivePlayers() << std::endl;

    //PropertyFactory Demonstration
    std::cout << "--- PropertyFactory Demonstration ---" << std::endl;
    Pawn p1_pawn("Red", {0, 0});
    Player p1("Vlad", p1_pawn, 2000);

    try {
        auto chalet1 = PropertyFactory::createChalet("Paltinis Chalet", 220);
        p1.add_property(std::move(chalet1));

        auto motel1 = PropertyFactory::createMotel("Crossroads Motel", 180);
        p1.add_property(std::move(motel1));

        auto bucharestPlace = PropertyFactory::createPlace("Bucharest - Calea Victoriei", "DarkBlue", 400, 50, 2000);
        p1.add_property(std::move(bucharestPlace));





    } catch (const std::exception& e) {
        std::cerr << "Error during property creation or adding: " << e.what() << '\n';
    }




while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }


    window.clear(sf::Color(200, 200, 200));
    gameBoard.draw(window); // Use the draw method defined above

    window.display();
}

return 0;
}
