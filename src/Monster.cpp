#include "../headers/Monster.hpp"
#include <iostream>
// #include "../headers/Character.hpp"


Monster::Monster(const sf::Texture& texture, 
                 const std::vector<sf::IntRect>& idleFrames, 
                 const std::vector<sf::IntRect>& walkFrames, 
                 const std::vector<sf::IntRect>& attackFrames, 
                 const std::vector<sf::IntRect>& hitFrames, 
                 const std::vector<sf::IntRect>& deathFrames, 
                 float frameDuration)
    : Entity(texture, idleFrames.empty() ? sf::IntRect() : idleFrames[0]),
      idleFrames(idleFrames), 
      walkFrames(walkFrames), 
      attackFrames(attackFrames), 
      hitFrames(hitFrames), 
      deathFrames(deathFrames), 
      frameDuration(frameDuration), 
      elapsedTime(0.0f), 
      currentAnimation(AnimationState::Idle),
      idleAnimation(sprite, idleFrames, frameDuration), 
      walkAnimation(sprite, walkFrames, frameDuration),
      attackAnimation(sprite, attackFrames, frameDuration),
      hitAnimation(sprite, hitFrames, frameDuration),
      deathAnimation(sprite, deathFrames, frameDuration),  wanderTime(0.0f), 
      wanderCooldown(3.0f),  
      isWandering(false), 
      wanderMoveTime(0.0f),
      wanderMoveDuration(2.0f), 
      wanderSpeed(10.0f) {}


      void Monster::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition) {
        sf::Vector2f monsterPosition = getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::Vector2f size(bounds.width, bounds.height);
    

        sf::Vector2f direction = playerPosition - monsterPosition;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    
        if (distance < chaseRange) {
            if (distance > 0.0f)
                direction /= distance;  
    

            if (distance > attackRange) {
                if (currentAnimation != AnimationState::Walk)
                    currentAnimation = AnimationState::Walk;
                walkAnimation.update(deltaTime);
                sf::Vector2f displacement = direction * moveSpeed * deltaTime;
                sf::Vector2f newPos = sprite.getPosition() + displacement;
                if (!gameMap.checkCollision(newPos, size)) {
                    sprite.move(displacement);
                    globalPosition += displacement;
                }
            } else {
                attack(deltaTime);
            }
        }
        // Блуждение
        else {
            wanderTime += deltaTime;
            if (isWandering) {
                wanderMoveTime += deltaTime;
                if (wanderMoveTime >= wanderMoveDuration) {
                    isWandering = false; 
                    wanderTime = 0.0f;  
                } else {
                    sf::Vector2f displacement = wanderDirection * wanderSpeed * deltaTime * 2.0f;
                    sf::Vector2f newPos = sprite.getPosition() + displacement;
                    if (!gameMap.checkCollision(newPos, size)) {
                        sprite.move(displacement);
                        globalPosition += displacement;
                    }
                    walkAnimation.update(deltaTime);
                }
            } else if (wanderTime >= wanderCooldown) {
                // Выбираем новое случайное направление для блуждания
                float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
                wanderDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
                isWandering = true;
                wanderMoveTime = 0.0f;
            }
            if (!isWandering) {
                if (currentAnimation != AnimationState::Idle)
                    currentAnimation = AnimationState::Idle;
                idleAnimation.update(deltaTime);
            }
        }
    }
    
    
    void Monster::wander(float deltaTime) {
        if (!isWandering) { 
            float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
            wanderDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
            isWandering = true;
            wanderTime = 0.0f;
        }
    
        if (isWandering) {
            wanderTime += deltaTime;
            if (wanderTime >= wanderCooldown) {
                isWandering = false;
            } else {
                if (currentAnimation != AnimationState::Walk) {
                    currentAnimation = AnimationState::Walk;
                }
                walkAnimation.update(deltaTime);
                sf::Vector2f displacement = wanderDirection * (moveSpeed / 2.0f) * deltaTime; 
                sprite.move(displacement);
                globalPosition += displacement;
            }
        }
    }

void Monster::attack(float deltaTime) {
    if (currentAnimation != AnimationState::Attack) {
        currentAnimation = AnimationState::Attack;
        attackAnimation.reset();
        isAnimationPlaying = true;
    }

    if (isAnimationPlaying) {
        attackAnimation.updateOnce(deltaTime);
        if (attackAnimation.isFinished()) {
            isAnimationPlaying = false;
            currentAnimation = AnimationState::Idle;
        }
    }
}

void Monster::playDeath(float deltaTime) {
    if (currentAnimation != AnimationState::Death) {
        currentAnimation = AnimationState::Death;
        deathAnimation.reset();
        isAnimationPlaying = true;
    }

    if (isAnimationPlaying) {
        deathAnimation.updateOnce(deltaTime);
        if (deathAnimation.isFinished()) {
            isAnimationPlaying = false;
        }
    }
}


sf::Vector2f Monster::getPosition() const {
    return sprite.getPosition(); 
}

bool Monster::isDead() const {
    return currentAnimation == AnimationState::Death;
}

void Monster::takeHit(float deltaTime) {
    if (currentAnimation != AnimationState::Hit) {
        currentAnimation = AnimationState::Hit;
        hitAnimation.reset();
        isAnimationPlaying = true;
    }

    if (isAnimationPlaying) {
        hitAnimation.updateOnce(deltaTime);
        if (hitAnimation.isFinished()) {
            isAnimationPlaying = false;
            currentAnimation = AnimationState::Idle; 
        }
    }
}
void Monster::takeDamage(int damage, float deltaTime) {
    if (currentAnimation == AnimationState::Death) return; 

    health -= damage;
    if (health <= 0) {
        playDeath(deltaTime);
    } else {
        takeHit(deltaTime);
    }
}

int Monster::getAttackPower() const {
    return attackPower;  
}

AnimationState Monster::getCurrentAnimation() const {
    return currentAnimation;
}

void Monster::setGlobalPosition(const sf::Vector2f& position) {
    globalPosition = position;
    sprite.setPosition(globalPosition); 
}

sf::Vector2f Monster::getGlobalPosition() const {
    return globalPosition;
}

void Monster::updatePosition(float offsetX, float offsetY) {
    sprite.setPosition(sf::Vector2f(globalPosition.x - offsetX, globalPosition.y - offsetY));
    bounds = sprite.getGlobalBounds(); 
}















