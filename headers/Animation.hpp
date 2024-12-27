// headers/Animation.hpp
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

enum class AnimationState {
    Idle,
    Walk,
    Attack,
    Hit,
    Death
};

class Animation {
public:
    Animation(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float frameDuration);

    void update(float deltaTime);
    void updateOnce(float deltaTime);
    void setFrames(const std::vector<sf::IntRect>& newFrames);
    void setCurrentFrame(size_t frameIndex);
    void reset();
    bool isFinished() const;

private:
    sf::Sprite& sprite;
    std::vector<sf::IntRect> frames;
    float frameDuration;
    size_t currentFrame;
    float frameTime;
    bool finished;
};

#endif // ANIMATION_HPP























// #define ANIMATION_HPP

// #include <SFML/Graphics.hpp>
// #include <vector>

// class Animation {
// public:
//     Animation(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float frameDuration);
//     void update(float deltaTime);
//     void playAttackAnimation(); 
//     void playDeathAnimation(); 
// 	void playhitAnimation();  

// private:
//     sf::Sprite& sprite;
//     std::vector<sf::IntRect> frames;
// 	// std::vector<sf::IntRect>& idleFrames;std::vector<sf::IntRect>& walkFrames;
// 	// std::vector<sf::IntRect>& attackFrames;
// 	// std::vector<sf::IntRect>& hitFrames; std::vector<sf::IntRect>& deathFrames;
//     float frameDuration;
//     int currentFrame;
//     float frameTime;
//     bool isAttacking;
// 	bool isDead;
// };

// #endif // ANIMATION_HPP













// // headers/Animation.hpp
// #ifndef ANIMATION_HPP
// #define ANIMATION_HPP

// #include <SFML/Graphics.hpp>
// #include <vector>

// enum class MonsterState {
//     Idle,
//     Walk,
//     Attack,
//     Hit,
//     Death
// };

// class Animation {
// public:
//     Animation(sf::Sprite& sprite, 
//               const std::vector<sf::IntRect>& idleFrames, 
//               const std::vector<sf::IntRect>& walkFrames, 
//               const std::vector<sf::IntRect>& attackFrames, 
//               const std::vector<sf::IntRect>& hitFrames, 
//               const std::vector<sf::IntRect>& deathFrames, 
//               float frameDuration);

//     void update(float deltaTime);

//     void playAttackAnimation(); 
//     void playDeathAnimation(); 
//     void playHitAnimation();  
//     void playIdleAnimation(); 
//     void playWalkAnimation(); 

//     void setState(MonsterState newState);
//     bool isAnimationFinished() const;

// private:
//     sf::Sprite& sprite;
//     const std::vector<sf::IntRect>& idleFrames;
//     const std::vector<sf::IntRect>& walkFrames;
//     const std::vector<sf::IntRect>& attackFrames;
//     const std::vector<sf::IntRect>& hitFrames;
//     const std::vector<sf::IntRect>& deathFrames;

//     float frameDuration;
//     int currentFrame;
//     float frameTime;
//     MonsterState state;
//     bool animationFinished;
// };

// #endif // ANIMATION_HPP





































