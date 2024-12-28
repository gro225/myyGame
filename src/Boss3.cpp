#include "../headers/Boss3.hpp"


Boss3::Boss3(const sf::Texture& texture)
    : Boss(texture, {
        sf::IntRect(16, 16, 64, 72),
        sf::IntRect(120, 16, 64, 72),
        sf::IntRect(224, 16, 64, 72),
        sf::IntRect(328, 16, 64, 72)
    },{
        sf::IntRect(16, 16, 64, 72),
        sf::IntRect(120, 16, 64, 72),
        sf::IntRect(224, 16, 64, 72),
        sf::IntRect(328, 16, 64, 72)
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