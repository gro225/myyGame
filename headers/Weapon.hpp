#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Character;

class Weapon {
public:
    Weapon(int damage, float attackSpeed, 
           const sf::Texture& weaponTexture);

    void draw(sf::RenderTarget& window, const sf::Vector2f& position);

    // void update(float deltaTime);

    int getDamage() const;
    float getAttackSpeed() const;
    sf::Sprite& getSprite();
    void updatePosition(const sf::Vector2f& characterPosition, bool facingRight);

private:
    int damage;
    float attackSpeed;
    sf::Sprite sprite;

    sf::Sprite weaponSprite;
    Character* owner;
    std::vector<Weapon>& getDroppedItems();
};

#endif // WEAPON_HPP
