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
      deathAnimation(sprite, deathFrames, frameDuration){}


void Monster::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition) {
   

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
            }
            walkAnimation.update(deltaTime);
            sprite.move(direction * moveSpeed * deltaTime);
        } else {
            attack(deltaTime);
            }
    } else {
        if (currentAnimation != AnimationState::Idle) {
            currentAnimation = AnimationState::Idle;
        }
        idleAnimation.update(deltaTime);
    }
}


void Monster::attack(float deltaTime) {

    if (currentAnimation != AnimationState::Attack) {
        currentAnimation = AnimationState::Attack;
        attackAnimation.reset();
    }

    attackAnimation.updateOnce(deltaTime);
    currentAnimation = AnimationState::Idle;
}
void Monster::takeHit(float deltaTime){
    hitAnimation.updateOnce(deltaTime);
    hitAnimation.reset();

}

void Monster::playDeath(float deltaTime){
     deathAnimation.updateOnce(deltaTime);
}


sf::Vector2f Monster::getPosition() const {
    return sprite.getPosition(); 
}

bool Monster::isDead() const {
    return currentAnimation == AnimationState::Death;
}

void Monster::takeDamage(int damage, float deltaTime) {
    health -= damage;
    if (health <= 0) {
        currentAnimation = AnimationState::Death;
        playDeath(deltaTime);
    } else {
        currentAnimation = AnimationState::Hit;
        takeHit(deltaTime);
        currentAnimation = AnimationState::Idle;
    }
    std::cout << "Monster HP: " << health << std::endl;
}

int Monster::getAttackPower() const {
    return attackPower;  // Вернуть значение силы атаки
}

AnimationState Monster::getCurrentAnimation() const {
    return currentAnimation;
}

// void Monster::setGlobalPosition(const sf::Vector2f& position) {
//     globalPosition = position;
//     updateRenderPosition(0.0f, 0.0f); // Обновляем отображаемую позицию
// }

// sf::Vector2f Monster::getGlobalPosition() const {
//     return globalPosition;
// }

// void Monster::updateRenderPosition(float offsetX, float offsetY) {
//     sprite.setPosition(sf::Vector2f(globalPosition.x - offsetX, globalPosition.y - offsetY));
//     bounds = sprite.getGlobalBounds(); // Обновляем границы
// }














// #include "../headers/Monster.hpp"
// #include "../headers/Character.hpp"



// Monster::Monster(const sf::Texture& texture, 
//                  const std::vector<sf::IntRect>& idleFrames, 
//                  const std::vector<sf::IntRect>& walkFrames, 
//                  const std::vector<sf::IntRect>& attackFrames, 
//                  const std::vector<sf::IntRect>& hitFrames, 
//                  const std::vector<sf::IntRect>& deathFrames, 
//                  float frameDuration)
//     : Entity(texture, idleFrames.empty() ? sf::IntRect() : idleFrames[0]), 
//       idleFrames(idleFrames), 
//       attackFrames(attackFrames), 
//       walkFrames(walkFrames), 
//       frameDuration(frameDuration), 
//       moveSpeed(34.f), 
//       elapsedTime(0.0f), 
//       animation(sprite, idleFrames, frameDuration), 
//       attackAnimation(sprite, attackFrames, frameDuration) 
// {}

// void Monster::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition) {
//     animation.update(deltaTime);
//     sf::Vector2f monsterPosition = getPosition();
//     // Вектор направления к игроку
//     sf::Vector2f direction = playerPosition - monsterPosition;

//     // Расстояние до игрока
//     float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

//     if (distance < chaseRange) {
//         elapsedTime += deltaTime;

//         if (elapsedTime >= frameDuration) {
//             elapsedTime -= frameDuration;
//             currentFrame = (currentFrame + 1) % idleFrames.size();
//             sprite.setTextureRect(idleFrames[currentFrame]);
//         }

//         if (distance > 0.0f) {
//             direction /= distance;  // Нормализация
//         }

//         // Обновление позиции монстра
//         if (distance > attackRange) {
//             sprite.move(direction * moveSpeed * deltaTime);
//         } else {
//             elapsedTime += deltaTime;

//             if (elapsedTime >= frameDuration) {
//                 elapsedTime -= frameDuration;
//                 currentFrame = (currentFrame + 1) % attackFrames.size();
//                 sprite.setTextureRect(attackFrames[currentFrame]);
//             }
//         }
//     } 
// }


// void Monster::attack(float deltaTime) {
//     sprite.setTextureRect(attackFrames[0]);
//     Animation attackAnimation(sprite, attackFrames, 0.1f);
//     animation.update(deltaTime); 
// }

// sf::Vector2f Monster::getPosition() const {
//     return sprite.getPosition(); 
// }









// #include "../headers/Monster.hpp"
// #include "../headers/Character.hpp"

// Monster::Monster(const sf::Texture& texture, 
//     const std::vector<sf::IntRect>& idleFrames, 
//     const std::vector<sf::IntRect>& walkFrames, 
//     const std::vector<sf::IntRect>& attackFrames, 
//     const std::vector<sf::IntRect>& hitFrames, 
//     const std::vector<sf::IntRect>& deathFrames, 
//     float frameDuration)
//     : Entity(texture, idleFrames[0]), 
//       moveSpeed(34.f), 
//       chaseRange(200.f), 
//       attackRange(50.f), 
//       animation(sprite, idleFrames, walkFrames, attackFrames, hitFrames, deathFrames, frameDuration),
//       state(MonsterState::Idle),
//       elapsedTime(0.0f)
// {}

// void Monster::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight, const sf::Vector2f& playerPosition) {
//     sf::Vector2f monsterPosition = getPosition();
//     sf::Vector2f direction = playerPosition - monsterPosition;
//     float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

//     if (distance < chaseRange) {
//         if (distance > attackRange) {
//             state = MonsterState::Walk;
//             direction /= distance;  // Нормализация
//             sprite.move(direction * moveSpeed * deltaTime);
//         } else {
//             state = MonsterState::Attack;
//         }
//     } else {
//         state = MonsterState::Idle;
//     }

//     animation.setState(state);
//     animation.update(deltaTime);
// }

// sf::Vector2f Monster::getPosition() const {
//     return sprite.getPosition(); 
// }

// void Monster::attack(float deltaTime) {
//     animation.setState(MonsterState::Attack);
//     animation.update(deltaTime);
// }
























