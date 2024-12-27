#include "../headers/Game.hpp"


int dungeonCounter = 0;
sf::Vector2f dungeonEntryPoint;

sf::Vector2f getRandomPositionNearCharacter(const Character& character, float radius) {
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2 * 3.14159f; // Случайный угол
    float distance = static_cast<float>(std::rand()) / RAND_MAX * radius; // Случайное расстояние в пределах радиуса

    float x = character.getPosition().x + distance * std::cos(angle);
    float y = character.getPosition().y + distance * std::sin(angle);

    return sf::Vector2f(x, y);
}

Game::Game(int windowWidth, int windowHeight)
    : window(sf::VideoMode(windowWidth, windowHeight), "Game"),
      character(characterTexture, {sf::IntRect(0, 0, 32, 32),sf::IntRect(32,0, 32, 32),sf::IntRect(64, 0, 32, 32),sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32),sf::IntRect(160, 0, 32, 32)},{sf::IntRect(0, 0, 32, 32),sf::IntRect(0,128, 32, 32),sf::IntRect(32, 0, 32, 32),sf::IntRect(32, 128, 32, 32), sf::IntRect(64, 0, 32, 32),sf::IntRect(64, 128, 32, 32), sf::IntRect(96, 0, 32, 32),sf::IntRect(96, 128, 32, 32),sf::IntRect(128, 0, 32, 32),sf::IntRect(128, 128, 32, 32),sf::IntRect(160, 0, 32, 32),sf::IntRect(160, 128, 32, 32)}, {sf::IntRect(0, 32 * 7, 32, 32),sf::IntRect(32,32 * 7, 32, 32),sf::IntRect(64, 32 * 7, 32, 32),sf::IntRect(96, 32 * 7, 32, 32), sf::IntRect(128, 32 * 7, 32, 32),sf::IntRect(160, 32 * 7, 32, 32),},{sf::IntRect(0, 32 * 6, 32, 32),sf::IntRect(32,32 * 6, 32, 32),sf::IntRect(64, 32 * 6, 32, 32),sf::IntRect(96, 32 * 6, 32, 32)},{sf::IntRect(0, 32 * 5, 32, 32),sf::IntRect(32,32 * 5, 32, 32),sf::IntRect(64, 32 * 5, 32, 32),sf::IntRect(96, 32 * 5, 32, 32), sf::IntRect(128, 32 * 5, 32, 32),sf::IntRect(160, 32 * 5, 32, 32),sf::IntRect(196, 32 * 5, 32, 32),sf::IntRect(224,32 * 5, 32, 32),sf::IntRect(256, 32 * 5, 32, 32),sf::IntRect(288, 32 * 5, 32, 32)}, 0.2f),
      gameMap(800, 600, 32, mapTexture), playerUI(120,120){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    loadTextures();
    initialize();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void Game::loadTextures() {
    if (!characterTexture.loadFromFile("../resources/satiro-Sheet v1.1.png") ||
        !mapTexture.loadFromFile("../resources/zeo254-completed-commission.png") ||
        !eyeTexture.loadFromFile("../resources/Monsters/eye.png") ||
        !goblinTexture.loadFromFile("../resources/Monsters/goblin.png") ||
        !mushroomTexture.loadFromFile("../resources/Monsters/mushroom.png") ||
        !skeletonTexture.loadFromFile("../resources/Monsters/skeleton.png") ||
		!dungeon.loadFromFile("../resources/spr_cave.png") ||
        !boss1.loadFromFile("../resources/Boss1/Minotaur - Sprite Sheet.png") ||
        !boss2.loadFromFile("../resources/Boss2/PNG sheet/Character_sheet.png") ||
        !boss3.loadFromFile("../resources/Boss3/png/idle.png") ||
        !weapon1Texture.loadFromFile("../resources/Weapons/sprites/sword 1.png") ||
        !weapon2Texture.loadFromFile("../resources/Weapons/sprites/sword 2.png") ||
        !weapon3Texture.loadFromFile("../resources/Weapons/sprites/sword 4.png") ||
        !weapon4Texture.loadFromFile("../resources/Weapons/sprites/mace 1.png")) {
        throw std::runtime_error("Failed to load textures");
    }
}

void Game::initialize() {
    character.sprite.setScale(2.0f, 2.0f);
    UI playerUI(windowWidth, windowHeight);

	 // Генерация подземелий
     if (dungeons.empty()) {
        for (int i = 0; i < 3; ++i) {
            sf::Vector2f dungeonPosition = sf::Vector2f(
                std::rand() % (windowWidth - 100),
                std::rand() % (windowHeight - 100)
            );
            dungeons.emplace_back(std::make_unique<Dungeon>(
            dungeon, dungeonPosition, sf::IntRect(16 * 8, 42 * 8, 12 * 8, 18 * 8)));
        }
    }

    for (int i = 0; i < 5; ++i) {
        spawnMonster();
        monsters.back()->setPosition(getRandomPositionNearCharacter(character, 300.0f));
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    if (!inDungeon) {
        // Обновляем персонажа
        character.update(deltaTime, gameMap, windowWidth, windowHeight);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            for (auto it = weaponsOnMap.begin(); it != weaponsOnMap.end(); ) {
                if (character.getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())) {
                    std::unique_ptr<Weapon> droppedWeapon = character.equipWeapon(std::move(*it));
                    playerUI.updateWeaponSprite(character.getWeaponSprite());
                    it = weaponsOnMap.erase(it);
                    if (droppedWeapon) {
                        droppedWeapon->getSprite().setPosition(character.getSprite().getPosition());
                        weaponsOnMap.push_back(std::move(droppedWeapon));
                    }
                    break;}
                else {++it;}
            }
        }

        // Проверяем взаимодействие персонажа с подземельями
        for (const auto& dungeon : dungeons) {
            if (character.sprite.getGlobalBounds().intersects(dungeon->getBounds())) {
                if(dungeon->getVisible()){
                    enterDungeon();
                }
                break;
            }
        }

        // Обновляем монстров
        for (auto it = monsters.begin(); it != monsters.end(); ) {
            (*it)->update(deltaTime, gameMap, windowWidth, windowHeight, character.getPosition());
            character.checkCollisionWith(**it, deltaTime);
            if (character.isDead()){
                showEndGameScreen();
                return;
            }

            if ((*it)->isDead()) {
                dropWeapon((*it)->getPosition());
                it = monsters.erase(it);
                spawnMonster();
            }
            else ++it;
        }

        for (auto& dungeon : dungeons) {
            dungeon->updateRenderPosition(gameMap.offsetX, gameMap.offsetY);
        }
        // for (auto& monster : monsters) {
        //     monster->update(monster->getGlobalPosition());
        // }
        // for (auto& weapon : weapons) {
        //     weapon->updateRenderPosition(gameMap.offsetX, gameMap.offsetY);
        // }
        // for (auto& boss : bosses) {
        //     boss->updateRenderPosition(gameMap.offsetX, gameMap.offsetY);
        // }
    } 
    else {
        // Обновление персонажа в подземелье
        character.update(deltaTime, gameMap, windowWidth, windowHeight);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            for (auto it = weaponsOnMap.begin(); it != weaponsOnMap.end(); /* пусто */) {
                if (character.getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())) {
                    std::unique_ptr<Weapon> droppedWeapon = character.equipWeapon(std::move(*it));
                    it = weaponsOnMap.erase(it);
                    if (droppedWeapon) {
                        droppedWeapon->getSprite().setPosition(character.getSprite().getPosition());
                        weaponsOnMap.push_back(std::move(droppedWeapon));
                    }
                    break;}
                else {++it;}
            }
        }
        


        // Обновляем монстров
        for (auto it = monsters.begin(); it != monsters.end(); ) {
            (*it)->update(deltaTime, gameMap, windowWidth, windowHeight, character.getPosition());
            character.checkCollisionWith(**it, deltaTime);
            if (character.isDead()){
                showEndGameScreen();
                return;
            }

            if ((*it)->isDead()) {
                dropWeapon((*it)->getPosition());
                it = monsters.erase(it);
                spawnMonster();
            } 
            else ++it;
            
        }

        //Обновляем Босса
        for (auto it = bosses.begin(); it != bosses.end(); ) {
            (*it)->update(deltaTime, gameMap, windowWidth, windowHeight, character.getPosition());
            character.checkCollisionWithBoss(**it, deltaTime);

            if (character.isDead()){
                showEndGameScreen();
                return;
            }

            if ((*it)->isDead()) {
                it = bosses.erase(it);
                exitDungeon();
            } 
            else ++it;
            
        }
        // for (auto& monster : monsters) {
        //     monster->update(monster->getGlobalPosition());
        // }
        // for (auto& weapon : weapons) {
        //     weapon->updateRenderPosition(gameMap.offsetX, gameMap.offsetY);
        // }
        // for (auto& boss : bosses) {
        //     boss->updateRenderPosition(gameMap.offsetX, gameMap.offsetY);
        // }
        
    }
}


