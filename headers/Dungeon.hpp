#ifndef DUNGEON
#define DUNGEON

#include <SFML/Graphics.hpp>

class Dungeon {
public:
    Dungeon(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect);

    void draw(sf::RenderWindow& window);
    const sf::FloatRect& getBounds() const;
    void setGlobalPosition(const sf::Vector2f& position); 
    sf::Vector2f getGlobalPosition() const;              
    void updateRenderPosition(float offsetX, float offsetY); 
    sf::FloatRect getGlobalBounds() const;
    void setVisible(bool isVisible);
    bool getVisible() const;
    void setCompleted(bool isComleted);
    bool getCompleted() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    sf::FloatRect bounds;
    sf::Vector2f globalPosition;
    bool visible;
    bool completed;
};

#endif // DUNGEON
