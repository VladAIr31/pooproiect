#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream> // For std::cout, std::cerr
#include <cmath>    // For std::abs, std::max, std::min
#include <algorithm> // For std::max, std::min
#include "incl/player.h"
#include "incl/chalet.h"
#include "incl/board.h"
#include "incl/boardconf.h"
#include "incl/prices.h"
#include "incl/exception.h"

int main() {




    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Monopoly Style Board - Single CPP");
    window.setFramerateLimit(60);

    GameBoard gameBoard;

    try {
        pawn p1_pawn("Rosu", {0, 0});
        player p1("Alice", p1_pawn, 500);
        std::cout << "Jucatorul initial:\n" << p1 << std::endl;

        auto chalet_ptr = std::make_unique<chalet>("Cabana Munte", 200);
        p1.add_property(std::move(chalet_ptr)); // Alice cumpără cabana
        std::cout << "Dupa cumparare:\n" << p1 << std::endl;


        int payment1 = 100;
        std::cout << "Alice incearca sa plateasca " << payment1 << "..." << std::endl;
        p1.pay(payment1);
        std::cout << "Plata reusita. Buget ramas: " << p1.getBuget() << std::endl;

        int payment2 = 1000;
        std::cout << "\nAlice incearca sa plateasca " << payment2 << "..." << std::endl;
        p1.pay(payment2);

        std::cout << "Aceasta linie nu ar trebui sa apara daca plata 2 esueaza." << std::endl;

    } catch (const FonduriInsuficienteError& e) {
        std::cerr << "\n!!! Eroare de Plata !!!\n";
        std::cerr << "Detalii: " << e.what() << std::endl;


    } catch (const RomopolyError& e) {
        // Prindem orice altă eroare specifică jocului derivată din RomopolyError
        std::cerr << "\n!!! Eroare Generala de Joc !!!\n";
        std::cerr << "Detalii: " << e.what() << std::endl;
        // Poți trata diferit alte erori ale jocului

    } catch (const std::exception& e) {
        // Prindem orice altă excepție standard (bună practică)
        std::cerr << "\n!!! Eroare Standard C++ !!!\n";
        std::cerr << "Detalii: " << e.what() << std::endl;

    } catch (...) {
        std::cerr << "\n!!! Eroare Necunoscuta !!!" << std::endl;
    }

    std::cout << "\nContinuam executia dupa blocul try/catch...\n" << std::endl;




    std::string potentialName = "Player1_Valid";
    if (player::isPlayerNameValid(potentialName)) {
        std::cout << "'" << potentialName << "' este un nume valid.\n";
        pawn p1_pawn("Albastru", {0,0});
        player p1(potentialName, p1_pawn, 1500);

        pawn p2_pawn("Verde", {0,0});
        player p2("Player2", p2_pawn, 1500);

        std::cout << "Numar curent de jucatori activi: " << player::getActivePlayers() << std::endl;

        {
            pawn p3_pawn("Galben", {0,0});
            player p3 = p1;
            std::cout << "Numar curent de jucatori activi (dupa copiere): " << player::getActivePlayers() << std::endl;
        }

        std::cout << "Numar curent de jucatori activi (dupa iesire bloc): " << player::getActivePlayers() << std::endl;

    } else {
        std::cout << "'" << potentialName << "' NU este un nume valid.\n";
    }



    std::cout << "Numar de jucatori activi la sfarsitul lui main (inainte de return): " << player::getActivePlayers() << std::endl;






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
