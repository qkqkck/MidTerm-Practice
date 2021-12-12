#include"Background.h"

Background::Background(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_currentFrame = 0;
	myPosition = m_position.getX();
}
void Background::draw()
{
	SDLGameObject::draw();
}
void Background::update()
{
	if (this->m_width == 1280) {
		m_currentFrame = 0;
	}
	else {
		m_velocity.setX(-10);	
		if (m_position.getX() <= myPosition - 2000) {
			m_position.setX(myPosition);
		}
	}

	SDLGameObject::update();

}
void Background::clean() {}