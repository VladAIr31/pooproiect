//
// Created by vladg on 5/5/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics/Color.hpp> // Include necessary SFML headers

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream> // For error messages in constructor/helpers if needed

// Include the board configuration constants
#include "Boardconf.h" // Uses constants like boardOffsetX, etc.

class GameBoard {
public:
    // Constructor: Initializes the board elements
    GameBoard();

    // Draw the board onto a render target (e.g., the window)
    void draw(sf::RenderTarget& target) const;

private:
    // --- Textures ---
    sf::Texture houseTexture;
    sf::Texture goCornerTexture;
    sf::Texture jailTexture;
    sf::Texture parkingTexture;
    sf::Texture goToJailTexture;

    // --- Shapes & Sprites ---
    std::vector<sf::RectangleShape> colorBarShapes;
    std::vector<sf::Sprite>         middleSprites;
    sf::Sprite                      bottomRightCornerSprite;
    sf::Sprite                      bottomLeftCornerSprite;
    sf::Sprite                      topLeftCornerSprite;
    sf::Sprite                      topRightCornerSprite;
    sf::VertexArray                 gridLines;

    // --- Private Helper Functions (Declarations only) ---
    // These will be implemented in main.cpp
    bool loadTexture(sf::Texture& texture, const std::string& filename);
    sf::Sprite createCenteredRotatedSprite(const sf::Texture& texture, sf::FloatRect targetBounds, float rotationAngle);
    void configureCornerSprite(sf::Sprite& sprite, const sf::Texture& texture, sf::FloatRect cornerBounds);
    void configureColorBarFill(sf::RectangleShape& bar, const sf::Color& fillColor);
    void addLine(float x1, float y1, float x2, float y2);
    void initializeBoardElements();
};

#endif //BOARD_H
