#include "player.h"

#include "board.h" // Provides constants
  // Provides GameBoard class declaration

// --- GameBoard Class Implementation ---
// Define the methods declared in GameBoard.hpp here

// Constructor Implementation
GameBoard::GameBoard() : gridLines(sf::Lines) {
    // Load textures first
    if (!loadTexture(houseTexture, "incl/cabana.jpg") ||
        !loadTexture(goCornerTexture, "incl/start.jpg") ||
        !loadTexture(jailTexture, "incl/jail.jpg") ||
        !loadTexture(parkingTexture, "incl/park.jpg") ||
        !loadTexture(goToJailTexture, "incl/gtjail.jpg"))
    {
        std::cerr << "FATAL: Failed to load one or more essential textures. Exiting." << std::endl;
        exit(1); // Exit if textures can't be loaded
    }
    // Initialize all board elements
    initializeBoardElements();
}

// Texture Loading Helper Implementation
bool GameBoard::loadTexture(sf::Texture& texture, const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading texture: " << filename << std::endl;
        return false;
    }
    texture.setSmooth(true);
    return true;
}

// Initialization of Board Elements Implementation
void GameBoard::initializeBoardElements() {
    colorBarShapes.clear();
    middleSprites.clear();
    gridLines.clear();

    // 1. Configure Corner Sprites
    sf::FloatRect tlCornerBounds(boardOffsetX, boardOffsetY, cornerSize, cornerSize);
    configureCornerSprite(topLeftCornerSprite, parkingTexture, tlCornerBounds);
    sf::FloatRect trCornerBounds(boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY, cornerSize, cornerSize);
    configureCornerSprite(topRightCornerSprite, goToJailTexture, trCornerBounds);
    sf::FloatRect brCornerBounds(boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY + boardTotalHeight - cornerSize, cornerSize, cornerSize);
    configureCornerSprite(bottomRightCornerSprite, goCornerTexture, brCornerBounds);
    sf::FloatRect blCornerBounds(boardOffsetX, boardOffsetY + boardTotalHeight - cornerSize, cornerSize, cornerSize);
    configureCornerSprite(bottomLeftCornerSprite, jailTexture, blCornerBounds);

    // --- Create Color Bars and Middle Sprites ---
    const int middleIndex = 3;

    // 2. Top Row
    for (int i = 0; i < numSpacesPerSide; ++i) {
        float currentX = boardOffsetX + cornerSize + i * topBottomSpaceWidth;
        float currentY = boardOffsetY;
        sf::FloatRect rectBounds(currentX, currentY, topBottomSpaceWidth, borderThickness);
        sf::Color barColor = sf::Color::Transparent;
        if (i == 0 || i == 2) { barColor = colorTop13; } else if (i == 4 || i == 6) { barColor = colorTop57; }

        if (barColor != sf::Color::Transparent) {
            // Calculate size directly
            float width = rectBounds.width;
            float height = colorBarThickness;
            if (width > 0 && height > 0) {
                // Create shape with calculated size
                sf::RectangleShape colorBar(sf::Vector2f(width, height));
                // Set position directly
                colorBar.setPosition(rectBounds.left, rectBounds.top + rectBounds.height - colorBarThickness);
                configureColorBarFill(colorBar, barColor);
                colorBarShapes.push_back(colorBar);
            }
        }
        if (i == middleIndex) { middleSprites.push_back(createCenteredRotatedSprite(houseTexture, rectBounds, rotationTop)); }
    }
    // 3. Bottom Row
    for (int i = 0; i < numSpacesPerSide; ++i) {
         float currentX = boardOffsetX + cornerSize + i * topBottomSpaceWidth;
         float currentY = boardOffsetY + boardTotalHeight - borderThickness;
         sf::FloatRect rectBounds(currentX, currentY, topBottomSpaceWidth, borderThickness);
         sf::Color barColor = sf::Color::Transparent;
         if (i == 0 || i == 2) { barColor = colorBottom13; } else if (i == 4 || i == 6) { barColor = colorBottom57; }

         if (barColor != sf::Color::Transparent) {
             // Calculate size directly
             float width = rectBounds.width;
             float height = colorBarThickness;
             if (width > 0 && height > 0) {
                 // Create shape with calculated size
                 sf::RectangleShape colorBar(sf::Vector2f(width, height));
                 // Set position directly
                 colorBar.setPosition(rectBounds.left, rectBounds.top);
                 configureColorBarFill(colorBar, barColor);
                 colorBarShapes.push_back(colorBar);
             }
         }
         if (i == middleIndex) { middleSprites.push_back(createCenteredRotatedSprite(houseTexture, rectBounds, rotationBottom)); }
     }
    // 4. Left Column
    for (int i = 0; i < numSpacesPerSide; ++i) {
        float currentX = boardOffsetX;
        float currentY = boardOffsetY + cornerSize + i * leftRightSpaceHeight;
        sf::FloatRect rectBounds(currentX, currentY, borderThickness, leftRightSpaceHeight);
        sf::Color barColor = sf::Color::Transparent;
        if (i == 0 || i == 2) { barColor = colorLeft13; } else if (i == 4 || i == 6) { barColor = colorLeft57; }

        if (barColor != sf::Color::Transparent) {
            // Calculate size directly
            float width = colorBarThickness;
            float height = rectBounds.height;
            if (width > 0 && height > 0) {
                // Create shape with calculated size
                sf::RectangleShape colorBar(sf::Vector2f(width, height));
                // Set position directly
                colorBar.setPosition(rectBounds.left + rectBounds.width - colorBarThickness, rectBounds.top);
                configureColorBarFill(colorBar, barColor);
                colorBarShapes.push_back(colorBar);
            }
        }
        if (i == middleIndex) { middleSprites.push_back(createCenteredRotatedSprite(houseTexture, rectBounds, rotationLeft)); }
    }
    // 5. Right Column
    for (int i = 0; i < numSpacesPerSide; ++i) {
        float currentX = boardOffsetX + boardTotalWidth - borderThickness;
        float currentY = boardOffsetY + cornerSize + i * leftRightSpaceHeight;
        sf::FloatRect rectBounds(currentX, currentY, borderThickness, leftRightSpaceHeight);
        sf::Color barColor = sf::Color::Transparent;
        if (i == 0 || i == 2) { barColor = colorRight13; } else if (i == 4 || i == 6) { barColor = colorRight57; }

        if (barColor != sf::Color::Transparent) {
            // Calculate size directly
            float width = colorBarThickness;
            float height = rectBounds.height;
            if (width > 0 && height > 0) {
                // Create shape with calculated size
                sf::RectangleShape colorBar(sf::Vector2f(width, height));
                // Set position directly
                colorBar.setPosition(rectBounds.left, rectBounds.top);
                configureColorBarFill(colorBar, barColor);
                colorBarShapes.push_back(colorBar);
            }
        }
        if (i == middleIndex) { middleSprites.push_back(createCenteredRotatedSprite(houseTexture, rectBounds, rotationRight)); }
     }

    // --- Define Grid Lines ---
    addLine(boardOffsetX, boardOffsetY, boardOffsetX + boardTotalWidth, boardOffsetY); // Top
    addLine(boardOffsetX + boardTotalWidth, boardOffsetY, boardOffsetX + boardTotalWidth, boardOffsetY + boardTotalHeight); // Right
    addLine(boardOffsetX + boardTotalWidth, boardOffsetY + boardTotalHeight, boardOffsetX, boardOffsetY + boardTotalHeight); // Bottom
    addLine(boardOffsetX, boardOffsetY + boardTotalHeight, boardOffsetX, boardOffsetY); // Left
    addLine(boardOffsetX + cornerSize, boardOffsetY + cornerSize, boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY + cornerSize); // Top Inner
    addLine(boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY + cornerSize, boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY + boardTotalHeight - cornerSize); // Right Inner
    addLine(boardOffsetX + boardTotalWidth - cornerSize, boardOffsetY + boardTotalHeight - cornerSize, boardOffsetX + cornerSize, boardOffsetY + boardTotalHeight - cornerSize); // Bottom Inner
    addLine(boardOffsetX + cornerSize, boardOffsetY + boardTotalHeight - cornerSize, boardOffsetX + cornerSize, boardOffsetY + cornerSize); // Left Inner
    for(int i = 0; i < numSpacesPerSide - 1; ++i) {
        float x = boardOffsetX + cornerSize + (i + 1) * topBottomSpaceWidth;
        addLine(x, boardOffsetY, x, boardOffsetY + cornerSize); // Top row dividers
        addLine(x, boardOffsetY + boardTotalHeight - cornerSize, x, boardOffsetY + boardTotalHeight); // Bottom row dividers
    }
    for(int i = 0; i < numSpacesPerSide - 1; ++i) {
        float y = boardOffsetY + cornerSize + (i + 1) * leftRightSpaceHeight;
        addLine(boardOffsetX, y, boardOffsetX + cornerSize, y); // Left column dividers
        addLine(boardOffsetX + boardTotalWidth - cornerSize, y, boardOffsetX + boardTotalWidth, y); // Right column dividers
    }
}

