#include "../headers/Character.hpp"
#include "../headers/Game.hpp"
#include <iostream>
// #include "../headers/GameMap.hpp"
// #include "../headers/Monster.hpp"



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
    handleInput(deltaTime, gameMap, windowWidth, windowHeight);

    switch (currentAnimation) {
        case AnimationState::Idle:
            idleAnimation.update(deltaTime);
            break;
        case AnimationState::Walk:
            walkAnimation.update(deltaTime);
            break;
        case AnimationState::Attack:
            attackAnimation.update(deltaTime);
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
    target.draw(sprite); // Отрисовка персонажа
    if (currentWeapon) {
        currentWeapon->draw(target,sf::Vector2f(sprite.getPosition().x+20.f,sprite.getPosition().y+10.f)); // Отрисовка оружия
    }
}



void Character::handleInput(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight) {
    if (currentAnimation == AnimationState::Death || currentAnimation == AnimationState::Hit) return;

    float moveX = 0.f, moveY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveX = -moveSpeed * deltaTime;
        sprite.setScale(-2.0f, 2.0f);
        sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width, 0)); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveX = moveSpeed * deltaTime;
        sprite.setScale(2.0f, 2.0f);
        sprite.setOrigin(0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveY = -moveSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveY = moveSpeed * deltaTime;
    }

    if (moveX != 0.f || moveY != 0.f) {
        if (currentAnimation != AnimationState::Walk) {
            currentAnimation = AnimationState::Walk;
        }
        sprite.move(moveX, moveY);
    } else {
        currentAnimation = AnimationState::Idle;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentAnimation != AnimationState::Attack) {
        currentAnimation = AnimationState::Attack;
    }

    // //Рассчитываем новую позицию
    // sf::Vector2f nextPosition = sprite.getPosition() + sf::Vector2f(1.f, 1.f);

    // if (!checkCollisionWithMap(gameMap , nextPosition)) {
    //     sprite.move(sf::Vector2<float>(moveX, moveY));
    // }


    // По вертикали смещение
if (sprite.getPosition().y < OFFSET_THRESHOLD) {
    gameMap.offsetY += moveY; // Обновляем смещение карты
    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, OFFSET_THRESHOLD)); // Откатить персонажа
    for (auto& dungeon : dungeons) {
        dungeon->setGlobalPosition(sf::Vector2f(dungeon->getGlobalPosition().x, dungeon->getGlobalPosition().y + moveY));
    }
    // for (auto& monster : monsters) {
    //     monster->setPosition(sf::Vector2f(monster->getPosition().x, OFFSET_THRESHOLD)); // Откатить монстра
    // }
    // for (auto& weapon : weapons) {
    //     weapon->setGlobalPosition(sf::Vector2f(weapon->getGlobalPosition().x, weapon->getGlobalPosition().y + moveY));
    // }
} else if (sprite.getPosition().y > windowHeight - OFFSET_THRESHOLD - sprite.getGlobalBounds().height) {
    gameMap.offsetY += moveY; // Обновляем смещение карты
    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, windowHeight - OFFSET_THRESHOLD - sprite.getGlobalBounds().height)); // Откатить персонажа
    for (auto& dungeon : dungeons) {
        dungeon->setGlobalPosition(sf::Vector2f(dungeon->getGlobalPosition().x, dungeon->getGlobalPosition().y + moveY));
    }
    // for (auto& monster : monsters) {
    //     monster->setPosition(sf::Vector2f(monster->getPosition().x, windowHeight - OFFSET_THRESHOLD - monster->getGlobalBounds().height)); // Откатить монстра
    // }
    // for (auto& weapon : weapons) {
    //     weapon->setGlobalPosition(sf::Vector2f(weapon->getGlobalPosition().x, weapon->getGlobalPosition().y + moveY));
    // }
}



    // По горизонтали смещение
if (sprite.getPosition().x < OFFSET_THRESHOLD) {
    gameMap.offsetX += moveX; // Обновляем смещение карты
    sprite.setPosition(sf::Vector2f(OFFSET_THRESHOLD, sprite.getPosition().y)); // Откатить персонажа
    for (auto& dungeon : dungeons) {
        dungeon->setGlobalPosition(sf::Vector2f(dungeon->getGlobalPosition().x + moveX, dungeon->getGlobalPosition().y));
    }
    // for (auto& monster : monsters) {
    //     monster->setPosition(sf::Vector2f(OFFSET_THRESHOLD, monster->getPosition().y)); // Откатить монстра
    // }
    // for (auto& weapon : weapons) {
    //     weapon->setGlobalPosition(sf::Vector2f(weapon->getGlobalPosition().x + moveX, weapon->getGlobalPosition().y));
    // }
} else if (sprite.getPosition().x > windowWidth - OFFSET_THRESHOLD - sprite.getGlobalBounds().width) {
    gameMap.offsetX += moveX; 
    sprite.setPosition(sf::Vector2f(windowWidth - OFFSET_THRESHOLD - sprite.getGlobalBounds().width, sprite.getPosition().y)); // Откатить персонажа
    for (auto& dungeon : dungeons) {
        dungeon->setGlobalPosition(sf::Vector2f(dungeon->getGlobalPosition().x + moveX, dungeon->getGlobalPosition().y));
    }
    //  for (auto& monster : monsters) {
    //     monster->setPosition(sf::Vector2f(windowWidth - OFFSET_THRESHOLD - monster->getGlobalBounds().width, monster->getPosition().y)); // Откатить монстра
    // }
    // for (auto& weapon : weapons) {
    //     weapon->setGlobalPosition(sf::Vector2f(weapon->getGlobalPosition().x + moveX, weapon->getGlobalPosition().y));
    // }
}


}

