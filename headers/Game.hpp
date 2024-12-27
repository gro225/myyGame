#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.hpp"
#include "Boss.hpp"
#include "Boss1.hpp"
#include "Boss2.hpp"
#include "Boss3.hpp"
#include "Dungeon.hpp"
#include "GameMap.hpp"
#include "UI.hpp"
#include "Weapon.hpp"
#include "Eye.hpp"
#include "Goblin.hpp"
#include "Mushroom.hpp"
#include "Skeleton.hpp"


class Game {
public:
    Game(int width = 800, int height = 600);
    void run();

private:
    void loadTextures();
    void initialize();
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnMonster();
    void spawnBoss();
    void showEndGameScreen();
    void showVictoryScreen();
    void dropWeapon(const sf::Vector2f& position);

	bool inDungeon = false;
    void enterDungeon();
    void exitDungeon();

    sf::RenderWindow window;
    sf::Clock clock;

    sf::Texture characterTexture;
    sf::Texture mapTexture;
    sf::Texture eyeTexture;
    sf::Texture goblinTexture;
    sf::Texture mushroomTexture;
    sf::Texture skeletonTexture;
    sf::Texture dungeon;
    sf::Texture boss1;
    sf::Texture boss2;
    sf::Texture boss3;
    sf::Texture weapon1Texture;
    sf::Texture weapon2Texture;
    sf::Texture weapon3Texture;
    sf::Texture weapon4Texture;

    

    Character character;
    GameMap gameMap;
    UI playerUI;
    std::vector<std::unique_ptr<Monster>> monsters;
    std::vector<std::unique_ptr<Boss>> bosses;
	std::vector<std::unique_ptr<Dungeon>> dungeons;
    std::vector<std::unique_ptr<Weapon>> weaponsOnMap;


    const int windowWidth = 800;
    const int windowHeight = 600;
    const int mapWidth = 128;
    const int mapHeight = 128;
};