void Game::render() {
    window.clear();
    gameMap.draw(window);
    character.draw(window);
    // currentWeapon.draw(window);
    for (const auto& weapon : weaponsOnMap) {
    window.draw(weapon->getSprite());
    }


	 for (const auto& dungeon : dungeons) {
        dungeon->draw(window);
    }

    for (const auto& monster : monsters) {
        monster->draw(window);
    }

    for (const auto& boss : bosses) {
        boss->draw(window);
    }
    playerUI.draw(window);
    window.display();
}

void Game::enterDungeon() {
    inDungeon = true;
    monsters.clear();
    dungeonCounter++;

    for (const auto& dungeon : dungeons) {
        if (character.sprite.getGlobalBounds().intersects(dungeon->getBounds())) {
            dungeonEntryPoint = dungeon->getBounds().getPosition();
            break;
        }
    }

    for (auto& dungeon : dungeons) {
        dungeon->setVisible(false);
    }

    std::string dungeonTexturePath;
    switch (dungeonCounter) {
        case 1: dungeonTexturePath = "../resources/Dungeons/dungeon1.png"; break;
        case 2: dungeonTexturePath = "../resources/Dungeons/dungeon2.png"; break;
        case 3: dungeonTexturePath = "../resources/Dungeons/dungeon3.png"; break;
        default: 
            showVictoryScreen();
            return;
    }
    gameMap.loadDungeonTexture(dungeonTexturePath);
    character.setPosition(sf::Vector2f(200.0f, 200.0f));
    for (int i = 0; i < 5; ++i) {
        spawnMonster();
        monsters.back()->setPosition(getRandomPositionNearCharacter(character, 150.0f));
    }
    spawnBoss();
    bosses.back()->setPosition(getRandomPositionNearCharacter(character, 150.0f));
}

