#include "../headers/Boss.hpp"
class Character;
class GameMap;
Boss::Boss(const sf::Texture& texture, 
           const std::vector<sf::IntRect>& idleFrames,
           const std::vector<sf::IntRect>& walkFrames,
           const std::vector<sf::IntRect>& attackFrames,
           const std::vector<sf::IntRect>& hitFrames,
           const std::vector<sf::IntRect>& deathFrames,
           float frameDuration)
    : Entity(texture, idleFrames.empty() ? sf::IntRect() : idleFrames[0]),
      health(500),
      dead(false),
      attackCooldown(2.0f),
      attackTimer(0.0f),
	  idleFrames(idleFrames), 
      walkFrames(walkFrames), 
      attackFrames(attackFrames), 
      hitFrames(hitFrames), 
      deathFrames(deathFrames), 
      frameDuration(frameDuration), 
      moveSpeed(20.f), 
      elapsedTime(0.0f), 
      currentAnimation(AnimationState::Idle),
      idleAnimation(sprite, idleFrames, frameDuration), 
      walkAnimation(sprite, walkFrames, frameDuration),
      attackAnimation(sprite, attackFrames, frameDuration),
      hitAnimation(sprite, hitFrames, frameDuration),
      deathAnimation(sprite, deathFrames, frameDuration) {
    sprite.setScale(2.0f, 2.0f); 
}

void Boss::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition) {
    sf::Vector2f monsterPosition = getPosition();
    sf::Vector2f direction = playerPosition - monsterPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < chaseRange) {
        if (distance > 0.0f) {
            direction /= distance;  // Нормализация
        }

        if (distance > attackRange) {
            if (currentAnimation != AnimationState::Walk) {
                currentAnimation = AnimationState::Walk;
                // walkAnimation.restart();
            }
            walkAnimation.update(deltaTime);
            sprite.move(direction * moveSpeed * deltaTime);
        } else {
            if (currentAnimation != AnimationState::Attack) {
                currentAnimation = AnimationState::Attack;
                // attackAnimation.restart();
            }
            attackAnimation.update(deltaTime);
        }
    } else {
        if (currentAnimation != AnimationState::Idle) {
            currentAnimation = AnimationState::Idle;
            // animation.restart();
        }
        idleAnimation.update(deltaTime);
    }
}


void Boss::takeDamage(int damage, float deltaTime) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        dead = true;
        currentAnimation = AnimationState::Death;
    } else {
        currentAnimation = AnimationState::Hit;
    }
}

bool Boss::isDead() const {
    return dead;
}

int Boss::getAttackPower() const {
    return attackPower; 
}

AnimationState Boss::getCurrentAnimation() const {
    return currentAnimation;
}

