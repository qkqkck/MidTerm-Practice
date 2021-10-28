#include "Player.h"
#include "LoaderParams.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
  m_x -= 1;
  m_currentFrame = ((SDL_GetTicks() / 100) % 6);
}

void Player::clean() {}