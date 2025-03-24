#include "../headers/GameMap.hpp"
#include "../headers/Monster.hpp"
#include "../headers/Dungeon.hpp"

#include <stdexcept>

GameMap::GameMap(int width, int height, int tileSize, sf::Texture& texture)
    : width(width), height(height), tileSize(tileSize), texture(texture) {
    mapData.resize(height, std::vector<int>(width, 0));
    collisionMap.resize(height, std::vector<int>(width, 0));
    spawnMap.resize(height, std::vector<bool>(width, true));

    // Генерация границ карты
    for (int x = 0; x < width; ++x) {
        mapData[0][x] = 1;
        mapData[height - 1][x] = 1;
        collisionMap[0][x] = 1;
        collisionMap[height - 1][x] = 1;
    }
    for (int y = 0; y < height; ++y) {
        mapData[y][0] = 1;
        mapData[y][width - 1] = 1;
        collisionMap[y][0] = 1;
        collisionMap[y][width - 1] = 1;
    }
    // Внутренние проходимые клетки
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            mapData[y][x] = 0;
            collisionMap[y][x] = 0;  
            spawnMap[y][x] = true;   
        }
    }

    // Загружаем текстуру острова и получаем её изображение для коллизии
    if (!islandTexture.loadFromFile("../resources/zeo254-completed-commission.png")) {
        throw std::runtime_error("Failed to load island texture");
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
    collisionMap.resize(height, std::vector<int>(width, 0));
    spawnMap.resize(height, std::vector<bool>(width, false));

    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Color tileColor = mapImage.getPixel(x * tileSize, y * tileSize);
            if (tileColor == sf::Color(48, 25, 108)) {
                collisionMap[y][x] = 1;  
            } else {
                collisionMap[y][x] = 0;
            }

            if (tileColor == sf::Color(66, 66, 66) || tileColor == sf::Color(0, 0, 0)) {
                spawnMap[y][x] = true;
            } else {
                spawnMap[y][x] = false;
            }
        }
    }
}

bool GameMap::canSpawnMonster(int x, int y) {
    constexpr int margin = 2;
    
    // Проверяем границы карты
    if (x < margin || y < margin || x >= width - margin || y >= height - margin) {
        return false;
    }

    // Проверяем, свободны ли клетки вокруг
    for (int dx = -margin; dx <= margin; ++dx) {
        for (int dy = -margin; dy <= margin; ++dy) {
            if (dx == 0 && dy == 0) continue; 

            int checkX = x + dx;
            int checkY = y + dy;

            if (checkX >= 0 && checkY >= 0 && checkX < width && checkY < height) {
                if (!spawnMap[checkY][checkX]) {
                    return false; 
                }
            }
        }
    }

    spawnMap[y][x] = false; 

    return true;
}



void GameMap::draw(sf::RenderWindow& window) const {
    if (isDungeon) {
        sf::Sprite sprite(dungeonTexture);
        int dungeonWidth = dungeonTexture.getSize().x / tileSize;
        int dungeonHeight = dungeonTexture.getSize().y / tileSize;
        for (int y = 0; y < dungeonHeight; ++y) {
            for (int x = 0; x < dungeonWidth; ++x) {
                sprite.setTextureRect(sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
                sprite.setPosition(x * tileSize - offsetX, y * tileSize - offsetY);
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
                    case 0:
                        sprite.setTextureRect(sf::IntRect(56, 0, 16, 16));
                        sprite.setScale(4.0f, 4.0f);
                        window.draw(sprite);
                        break;
                    case 1:
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

void GameMap::setStateOfDungeon(bool state){
    isDungeon = state;
}

bool GameMap::checkCollision(const sf::Vector2f& nextPosition, const sf::Vector2f& size) {
   
    sf::Vector2f adjustedPos = nextPosition + sf::Vector2f(offsetX, offsetY);

    

    sf::Vector2f feetPoints[3] = {
        adjustedPos + sf::Vector2f(size.x * 0.3f, size.y - 9.f),
        adjustedPos + sf::Vector2f(size.x * 0.5f, size.y - 9.f),
        adjustedPos + sf::Vector2f(size.x * 0.7f, size.y - 9.f)
    };
    sf::Vector2f headPoints[3] = {
        adjustedPos + sf::Vector2f(size.x * 0.3f, 30.f),
        adjustedPos + sf::Vector2f(size.x * 0.5f, 30.f),
        adjustedPos + sf::Vector2f(size.x * 0.7f, 30.f)
    };

    for (const auto &point : feetPoints) {
        int tileX = static_cast<int>(point.x / 32);
        int tileY = static_cast<int>(point.y / 32);


        if (mapData[tileY][tileX] == 1) { 
            return true;
        }
    }

    for (const auto &point : feetPoints) {
        sf::Color pixelColor = getPixelColorAtPosition(point);
        if (pixelColor == sf::Color(48, 25, 108) ||
            pixelColor == sf::Color(45, 36, 29))
            return true;
    }

    for (const auto &point : headPoints) {
        sf::Color pixelColor = getPixelColorAtPosition(point);
        if (pixelColor == sf::Color(48, 25, 108) ||
            pixelColor == sf::Color(45, 36, 29))
            return true;
    }

    return false;
}

sf::Image GameMap::getImage() const {
    return mapImage;
}

sf::Color GameMap::getPixelColorAtPosition(const sf::Vector2f& position) {
    int pixelX = static_cast<int>(position.x);
    int pixelY = static_cast<int>(position.y);

    if (pixelX < 0 || pixelX >= static_cast<int>(mapImage.getSize().x) ||
        pixelY < 0 || pixelY >= static_cast<int>(mapImage.getSize().y)) {
        return sf::Color::Black;
    }
    return mapImage.getPixel(pixelX, pixelY);
}

void GameMap::resetToIsland() {
    isDungeon = false;
    mapImage = islandTexture.copyToImage();
}

int GameMap::getWidth() const { return width; }
int GameMap::getHeight() const { return height; }
int GameMap::getTileSize() const { return tileSize; }
const sf::Sprite& GameMap::getBackgroundSprite() const{ return backgroundSprite; }
