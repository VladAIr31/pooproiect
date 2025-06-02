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
#include "incl/Deck.h"            // Include the Deck template class
#include "incl/Myfind.h"           // Include the template function
#include "incl/Observer.h"        // For Observer/Subject
#include "incl/Dice.h"

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

    // --- Observer Pattern Demonstration ---
    Player p2("Bob", Pawn("Blue", {0, 0}), 1500);
    std::cout << "\n--- Observer Pattern Demonstration ---" << std::endl;
    Dice gameDice;
    gameDice.attach(&p1); // Vlad observes the dice
    gameDice.attach(&p2); // Bob observes the dice

    std::cout << "\nRolling dice..." << std::endl;
    gameDice.roll();

    std::cout << "\nBob stops observing." << std::endl;
    gameDice.detach(&p2);

    std::cout << "\nRolling dice again..." << std::endl;
    gameDice.roll();


    // --- Deck Template Class Demonstration ---
    std::cout << "\n--- Deck Template Class Demonstration ---" << std::endl;
    // Instantiation 1: Deck of Cards
    Deck<Card> chanceDeck;
    chanceDeck.addCard(Card("Chance", "Advance to Go (Collect $200)"));
    chanceDeck.addCard(Card("Chance", "Bank error in your favor. Collect $75"));
    chanceDeck.addCard(Card("Chance", "Go to Jail. Go directly to Jail."));
    std::cout << "Original Chance Deck:\n" << chanceDeck;
    chanceDeck.shuffle();
    std::cout << "\nShuffled Chance Deck:\n" << chanceDeck;
    try {
        Card drawnChanceCard = chanceDeck.drawCard();
        std::cout << "Drawn Chance Card: " << drawnChanceCard << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    // Instantiation 2: Deck of Integers (e.g., for Community Chest amounts)
    Deck<int> communityChestValues;
    communityChestValues.addCard(100); // Collect $100
    communityChestValues.addCard(-50); // Pay $50
    communityChestValues.addCard(20);  // Collect $20
    std::cout << "\nOriginal Community Chest Values Deck:\n" << communityChestValues;
    communityChestValues.shuffle();
    std::cout << "\nShuffled Community Chest Values Deck:\n" << communityChestValues;
    try {
        int drawnValue = communityChestValues.drawCard();
        std::cout << "Drawn Community Chest Value: $" << drawnValue << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }


    // --- Template Function Demonstration (`findInCollection`) ---
    std::cout << "\n--- Template Function Demonstration ---" << std::endl;
    std::vector<Player> playerList;
    playerList.push_back(p1);
    playerList.push_back(p2);
    playerList.push_back(Player("Charlie", Pawn("Green", {0,0}), 800));

    // Instantiation 1: Find player by name
    std::string nameToFind = "Bob";
    auto foundPlayerByName = findInCollection(playerList,
        [&nameToFind](const Player& p){ return p.getName() == nameToFind; });

    if (foundPlayerByName) {
        std::cout << "Found player by name '" << nameToFind << "': " << foundPlayerByName->getName() << " with budget $" << foundPlayerByName->getBuget() << std::endl;
    } else {
        std::cout << "Player with name '" << nameToFind << "' not found." << std::endl;
    }

    // Instantiation 2: Find player with budget less than 1000
    int budgetThreshold = 1000;
    auto foundPlayerByBudget = findInCollection(playerList,
        [budgetThreshold](const Player& p){ return p.getBuget() < budgetThreshold; });

    if (foundPlayerByBudget) {
        std::cout << "Found player with budget < $" << budgetThreshold << ": " << foundPlayerByBudget->getName() << " with budget $" << foundPlayerByBudget->getBuget() << std::endl;
    } else {
        std::cout << "No player found with budget < $" << budgetThreshold << "." << std::endl;
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
