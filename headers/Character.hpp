#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "Animation.hpp"
#include "GameMap.hpp"
#include "Weapon.hpp"
#include "UI.hpp"
#include <SFML/Graphics.hpp>

class Monster;
class Boss;
class Dungeon;



class Character : public Entity {
public:
    Character(const sf::Texture& texture,
              const std::vector<sf::IntRect>& idleFrames, 
              const std::vector<sf::IntRect>& walkFrames, 
              const std::vector<sf::IntRect>& attackFrames, 
              const std::vector<sf::IntRect>& hitFrames, 
              const std::vector<sf::IntRect>& deathFrames, 
              float frameDuration);
    void update(float deltaTime, GameMap& gameMap,  int windowWidth, int windowHeight);
    void move(float offsetX, float offsetY);
    void handleInput(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight);
    void attack(float deltaTime);
    void takeDamage(int damage);
    void checkCollisionWith(Monster& monster, float deltaTime);
    void checkCollisionWithBoss(Boss& boss, float deltaTime);
    void interactWithDroppedItems(GameMap& gameMap);
    // void equipWeapon(const Weapon& weapon);
    bool isDead() const;
    bool checkCollisionWithMap(GameMap& map, const sf::Vector2f& nextPosition);
    sf::Vector2f getPosition() const;
    std::unique_ptr<Weapon> equipWeapon(std::unique_ptr<Weapon> newWeapon);
    const sf::Sprite& getWeaponSprite() const;
    void draw(sf::RenderTarget& target) const;
private:
    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> walkFrames;
    std::vector<sf::IntRect> attackFrames;
    std::vector<sf::IntRect> hitFrames;
    std::vector<sf::IntRect> deathFrames;

    // std::vector<std::shared_ptr<Weapon>> inventory; // Инвентарь персонажа
    // std::shared_ptr<Weapon> equippedWeapon;


    Animation idleAnimation;            
    Animation walkAnimation;       
    Animation attackAnimation;      
    Animation hitAnimation;         
    Animation deathAnimation; 
    AnimationState currentAnimation;

    const float OFFSET_THRESHOLD = 120.0f;
    float moveSpeed;
    float elapsedTime;
    int health;
    int attackPower;
    std::vector<std::unique_ptr<Dungeon>> dungeons;
    std::vector<std::unique_ptr<Monster>> monsters;
    std::vector<std::unique_ptr<Weapon>> weapons;
    std::unique_ptr<Weapon>  currentWeapon = nullptr;

};

#endif // CHARACTER_HPP