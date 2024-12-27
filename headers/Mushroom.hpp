// headers/Mushroom.hpp
#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "Monster.hpp"

class Mushroom : public Monster {
public:
    Mushroom (const sf::Texture& texture);
};

#endif // MUSHROOM_HPP