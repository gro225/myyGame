// Goblin.cpp
#include "../headers/Goblin.hpp"

Goblin::Goblin(const sf::Texture& texture)
    : Monster(texture,{
       sf::IntRect(56, 64, 40, 40), 
       sf::IntRect(208, 64, 40, 40), 
       sf::IntRect(352, 64, 40, 40),
       sf::IntRect(504, 64, 40, 40)
    },{
        sf::IntRect(56, 208, 40, 56),
        sf::IntRect(208, 208, 40, 56),
        sf::IntRect(368, 208, 40, 56),
        sf::IntRect(520, 208, 40, 56),
        sf::IntRect(664, 208, 40, 56),
        sf::IntRect(816, 208, 40, 56),
        sf::IntRect(968, 208, 40, 56),
        sf::IntRect(1112, 208, 40, 56)
    },{
        sf::IntRect(56, 64, 40, 40), 
       sf::IntRect(208, 64, 40, 40), 
       sf::IntRect(352, 64, 40, 40),
       sf::IntRect(504, 64, 40, 40)
    },{
        sf::IntRect(56, 64, 400, 56),
        sf::IntRect(208, 64, 400, 56),
        sf::IntRect(360, 64, 400, 56),
        sf::IntRect(504, 64, 400, 56),
        sf::IntRect(656, 64, 400, 56),
        sf::IntRect(808, 64, 400, 56),
        sf::IntRect(928, 48, 400, 56),
        sf::IntRect(1080, 48, 400, 56)
    },{
        sf::IntRect(56, 496, 40, 56),
        sf::IntRect(208, 496, 40, 56),
        sf::IntRect(352, 496, 48, 56),
        sf::IntRect(504, 496, 40, 56)
    } ,0.1f) {}