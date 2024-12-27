#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>

class UI {
public:
    UI(float windowWidth, float windowHeight);

    void updatePlayerHealth(int currentHealth, int maxHealth);
    void updateWeaponSprite(const sf::Sprite& weaponSprite);

    void draw(sf::RenderWindow& window) const;

private:
    void updateHealthBar();

    // Health bar elements
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;

    // Weapon display elements
    sf::RectangleShape weaponDisplayBackground;
    sf::Sprite weaponSprite;

    // Health and UI dimensions
    int maxHealth;
    int currentHealth;

    float windowWidth;
    float windowHeight;
};

#endif // UI_HPP
