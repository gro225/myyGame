#include "../headers/Entity.hpp"

Entity::Entity(const sf::Texture& texture, const sf::IntRect& rect) {
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}

void Entity::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Entity::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}

void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
