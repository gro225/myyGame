#ifndef EYE_HPP
#define EYE_HPP

#include "Monster.hpp"

class Eye : public Monster {
public:
    Eye(const sf::Texture& texture);
    // void update(float deltaTime, GameMap& gameMap, int windowWidth, int windowHeight) override;
};

#endif //EYE_HPP
