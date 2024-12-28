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
    
    void setStateOfDangeon(bool state);

    bool checkCollision(const sf::Vector2f& nextPosition);

    sf::Image getImage() const;

    

private:
    int width, height, tileSize;
    std::vector<std::vector<int>> mapData;
    sf::Texture& texture;

    sf::Texture islandTexture;
    sf::Texture dungeonTexture; 
    sf::Sprite dungeonSprite;  
    sf::Image mapImage;
    bool isDungeon = false;     

    std::vector<std::unique_ptr<Dungeon>> dungeons;
    std::vector<std::unique_ptr<Monster>> monsters;
};

#endif // GAMEMAP_HPP

