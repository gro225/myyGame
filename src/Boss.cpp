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
                isWandering = false; // Останавливаем блуждание
                wanderTime = 0.0f;   // Сбрасываем таймер ожидания
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
void Boss::wander(float deltaTime) {
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

void Boss::attack(float deltaTime) {
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

void Boss::setGlobalPosition(const sf::Vector2f& position) {
    globalPosition = position;
    sprite.setPosition(globalPosition); 
}

sf::Vector2f Boss::getGlobalPosition() const {
    return globalPosition;
}

void Boss::updatePosition(float offsetX, float offsetY) {
    sprite.setPosition(sf::Vector2f(globalPosition.x - offsetX, globalPosition.y - offsetY));
    bounds = sprite.getGlobalBounds();
}

