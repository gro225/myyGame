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
};

#endif // BOSS_HPP
