//
// Created by vladg on 5/5/2025.
//

#ifndef BOARDCONF_H
#define BOARDCONF_H
#include <SFML/Graphics/Color.hpp>
// --- Board Configuration ---
const unsigned int windowWidth = 1000;
const unsigned int windowHeight = 1000;
const float boardTotalWidth = 800.0f;
const float boardTotalHeight = 800.0f;
const float boardOffsetX = (windowWidth - boardTotalWidth) / 2.0f;
const float boardOffsetY = (windowHeight - boardTotalHeight) / 2.0f;
const float borderThickness = 100.0f;
const float cornerSize = borderThickness;
const int numSpacesPerSide = 7;
// No need for mainOutlineThickness for shapes anymore
// No need for colorBarOutlineThickness
const float colorBarThickness = 25.0f;
const float imagePadding = 3.0f; // Padding for middle images
const sf::Color boardBackgroundColor = sf::Color::White; // Base color if needed

// --- Define 8 Unique Colors ---
const sf::Color colorTop13 = sf::Color(173, 216, 230);
const sf::Color colorTop57 = sf::Color(255, 182, 193);
const sf::Color colorBottom13 = sf::Color(144, 238, 144);
const sf::Color colorBottom57 = sf::Color(255, 255, 0);
const sf::Color colorLeft13 = sf::Color(255, 160, 122);
const sf::Color colorLeft57 = sf::Color(216, 191, 216);
const sf::Color colorRight13 = sf::Color(255, 165, 0);
const sf::Color colorRight57 = sf::Color(165, 42, 42);

// --- Rotation Angles ---
const float rotationTop = 180.0f;
const float rotationBottom = 0.0f;
const float rotationLeft = 90.0f;
const float rotationRight = 270.0f;

// --- Calculated Dimensions ---
const float topBottomSpaceWidth = (boardTotalWidth - 2.0f * cornerSize) / numSpacesPerSide;
const float leftRightSpaceHeight = (boardTotalHeight - 2.0f * cornerSize) / numSpacesPerSide;

#endif //BOARDCONF_H
