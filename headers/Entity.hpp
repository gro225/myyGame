#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(const sf::Texture& texture, const sf::IntRect& rect);

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    sf::Sprite& getSprite();
    virtual void draw(sf::RenderWindow& window) const;
    friend class Game;

protected:
    sf::Sprite sprite;
};

#endif // ENTITY_HPP
