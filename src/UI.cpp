#include "../headers/UI.hpp"

UI::UI(float windowWidth, float windowHeight)
    : windowWidth(windowWidth), 
      windowHeight(windowHeight),
      maxHealth(100),
      currentHealth(100) {
    // Initialize health bar
    healthBarBackground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50)); // Gray background
    healthBarBackground.setPosition(10.f, 10.f);

    healthBar.setSize(sf::Vector2f(200.f, 20.f));
    healthBar.setFillColor(sf::Color::Green); // Green health bar
    healthBar.setPosition(10.f, 10.f);

    // Initialize weapon display
    weaponDisplayBackground.setSize(sf::Vector2f(40.f, 40.f));
    weaponDisplayBackground.setFillColor(sf::Color(100, 100, 100)); // Gray background
    weaponDisplayBackground.setOutlineThickness(2.f);
    weaponDisplayBackground.setOutlineColor(sf::Color::White);
	weaponDisplayBackground.setPosition(sf::Vector2f(windowWidth - 108.f, 40.f));
}

void UI::updatePlayerHealth(int currentHealth, int maxHealth) {
    this->currentHealth = currentHealth;
    this->maxHealth = maxHealth;
    updateHealthBar();
}

void UI::updateWeaponSprite(const sf::Sprite& newWeaponSprite) {
    weaponSprite = newWeaponSprite;
    weaponSprite.setPosition(weaponDisplayBackground.getPosition() + sf::Vector2f(14.f, 0.f)); 
    weaponSprite.setScale(0.1f, 0.1f);
}

void UI::updateHealthBar() {
    float healthRatio = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);
    healthBar.setSize(sf::Vector2f(200.f * healthRatio, 20.f));
    if (healthRatio > 0.5f) {
        healthBar.setFillColor(sf::Color::Green);
    } else if (healthRatio > 0.2f) {
        healthBar.setFillColor(sf::Color::Yellow);
    } else {
        healthBar.setFillColor(sf::Color::Red);
    }
}

void UI::draw(sf::RenderWindow& window) const {
    // Draw health bar
    window.draw(healthBarBackground);
    window.draw(healthBar);

    // Draw weapon display
    window.draw(weaponDisplayBackground);
    if (weaponSprite.getTexture() != nullptr) { 
        window.draw(weaponSprite);
    }
}