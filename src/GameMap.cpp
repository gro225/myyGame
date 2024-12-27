#include "../headers/GameMap.hpp"
#include "../headers/Monster.hpp"
#include "../headers/Dungeon.hpp"

#include <stdexcept>

GameMap::GameMap(int width, int height, int tileSize,  sf::Texture& texture)
    : width(width), height(height), tileSize(tileSize), texture(texture) {
    mapData.resize(height, std::vector<int>(width, 0));

    // Генерация карты острова 
    for (int x = 0; x < width; ++x) {
        mapData[0][x] = 1;
        mapData[height - 1][x] = 1;
    }
    for (int y = 0; y < height; ++y) {
        mapData[y][0] = 1;
        mapData[y][width - 1] = 1;
    }
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            mapData[y][x] = 0;
        }
    }
    if (!islandTexture.loadFromFile("../resources/zeo254-completed-commission.png")) {
        throw std::runtime_error("Failed to load dungeon texture from file: ");
    }
    mapImage = islandTexture.copyToImage();
}

void GameMap::loadDungeonTexture(const std::string& filePath) {
    if (!dungeonTexture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load dungeon texture from file: " + filePath);
    }
    dungeonSprite.setTexture(dungeonTexture);
    mapImage = dungeonTexture.copyToImage();
    isDungeon = true; 
    int imageWidth = dungeonTexture.getSize().x;
    int imageHeight = dungeonTexture.getSize().y;

    width = imageWidth / tileSize;
    height = imageHeight / tileSize;

    mapData.resize(height, std::vector<int>(width, 0));
}

void GameMap::draw(sf::RenderWindow& window) const {
    if (isDungeon) {
        // Разбиваем dungeonSprite на тайлы и смещаем 
        sf::Sprite sprite(dungeonTexture);

        int dungeonWidth = dungeonTexture.getSize().x / tileSize;
        int dungeonHeight = dungeonTexture.getSize().y / tileSize;

        for (int y = 0; y < dungeonHeight; ++y) {
            for (int x = 0; x < dungeonWidth; ++x) {
                sprite.setTextureRect(sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
                sprite.setPosition(x * tileSize - offsetX, y * tileSize - offsetY);

                // Рисуем только видимые тайлы
                if (sprite.getPosition().x + tileSize > 0 && sprite.getPosition().x < window.getSize().x &&
                    sprite.getPosition().y + tileSize > 0 && sprite.getPosition().y < window.getSize().y) {
                    window.draw(sprite);
                }
            }
        }
    } else {
        sf::Sprite sprite(islandTexture);
        int startX = std::max(0, static_cast<int>(offsetX / tileSize));
        int startY = std::max(0, static_cast<int>(offsetY / tileSize));
        int endX = std::min(width, static_cast<int>((offsetX + window.getSize().x) / tileSize + 1));
        int endY = std::min(height, static_cast<int>((offsetY + window.getSize().y) / tileSize + 1));

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                sprite.setPosition(x * tileSize - offsetX, y * tileSize - offsetY);

                switch (mapData[y][x]) {
                    case 0: // Проходимая клетка
                        sprite.setTextureRect(sf::IntRect(56, 0, 16, 16));
                        sprite.setScale(4.0f, 4.0f);
                        window.draw(sprite);
                        break;
                    case 1: // Непроходимая клетка
                        sprite.setTextureRect(sf::IntRect(80, 80, 16, 16));
                        sprite.setScale(4.0f, 4.0f);
                        window.draw(sprite);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void GameMap::setStateOfDangeon(bool state){
    isDungeon = state;

}

bool GameMap::checkCollision(const sf::Vector2f& nextPosition) {
    int pixelX = static_cast<int>(nextPosition.x);
    int pixelY = static_cast<int>(nextPosition.y);


    sf::Color pixelColor = mapImage.getPixel(pixelX, pixelY);
//pixelColor == sf::Color(139, 69, 19) || pixelColor == sf::Color(192, 5, 248)
    
        if (pixelColor == sf::Color::Black) {
            return true;
        }

    return false;
}

sf::Image GameMap::getImage() const{
    return mapImage;
}

// void GameMap::applyOffset() {
//     for (auto& monster : monsters) {
//         monster->setPosition(sf::Vector2f(monster->getPosition().x - offsetX, monster->getPosition().y - offsetY));
//     }

//     for (auto& dungeon : dungeons) {
//         dungeon->setPosition(sf::Vector2f(dungeon->getPosition().x - offsetX, dungeon->getPosition().y - offsetY));
//     }
// }

// void GameMap::setMonsters(std::vector<std::unique_ptr<Monster>> monsters) {
//     this->monsters = monsters;
// }

// void GameMap::setDungeons(std::vector<std::unique_ptr<Dungeon>> dungeons) {
//     this->dungeons = dungeons;
// }