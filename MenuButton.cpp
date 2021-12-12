#include "MenuButton.h"
#include "InputHandler.h"
MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // use the base class drawing
}
void MenuButton::update() {
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(0) && m_bReleased) {
			m_currentFrame = CLICKED;
			m_callback(); // 콜백 함수 호출
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(0)) {
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else {
		m_currentFrame = MOUSE_OUT;
	}
}
void MenuButton::clean()
{
	SDLGameObject::clean();
}