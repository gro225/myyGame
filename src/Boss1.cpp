#include "../headers/Boss1.hpp"


Boss1::Boss1(const sf::Texture& texture)
    : Boss(texture, {
        sf::IntRect(24, 16, 56, 56),
        sf::IntRect(120, 16, 56, 56),
        sf::IntRect(216, 16, 56, 56),
        sf::IntRect(312, 16, 56, 56),
        sf::IntRect(408, 16, 56, 56)
    },{
        sf::IntRect(24, 112, 56, 56),
        sf::IntRect(120, 112, 56, 56),
        sf::IntRect(216, 112, 56, 56),
        sf::IntRect(312, 112, 56, 56),
        sf::IntRect(408, 112, 56, 56),
        sf::IntRect(504, 112, 56, 56),
        sf::IntRect(600, 112, 56, 56), 
        sf::IntRect(696, 112, 56, 56)
    },{
        sf::IntRect(56, 208, 48, 48),
        sf::IntRect(200, 208, 48, 48), 
        sf::IntRect(352, 208, 48, 48),
        sf::IntRect(496, 208, 48, 48), 
        sf::IntRect(648, 208, 48, 48), 
        sf::IntRect(800, 208, 48, 48),
        sf::IntRect(960, 208, 48, 48), 
        sf::IntRect(1112, 208, 48, 48), 
        // sf::IntRect(960, 208, 48, 48),
        // sf::IntRect(800, 208, 48, 48),
        // sf::IntRect(648, 208, 48, 48),
        // sf::IntRect(496, 208, 48, 48),
        // sf::IntRect(352, 208, 48, 48),
        // sf::IntRect(200, 208, 48, 48),
        // sf::IntRect(56, 208, 48, 48)
        },{
        sf::IntRect(56, 368, 48, 48),
        sf::IntRect(200, 368, 48, 48),
        sf::IntRect(360, 368, 48, 48), 
        sf::IntRect(512, 368, 48, 48)
        },{ 
        sf::IntRect(56, 520, 48, 48), 
        sf::IntRect(216, 520, 48, 48),
        sf::IntRect(344, 520,48, 48), 
        sf::IntRect(496, 520, 48, 48)
        }, 0.1f) {}
