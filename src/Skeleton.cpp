#include "../headers/Skeleton.hpp"

Skeleton::Skeleton(const sf::Texture& texture)
    : Monster(texture, {
        sf::IntRect(56, 32, 56, 72),
        sf::IntRect(208, 32, 56, 72),
        sf::IntRect(360, 32, 56, 72),
        sf::IntRect(504, 32, 56, 72)
    }, {
        sf::IntRect(56, 184, 56, 72),
        sf::IntRect(208, 184, 56, 72),
        sf::IntRect(360, 184, 56, 72),
        sf::IntRect(504, 184, 56, 72)
    },{
        sf::IntRect(56, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(512, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56)
    },{
        sf::IntRect(56, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(512, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56)
    },{
        sf::IntRect(56, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(512, 48, 56, 56),
        sf::IntRect(360, 48, 56, 56),
        sf::IntRect(208, 48, 56, 56)
    },0.1f) {}