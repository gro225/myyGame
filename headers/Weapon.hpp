#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Character;
class Monsrer;

class Weapon {
public:
    Weapon(int damage, float attackSpeed, 
           const sf::Texture& weaponTexture);

    void draw(sf::RenderTarget& window, const sf::Vector2f& position);


    int getDamage() const;
    float getAttackSpeed() const;
    sf::Sprite& getSprite();
    void updatePosition(const sf::Vector2f& characterPosition, bool facingRight);
    void setGlobalPosition(const sf::Vector2f& position);
    sf::Vector2f getGlobalPosition() const;
    void updateRenderPosition(float offsetX, float offsetY); 

private:
    int damage;
    float attackSpeed;
    sf::Sprite sprite;

    sf::Sprite weaponSprite;
    Character* owner;
    std::vector<Weapon>& getDroppedItems();

    sf::FloatRect bounds;
    sf::Vector2f globalPosition;
};

#endif // WEAPON_HPP
