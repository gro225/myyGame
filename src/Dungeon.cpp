#include "../headers/Dungeon.hpp"

Dungeon::Dungeon(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect)
    : globalPosition(position),
    visible(true),
    completed(false) { 
    sprite.setTexture(texture);
    sprite.setTextureRect(rect); 
    sprite.setPosition(position); 
    bounds = sprite.getGlobalBounds();
}

void Dungeon::draw(sf::RenderWindow& window) {
    if (visible) {
        window.draw(sprite);
    }
}

const sf::FloatRect& Dungeon::getBounds() const {
    return bounds;
}

void Dungeon::setGlobalPosition(const sf::Vector2f& position) {
    globalPosition = position;
    updateRenderPosition(0.0f, 0.0f); 
}

sf::Vector2f Dungeon::getGlobalPosition() const {
    return globalPosition;
}

void Dungeon::updateRenderPosition(float offsetX, float offsetY) {
    sprite.setPosition(sf::Vector2f(globalPosition.x - offsetX, globalPosition.y - offsetY));
    bounds = sprite.getGlobalBounds();
}

sf::FloatRect Dungeon::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
void Dungeon::setVisible(bool isVisible) { 
    visible = isVisible; 
}

bool Dungeon::getVisible() const { 
    return visible; 
}

void Dungeon::setCompleted(bool isCompleted) { 
    completed = isCompleted; 
}

bool Dungeon::getCompleted() const { 
    return completed;
}