// Color Bar Fill Helper Implementation
void GameBoard::configureColorBarFill(sf::RectangleShape& bar, const sf::Color& fillColor) {
    bar.setFillColor(fillColor);
    bar.setOutlineThickness(0);
}

// Centered Rotated Sprite Helper Implementation
sf::Sprite GameBoard::createCenteredRotatedSprite(const sf::Texture& texture, sf::FloatRect targetBounds, float rotationAngle) {
    sf::FloatRect paddedBounds;
    paddedBounds.left = targetBounds.left + imagePadding;
    paddedBounds.top = targetBounds.top + imagePadding;
    paddedBounds.width = std::max(0.0f, targetBounds.width - 2.0f * imagePadding);
    paddedBounds.height = std::max(0.0f, targetBounds.height - 2.0f * imagePadding);
    if (paddedBounds.width <= 1e-3 || paddedBounds.height <= 1e-3) return sf::Sprite();
    sf::Sprite sprite(texture);
    float textureWidth = static_cast<float>(texture.getSize().x);
    float textureHeight = static_cast<float>(texture.getSize().y);
    if (textureWidth <= 1e-3 || textureHeight <= 1e-3) return sf::Sprite();
    float scale = 1.0f;
    bool isSideways = (std::abs(rotationAngle - 90.0f) < 1.0f || std::abs(rotationAngle - 270.0f) < 1.0f);
    if (isSideways) {
        float scaleX_rot = paddedBounds.width / textureHeight; float scaleY_rot = paddedBounds.height / textureWidth;
        scale = std::min(scaleX_rot, scaleY_rot);
    } else {
        float scaleX = paddedBounds.width / textureWidth; float scaleY = paddedBounds.height / textureHeight;
        scale = std::min(scaleX, scaleY);
    }
    scale = std::max(0.0f, scale);
    sprite.setScale(scale, scale);
    sprite.setOrigin(textureWidth / 2.0f, textureHeight / 2.0f);
    sprite.setRotation(rotationAngle);
    float paddedCenterX = paddedBounds.left + paddedBounds.width / 2.0f;
    float paddedCenterY = paddedBounds.top + paddedBounds.height / 2.0f;
    sprite.setPosition(paddedCenterX, paddedCenterY);
    return sprite;
}

