// Mushroom.cpp
#include "../headers/Mushroom.hpp"

Mushroom::Mushroom(const sf::Texture& texture)
    : Monster(texture, {
        sf::IntRect(56, 64, 40, 40),
        sf::IntRect(208, 64, 40, 40),
        sf::IntRect(360, 64, 40, 40),
        sf::IntRect(504, 64, 40, 40)
    }, {
        sf::IntRect(56, 208, 40, 56),
        sf::IntRect(208, 208, 32, 56),
        sf::IntRect(368, 208, 32, 56),
        sf::IntRect(520, 208, 40, 56),
        sf::IntRect(664, 208, 32, 56),
        sf::IntRect(816, 208, 40, 56),
        sf::IntRect(968, 208, 96, 56),
        sf::IntRect(1112, 208, 88, 56)
    },{
        sf::IntRect(56, 208, 40, 56),
        sf::IntRect(208, 208, 32, 56),
        sf::IntRect(368, 208, 32, 56),
        sf::IntRect(520, 208, 40, 56),
        sf::IntRect(664, 208, 32, 56),
        sf::IntRect(816, 208, 40, 56),
        sf::IntRect(968, 208, 96, 56),
        sf::IntRect(1112, 208, 88, 56)
    },{
        sf::IntRect(64, 64, 24, 40),
        sf::IntRect(208, 64, 32, 40),
        sf::IntRect(360, 64, 32, 40),
        sf::IntRect(512, 64, 32, 40),
        sf::IntRect(360, 64, 32, 40),
        sf::IntRect(208, 64, 32, 40)
    },{
        sf::IntRect(64, 64, 24, 40),
        sf::IntRect(208, 64, 32, 40),
        sf::IntRect(360, 64, 32, 40),
        sf::IntRect(512, 64, 32, 40),
        sf::IntRect(360, 64, 32, 40),
        sf::IntRect(208, 64, 32, 40)
    }, 0.1f) {}