bool Character::checkCollisionWithMap(GameMap& map, const sf::Vector2f& nextPosition) {
    return map.checkCollision(nextPosition);
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
    health -= damage;
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





























// #include "../headers/Character.hpp"
// #include "../headers/GameMap.hpp"

// Character::Character(const sf::Texture& texture, const sf::IntRect& rect)
//     : Entity(texture, rect), animation(sprite, sf::Vector2i(32, 32), 0.1f) {
//     sprite.setScale(2.0f, 2.0f);
// }

// void Character::update(float deltaTime, GameMap& gameMap,  int windowWidth, int windowHeight) { 
//     input.handleInput(*this, deltaTime, gameMap, windowWidth, windowHeight);
//     animation.update(sf::seconds(deltaTime));
// }

// void Character::move(float offsetX, float offsetY) {
//     sprite.move(sf::Vector2f(offsetX, offsetY));
// }

// sf::Vector2f Character::getPosition() const {
//     return sprite.getPosition(); // Возвращаем текущую позицию спрайта
// }

// // Character::MoveAnimation::MoveAnimation(sf::Sprite& sprite, sf::Vector2i frameSize, float frameDuration)
// //     : sprite(sprite), frameSize(frameSize), frameDuration(frameDuration), currentFrame(0), frameTime(0.0f) {}

// // void Character::MoveAnimation::update(sf::Time deltaTime) {
// //     frameTime += deltaTime.asSeconds();
// //     if (frameTime >= frameDuration) {
// //         currentFrame = (currentFrame + 1) % 6;
// //         sf::IntRect rect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y);
// //         sprite.setTextureRect(rect);
// //         frameTime = 0.0f;
// //     }
// // }

// void Character::KeyboardInput::handleInput(Character& character, float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight) {
//     float moveX = 0.0f;
//     float moveY = 0.0f;

//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//         moveX = -100.0f * deltaTime;
//         character.sprite.setScale(-2.0f, 2.0f);
//         character.sprite.setOrigin(sf::Vector2f(character.sprite.getLocalBounds().width, 0)); 
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//         moveX = 100.0f * deltaTime;
//         character.sprite.setScale(2.0f, 2.0f);
//         character.sprite.setOrigin(0, 0);
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//         moveY = -100.0f * deltaTime;
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//         moveY = 100.0f * deltaTime;
//     }

//     // Применяем движение
//     character.sprite.move(sf::Vector2f(moveX, moveY));

//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//         //Играем анимацию атаки

//     }


//     // Проверяем столкновение
//     // if (gameMap.checkCollision(character.sprite)) {
//         // Если произошло столкновение, откатить движение
//         // character.sprite.move(sf::Vector2f(-moveX, -moveY));
//     //     character.sprite.move(-moveX, -moveY);
//     // }
//     // Проверяем выход за пределы окна
//     // Проверяем выход за пределы окна и обновляем смещение карты
    
//     if (character.sprite.getPosition().x < OFFSET_THRESHOLD) {
//         gameMap.offsetX += moveX; // Обновляем смещение карты
//         character.sprite.setPosition(sf::Vector2f(OFFSET_THRESHOLD, character.sprite.getPosition().y)); // Откатить персонажа
//     } else if (character.sprite.getPosition().x > windowWidth - OFFSET_THRESHOLD - character.sprite.getGlobalBounds().width) {
//         gameMap.offsetX += moveX; // Обновляем смещение карты
//         character.sprite.setPosition(sf::Vector2f(windowWidth - OFFSET_THRESHOLD - character.sprite.getGlobalBounds().width, character.sprite.getPosition().y)); // Откатить персонажа
//     }

//     if (character.sprite.getPosition().y < OFFSET_THRESHOLD) {
//         gameMap.offsetY += moveY; // Обновляем смещение карты
//         character.sprite.setPosition(sf::Vector2f(character.sprite.getPosition().x, OFFSET_THRESHOLD)); // Откатить персонажа
//     } else if (character.sprite.getPosition().y > windowHeight - OFFSET_THRESHOLD - character.sprite.getGlobalBounds().height) {
//         gameMap.offsetY += moveY; // Обновляем смещение карты
//         character.sprite.setPosition(sf::Vector2f(character.sprite.getPosition().x, windowHeight - OFFSET_THRESHOLD - character.sprite.getGlobalBounds().height)); // Откатить персонажа
//     }
// }