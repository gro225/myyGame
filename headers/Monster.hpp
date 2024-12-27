#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Entity.hpp"
#include "Animation.hpp"
#include "GameMap.hpp"
#include <SFML/Graphics.hpp>

class Character;


class Monster : public Entity {
public:
    using AnimationState = ::AnimationState; // Импортируем в область видимости Monster
    Monster(const sf::Texture& texture, const std::vector<sf::IntRect>& idleFrames, const std::vector<sf::IntRect>& walkFrames, const std::vector<sf::IntRect>& attackFrames, const std::vector<sf::IntRect>& hitFrames, const std::vector<sf::IntRect>& deathFrames, float frameDuration);

    virtual void update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition); 
    sf::Vector2f getPosition() const;

    void takeDamage(int damage, float deltaTime);
    int getAttackPower() const;

    void playIdleAnimation(); 
    void playAttackAnimation();
    void attack(float deltaTime);
    void takeHit(float deltaTime);
    void playDeath(float deltaTime);
    bool isDead() const;
    void setGlobalPosition(const sf::Vector2f& position);
    sf::Vector2f getGlobalPosition() const;

void updatePosition(const sf::Vector2f& mapOffset);
    

protected:
    sf::Sprite spr; 

    Animation idleAnimation;            
    Animation walkAnimation;       
    Animation attackAnimation;      
    Animation hitAnimation;         
    Animation deathAnimation;
    AnimationState currentAnimation;  
    friend class Character;      
    

    sf::Vector2f initialPosition;
    float moveSpeed = 20.f;
    float frameDuration;
    float elapsedTime;

    size_t currentFrame;
    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> attackFrames;
    std::vector<sf::IntRect> walkFrames;
    std::vector<sf::IntRect> hitFrames;
    std::vector<sf::IntRect> deathFrames;

    float getDistanceToCharacter(const Character& character) const;
    AnimationState getCurrentAnimation() const;

    bool isAttacking = false;

    float attackRange = 5.0f;
    float chaseRange = 200.0f; 
    int health = 100;
    int attackPower = 5;
    sf::FloatRect bounds;
    sf::Vector2f globalPosition;
    
};

#endif //MONSTER_HPP