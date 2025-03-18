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
    void loadDungeonTexture(const std::string& filePath); 
    bool checkCollision(const sf::Sprite& sprite) const;
    void applyOffset() ;
    std::vector<Weapon>& getDroppedItems();
    void setMonsters(std::vector<std::unique_ptr<Monster>> monsters);

    void setDungeons(std::vector<std::unique_ptr<Dungeon>> dungeons);
    
    void  setStateOfDungeon(bool state);

    bool checkCollision(const sf::Vector2f& nextPosition, const sf::Vector2f& size);
    bool canSpawnMonster(int x, int y);

    sf::Color getPixelColorAtPosition(const sf::Vector2f& position);
    int getWidth() const ;
    int getHeight() const ;
    int getTileSize() const;
    

    sf::Image getImage() const;

    void resetToIsland();
    const sf::Sprite& getBackgroundSprite() const;

    

private:
    int width, height, tileSize;
    std::vector<std::vector<int>> mapData;
    std::vector<std::vector<int>> collisionMap;
    std::vector<std::vector<bool>> spawnMap;
    sf::Texture& texture;

    sf::Texture islandTexture;
    sf::Texture dungeonTexture; 
    sf::Sprite dungeonSprite;
    sf::Sprite backgroundSprite;
    sf::Image mapImage;
    sf::Texture backgroundTexture;
    sf::Image backgroundImage;

    bool isDungeon = false;     

    std::vector<std::unique_ptr<Dungeon>> dungeons;
    std::vector<std::unique_ptr<Monster>> monsters;
};

#endif // GAMEMAP_HPP

