#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP


#include <SFML/Graphics.hpp>
#include "Weapon.hpp"
#include <vector>

class Monster;
class Dungeon;


class GameMap {
public:
    float offsetX = 0.0f; // Смещение по X
    float offsetY = 0.0f; // Смещение по Y

    GameMap(int width, int height, int tileSize,  sf::Texture& texture);

    void draw(sf::RenderWindow& window) const;
    void loadDungeonTexture(const std::string& filePath); // Загрузка текстуры для подземелья
    bool checkCollision(const sf::Sprite& sprite) const;
    void applyOffset() ;
    std::vector<Weapon>& getDroppedItems();
    void setMonsters(std::vector<std::unique_ptr<Monster>> monsters);

    void setDungeons(std::vector<std::unique_ptr<Dungeon>> dungeons);
    
    void setStateOfDangeon(bool state);

    bool checkCollision(const sf::Vector2f& nextPosition);

    sf::Image getImage() const;

    

private:
    int width, height, tileSize;
    std::vector<std::vector<int>> mapData;
    sf::Texture& texture;

    sf::Texture islandTexture;
    sf::Texture dungeonTexture; // Текстура подземелья
    sf::Sprite dungeonSprite;   // Спрайт для отображения подземелья
    sf::Image mapImage;
    bool isDungeon = false;     // Флаг для определения режима карты

    std::vector<std::unique_ptr<Dungeon>> dungeons;
    std::vector<std::unique_ptr<Monster>> monsters;
};

#endif // GAMEMAP_HPP












// #ifndef GAMEMAP_HPP
// #define GAMEMAP_HPP

// #include <SFML/Graphics.hpp>
// #include <vector>

// class GameMap {
// public:
//     float offsetX = 0.0f; // Смещение по X
//     float offsetY = 0.0f; // Смещение по Y
//     GameMap(int width, int height, int tileSize, const sf::Texture& texture);
//     void draw(sf::RenderWindow& window) const;
//     bool checkCollision(const sf::Sprite& sprite) const;

// private:
//     int width, height, tileSize;
//     std::vector<std::vector<int>> mapData;
//     const sf::Texture& texture;
// };

// #endif // GAMEMAP_HPP