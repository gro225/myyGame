#include "../headers/Character.hpp"
#include "../headers/Game.hpp"
#include <iostream>



Character::Character(const sf::Texture& texture,
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
      moveSpeed(100.f), 
      elapsedTime(0.0f),
      currentAnimation(AnimationState::Idle),
      idleAnimation(sprite, idleFrames, frameDuration), 
      walkAnimation(sprite, walkFrames, frameDuration),
      attackAnimation(sprite, attackFrames, frameDuration),
      hitAnimation(sprite, hitFrames, frameDuration),
      deathAnimation(sprite, deathFrames, frameDuration),
      health(100),
      attackPower(25) {}



      void Character::update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight) {
        if (isRecentlyHit) {
            hitTimer += deltaTime;
            if (hitTimer >= hitCooldown) {
                isRecentlyHit = false;
                hitTimer = 0.0f;
            }
        }
        
        handleInput(deltaTime, gameMap, windowWidth, windowHeight);
    
        switch (currentAnimation) {
            case AnimationState::Idle:
                idleAnimation.update(deltaTime);
                break;
            case AnimationState::Walk:
                walkAnimation.update(deltaTime);
                break;
            case AnimationState::Attack:
                attackAnimation.updateOnce(deltaTime);
                break;
            case AnimationState::Hit:
                hitAnimation.updateOnce(deltaTime);
                currentAnimation = AnimationState::Idle;
                break;
            case AnimationState::Death:
                deathAnimation.updateOnce(deltaTime);
                break;
        }
    }
    

std::unique_ptr<Weapon> Character::equipWeapon(std::unique_ptr<Weapon> newWeapon) {
     std::unique_ptr<Weapon> oldWeapon = std::move(currentWeapon); 
    currentWeapon = std::move(newWeapon);                       
    return oldWeapon;  
}
const sf::Sprite& Character::getWeaponSprite() const {
    if (currentWeapon) {
        return currentWeapon->getSprite();
    }
    static sf::Sprite emptySprite;
    return emptySprite;
}

void Character::draw(sf::RenderTarget& target) const {
    target.draw(sprite); 
    if (currentWeapon) {
        currentWeapon->draw(target,sf::Vector2f(sprite.getPosition().x+20.f,sprite.getPosition().y+10.f)); 
    }
}



void Character::handleInput(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight) {
    if (currentAnimation == AnimationState::Death || currentAnimation == AnimationState::Hit)
        return;

    const float collisionMargin = 2.f;


    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    float moveX = 0.f, moveY = 0.f;


    if (gameMap.checkCollision(currentPos, size)) {
        return; 
    }

    // Горизонтальное движение
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sf::Vector2f newPos = currentPos - sf::Vector2f(moveSpeed * deltaTime + collisionMargin, 0);
        if (!gameMap.checkCollision(newPos, size)) {
            moveX = -moveSpeed * deltaTime;
            sprite.setScale(-2.0f, 2.0f);
            sprite.setOrigin(sprite.getLocalBounds().width, 0);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sf::Vector2f newPos = currentPos + sf::Vector2f(moveSpeed * deltaTime + collisionMargin, 0);
        if (!gameMap.checkCollision(newPos, size)) {
            moveX = moveSpeed * deltaTime;
            sprite.setScale(2.0f, 2.0f);
            sprite.setOrigin(0, 0);
        }
    }

    // Перемещение по X
    if (moveX != 0.f) sprite.move(moveX, 0);
    currentPos = sprite.getPosition();

    // Вертикальное движение
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sf::Vector2f newPos = currentPos - sf::Vector2f(0, moveSpeed * deltaTime + collisionMargin);
        if (!gameMap.checkCollision(newPos, size)) {
            moveY = -moveSpeed * deltaTime;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sf::Vector2f newPos = currentPos + sf::Vector2f(0, moveSpeed * deltaTime + collisionMargin);
        if (!gameMap.checkCollision(newPos, size)) {
            moveY = moveSpeed * deltaTime;
        }
    }

    // Перемещение по Y
    if (moveY != 0.f) sprite.move(0, moveY);

   
    currentAnimation = (moveX != 0.f || moveY != 0.f) ? AnimationState::Walk : AnimationState::Idle;

   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentAnimation != AnimationState::Attack) {
        currentAnimation = AnimationState::Attack;
    }

    // Проверяем цвет тайла под персонажем
    sf::Vector2f playerPosition = sprite.getPosition();
    sf::Color tileColor = gameMap.getPixelColorAtPosition(playerPosition);
    
    std::cout << "Player is on pixel color: ("
              << static_cast<int>(tileColor.r) << ", "
              << static_cast<int>(tileColor.g) << ", "
              << static_cast<int>(tileColor.b) << ")" << std::endl;

    // Камера
    sf::Vector2f shift(0.f, 0.f);
    sf::Vector2f spritePos = sprite.getPosition();

    if (spritePos.x < OFFSET_THRESHOLD)
        shift.x = OFFSET_THRESHOLD - spritePos.x;
    else if (spritePos.x > windowWidth - OFFSET_THRESHOLD - sprite.getGlobalBounds().width)
        shift.x = (windowWidth - OFFSET_THRESHOLD - sprite.getGlobalBounds().width) - spritePos.x;

    if (spritePos.y < OFFSET_THRESHOLD)
        shift.y = OFFSET_THRESHOLD - spritePos.y;
    else if (spritePos.y > windowHeight - OFFSET_THRESHOLD - sprite.getGlobalBounds().height)
        shift.y = (windowHeight - OFFSET_THRESHOLD - sprite.getGlobalBounds().height) - spritePos.y;

    if (shift != sf::Vector2f(0.f, 0.f)) {
        gameMap.offsetX -= shift.x;
        gameMap.offsetY -= shift.y;
        sprite.move(shift);
    }
}




