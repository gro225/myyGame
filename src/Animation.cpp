#include "../headers/Animation.hpp"

Animation::Animation(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float frameDuration)
    : sprite(sprite), frames(frames), frameDuration(frameDuration), currentFrame(0), frameTime(0.0f),finished(false) {}

void Animation::update(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime >= frameDuration && !frames.empty()) {
        frameTime -= frameDuration;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);
    }
}
void Animation::updateOnce(float deltaTime) {
    if (finished) return;

    frameTime += deltaTime;
    if (frameTime >= frameDuration && !frames.empty()) {
        frameTime -= frameDuration;
        ++currentFrame;

        if (currentFrame >= frames.size()) {
            currentFrame = frames.size() - 1; 
            finished = true;
        }

        sprite.setTextureRect(frames[currentFrame]);
    }
}


void Animation::reset() {
    finished = false;
    currentFrame = 0;
}
bool Animation::isFinished() const {
    return finished;
}




























