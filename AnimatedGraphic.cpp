#include"AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams) {}

void AnimatedGraphic::update() {
	m_currentFrame = int(SDL_GetTicks() / 100 % m_numFrames);
	SDLGameObject::update();
}
void AnimatedGraphic::draw() {
	SDLGameObject::draw();
}
void AnimatedGraphic::clean() {
}