bool Character::checkCollisionWithMap(GameMap& map, const sf::Vector2f& nextPosition) {
    return map.checkCollision(nextPosition, sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}


void Character::checkCollisionWith(Monster& monster, float deltaTime) {
    if (currentAnimation == AnimationState::Death || monster.isDead()) return;

    if (sprite.getGlobalBounds().intersects(monster.getSprite().getGlobalBounds())) {
        if (currentAnimation == AnimationState::Attack && monster.getCurrentAnimation() != Monster::AnimationState::Hit) {
            monster.takeDamage(attackPower, deltaTime);
        }
        if (monster.getCurrentAnimation() == Monster::AnimationState::Attack && currentAnimation != AnimationState::Hit) {
            takeDamage(monster.getAttackPower());
        }
    }
}

void Character::checkCollisionWithBoss(Boss& boss, float deltaTime){
    if (currentAnimation == AnimationState::Death || boss.isDead()) return;

    if (sprite.getGlobalBounds().intersects(boss.getSprite().getGlobalBounds())) {
        if (currentAnimation == AnimationState::Attack && boss.getCurrentAnimation() != Boss::AnimationState::Hit) {
            boss.takeDamage(attackPower, deltaTime);
        }
        if (boss.getCurrentAnimation() == Boss::AnimationState::Attack && currentAnimation != AnimationState::Hit) {
            takeDamage(boss.getAttackPower());
        }
    }

}
 
void Character::takeDamage(int damage) {
    if (isRecentlyHit) {
        return; 
    }
    
    health -= damage;
    isRecentlyHit = true;
    hitTimer = 0.0f;    

    if (health <= 0) {
        currentAnimation = AnimationState::Death;
    } else {
        currentAnimation = AnimationState::Hit;
    }
    std::cout << "Character HP: " << health << std::endl;
}


sf::Vector2f Character::getPosition() const {
    return sprite.getPosition();
}

bool Character::isDead() const {
    return currentAnimation == AnimationState::Death;
}

int Character::getCurrentHealth() const {
    return health;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

void Character::enterDungeon(sf::Vector2f newInsidePosition) {
    lastOutsidePosition = newInsidePosition; 
}

void Character::exitDungeon() {
    sprite.setPosition(lastOutsidePosition); // Возвращение на сохранённую позицию
}