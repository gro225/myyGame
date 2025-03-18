#ifndef BOSS_HPP
#define BOSS_HPP

#include "Entity.hpp"
#include "Animation.hpp"
#include "GameMap.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Character;
class GameMap;

class Boss : public Entity {
public:
	using AnimationState = ::AnimationState;
    Boss(const sf::Texture& texture, 
         const std::vector<sf::IntRect>& idleFrames,
         const std::vector<sf::IntRect>& walkFrames,
         const std::vector<sf::IntRect>& attackFrames,
         const std::vector<sf::IntRect>& hitFrames,
         const std::vector<sf::IntRect>& deathFrames,
         float frameDuration);

    virtual void update(float deltaTime, GameMap& gamemap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition);
    void takeDamage(int damage, float deltaTime);
    int getAttackPower() const ;
    AnimationState getCurrentAnimation() const;
    void setGlobalPosition(const sf::Vector2f& position);
    sf::Vector2f getGlobalPosition() const;
    void updatePosition(float offsetX, float offsetY);
    void attack(float deltaTime);
    bool isRecentlyHit() const { return recentlyHit; }
    void setRecentlyHit(bool value) { recentlyHit = value; hitTimer = 0.f; }
    void wander(float deltaTime);
    



    bool isDead() const;

private:
	float attackRange = 5.0f;
    float chaseRange = 200.0f; 
	float frameDuration;
    float elapsedTime;
	float moveSpeed;
    int health;
    int attackPower = 25; 
    bool dead;
    float attackCooldown;
    float attackTimer;
    bool recentlyHit = false;
    float hitCooldown = 0.5f; 
    float hitTimer = 0.f;

    float wanderTime;
    float wanderCooldown;
    bool isWandering;
    sf::Vector2f wanderDirection;
    float wanderMoveTime;
    float wanderMoveDuration;
    float wanderSpeed;
    bool isAnimationPlaying = false;
	Animation idleAnimation;            
    Animation walkAnimation;       
    Animation attackAnimation;      
    Animation hitAnimation;         
    Animation deathAnimation;
	AnimationState currentAnimation;
	std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> attackFrames;
    std::vector<sf::IntRect> walkFrames;
    std::vector<sf::IntRect> hitFrames;
    std::vector<sf::IntRect> deathFrames;
    sf::Vector2f globalPosition;
    sf::FloatRect bounds;
};

#endif // BOSS_HPP
