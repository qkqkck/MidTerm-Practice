#include"Player.h"
#include"PlayState.h"
Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {
}
void Player::draw() {
	SDLGameObject::draw(); // SDLGameObject 사용
}
void Player::update() {
	m_velocity.setX(0);		// 키를 때면 멈춤
	m_velocity.setY(0);		// 키를 때면 멈춤 
	handleInput(); // add our function
	if (PlayState::Instance()->colli) {
		m_currentFrame = int(((SDL_GetTicks() / 33) % 6));
	}
	else m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	SDLGameObject::update();
}
void Player::clean() {
}
void Player::handleInput() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		if (this->m_position.getX() + this->m_width >= 1280) {
			m_velocity.setX(0);
		}
		else m_velocity.setX(5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		if (this->m_position.getX() <= 0) {
			m_velocity.setX(0);
		}
		else m_velocity.setX(-5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		if (this->m_position.getY() <= 100) {
			m_velocity.setY(0);
		}
		else m_velocity.setY(-5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		if (this->m_position.getY() + this->m_height >= 720) {
			m_velocity.setY(0);
		}
		else m_velocity.setY(5);
	}
}