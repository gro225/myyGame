#include "../headers/Weapon.hpp"

Weapon::Weapon(int damage, float attackSpeed, const sf::Texture& weaponTexture)
    : damage(damage), attackSpeed(attackSpeed)  {
    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setScale(0.15f, 0.15f);
    
}

void Weapon::draw(sf::RenderTarget& window, const sf::Vector2f& position) {
    weaponSprite.setPosition(position);
    window.draw(weaponSprite);
}

void Weapon::updatePosition(const sf::Vector2f& characterPosition, bool facingRight) {
    if (facingRight) {
        weaponSprite.setPosition(sf::Vector2f(characterPosition.x + 20.f, characterPosition.y + 10.f));
        weaponSprite.setScale(1.5f, 1.5f); 
    } else {
        weaponSprite.setPosition(sf::Vector2(characterPosition.x - 20.f, characterPosition.y + 10.f));
        weaponSprite.setScale(-1.5f, 1.5f); 
    }
}

int Weapon::getDamage() const {
    return damage;
}

float Weapon::getAttackSpeed() const {
    return attackSpeed;
}

sf::Sprite& Weapon::getSprite() {
    return weaponSprite;
}

void Weapon::setGlobalPosition(const sf::Vector2f& position) {
    globalPosition = position;
    weaponSprite.setPosition(globalPosition);
}

sf::Vector2f Weapon::getGlobalPosition() const {
    return globalPosition;
}

void Weapon::updateRenderPosition(float offsetX, float offsetY) {
    weaponSprite.setPosition(sf::Vector2f(globalPosition.x - offsetX, globalPosition.y - offsetY));
    bounds = sprite.getGlobalBounds(); 
}



















// #include "../headers/Weapon.hpp"

// Weapon::Weapon(int damage, float attackSpeed, 
//                const sf::Texture& weaponTexture)
//     :  damage(damage), 
//       attackSpeed(attackSpeed){
// }

// void Weapon::draw(sf::RenderTarget& window, const sf::Vector2f& position){
//     // Draw weapon
//     weaponSprite.setPosition(position);
//     window.draw(weaponSprite);

// }

// // void updatePosition(const sf::Vector2f& characterPosition, bool facingRight) {
// //         if (facingRight) {
// //             sprite.setPosition(characterPosition.x + 20.f, characterPosition.y + 10.f);
// //             sprite.setScale(1.5f, 1.5f); // Обычный масштаб
// //         } else {
// //             sprite.setPosition(characterPosition.x - 20.f, characterPosition.y + 10.f);
// //             sprite.setScale(-1.5f, 1.5f); // Отраженный масштаб
// //         }
// // }



// void Weapon::update(float deltaTime) {
//     if (effectPlaying) {
//         effectTime += deltaTime;
//         if (effectTime >= effectAnimationSpeed) {
//             effectTime = 0.0f;
//             effectCurrentFrame++;
//             if (effectCurrentFrame >= effectFrames.size()) {
//                 effectPlaying = false; // Stop the effect animation
//             } else {
//                 effectSprite.setTextureRect(effectFrames[effectCurrentFrame]);
//             }
//         }
//     }
// }

// // oid Weapon::update(float deltaTime) {
// //     if (effectPlaying) {
// //         effectTime += deltaTime;
// //         if (effectTime >= effectAnimationSpeed) {
// //             effectTime = 0.0f;
// //             effectCurrentFrame++;
// //             if (effectCurrentFrame >= effectFrames.size()) {
// //                 effectPlaying = false; // Stop the effect animation
// //             } else {
// //                 effectSprite.setTextureRect(effectFrames[effectCurrentFrame]);
// //             }
// //         }
// //     }
// // }

// int Weapon::getDamage() const {
//     return damage;
// }

// float Weapon::getAttackSpeed() const {
//     return attackSpeed;
// }

// sf::Sprite& Weapon::getSprite() {
//     return weaponSprite;
// }