void Game::exitDungeon() {
    inDungeon = false;
    gameMap.setStateOfDangeon(false);
    monsters.clear();
    gameMap.draw(window);
    for (auto& dungeon : dungeons) {
        if (dungeon->getBounds().getPosition() == dungeonEntryPoint) {
            dungeon->setVisible(false); 
            dungeon->setCompleted(true);
        } else if (!dungeon->getCompleted()){
            dungeon->setVisible(true);
        }
    }
    if (dungeonCounter == 3){
        showVictoryScreen();
        return;
    }

    initialize();
        
}

void Game::spawnMonster() {
    int type = rand() % 4; 
    sf::Vector2f monsterPosition = getRandomPositionNearCharacter(character, 150.0f);

    switch (type) {
        case 0: monsters.emplace_back(std::make_unique<Eye>(eyeTexture)); break;
        case 1: monsters.emplace_back(std::make_unique<Goblin>(goblinTexture)); break;
        case 2: monsters.emplace_back(std::make_unique<Mushroom>(mushroomTexture)); break;
        case 3: monsters.emplace_back(std::make_unique<Skeleton>(skeletonTexture)); break;
    }

    monsters.back()->setPosition(monsterPosition);
}

void Game::spawnBoss() {
    sf::Vector2f bossPosition(400.0f, 300.0f);

    switch (dungeonCounter) {
        case 1: 
            bosses.emplace_back(std::make_unique<Boss1>(boss1));
            bosses.back()->setPosition(bossPosition);
            break;
        case 2: 
            bosses.emplace_back(std::make_unique<Boss2>(boss2));
            bosses.back()->setPosition(bossPosition);
            break;
        case 3: 
            bosses.emplace_back(std::make_unique<Boss3>(boss3));
            bosses.back()->setPosition(bossPosition);
            break;
    }
}

void Game::dropWeapon(const sf::Vector2f& position) {
    if (rand() % 100 < 10) { 
        int type = rand() % 4; 
        switch (type) {
            case 0: weaponsOnMap.emplace_back(std::make_unique<Weapon>(25,20.f,weapon1Texture));break;
            case 1: weaponsOnMap.emplace_back(std::make_unique<Weapon>(25,20.f,weapon2Texture)); break;
            case 2: weaponsOnMap.emplace_back(std::make_unique<Weapon>(25,20.f,weapon3Texture)); break;
            case 3: weaponsOnMap.emplace_back(std::make_unique<Weapon>(25,20.f,weapon4Texture)); break;
        }

        weaponsOnMap.back()->getSprite().setPosition(position);
    }
}

void Game::showVictoryScreen() {
     sf::Texture texture;
    if (!texture.loadFromFile("../resources/Win.jpg")) {
        throw std::runtime_error("Failed to load font");
    }
    // // Создаем спрайт с текстурой
    sf::Sprite sprite(texture);

    // Масштабируем картинку под размер окна
    float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
    sprite.setScale(sf::Vector2<float>(scaleX, scaleY));
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
    }
}


void Game::showEndGameScreen() {
    sf::Texture texture;
    if (!texture.loadFromFile("../resources/gameOver.jpeg")) {
        throw std::runtime_error("Failed to load font");
    }
    sf::Sprite sprite(texture);

    // Масштабируем под размер окна
    float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
    sprite.setScale(sf::Vector2<float>(scaleX, scaleY));
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
    }
}



