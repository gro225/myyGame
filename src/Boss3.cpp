#include "../headers/Boss3.hpp"


Boss3::Boss3(const sf::Texture& texture)
    : Boss(texture, {
        sf::IntRect(56, 64, 56, 40),
        sf::IntRect(192, 64, 56, 40),
        sf::IntRect(344, 64, 56, 40),
        sf::IntRect(496, 64, 56, 40),
        sf::IntRect(648, 64, 56, 40),
        sf::IntRect(802, 64, 56, 40),
        sf::IntRect(952, 64, 56, 40), 
        sf::IntRect(1104, 64, 56, 40), 
        sf::IntRect(952, 64, 56, 40),
        sf::IntRect(802, 64, 56, 40), 
        sf::IntRect(648, 64, 56, 40), 
        sf::IntRect(496, 64, 56, 40),
        sf::IntRect(344, 64, 56, 40), 
        sf::IntRect(192, 64, 56, 40)
    },{
        sf::IntRect(56, 64, 56, 40),
        sf::IntRect(192, 64, 56, 40),
        sf::IntRect(344, 64, 56, 40),
        sf::IntRect(496, 64, 56, 40),
        sf::IntRect(648, 64, 56, 40),
        sf::IntRect(802, 64, 56, 40),
        sf::IntRect(952, 64, 56, 40), 
        sf::IntRect(1104, 64, 56, 40), 
        sf::IntRect(952, 64, 56, 40),
        sf::IntRect(802, 64, 56, 40), 
        sf::IntRect(648, 64, 56, 40), 
        sf::IntRect(496, 64, 56, 40),
        sf::IntRect(344, 64, 56, 40), 
        sf::IntRect(192, 64, 56, 40)
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