// Corner Sprite Helper Implementation
void GameBoard::configureCornerSprite(sf::Sprite& sprite, const sf::Texture& texture, sf::FloatRect cornerBounds) {
    sprite.setTexture(texture);
    if (cornerBounds.width <= 1e-3 || cornerBounds.height <= 1e-3) { sprite.setScale(0, 0); return; }
    float texW = static_cast<float>(texture.getSize().x); float texH = static_cast<float>(texture.getSize().y);
    if (texW <= 1e-3 || texH <= 1e-3) { sprite.setScale(0, 0); return; }
    float scaleX = cornerBounds.width / texW; float scaleY = cornerBounds.height / texH;
    float scale = std::min(scaleX, scaleY);
    scale = std::max(0.0f, scale);
    sprite.setScale(scale, scale);
    sprite.setPosition(cornerBounds.left, cornerBounds.top);
}

// Add Line Helper Implementation
void GameBoard::addLine(float x1, float y1, float x2, float y2) {
    gridLines.append(sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Black));
    gridLines.append(sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Black));
}

// Draw Method Implementation
void GameBoard::draw(sf::RenderTarget& target) const {
    target.draw(topLeftCornerSprite);
    target.draw(topRightCornerSprite);
    target.draw(bottomRightCornerSprite);
    target.draw(bottomLeftCornerSprite);
    for (const auto& shape : colorBarShapes) { target.draw(shape); }
    for (const auto& sprite : middleSprites) { target.draw(sprite); }
    target.draw(gridLines);
}

