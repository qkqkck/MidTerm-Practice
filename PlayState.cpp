#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Heart.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Background.h"

const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = 0;

void PlayState::update() {	//onenter로 들어오면 sdl_geetticks로 시간 받고 계속 SDL_GetTicks받으면서 시간 차이 체크하고 화면에 출력하기
	if (PauseState::Instance()->pause) {
		PauseState::Instance()->update();
	}
	else {
		for (int i = 0; i < m_back.size(); i++) {
			m_back[i]->update();
		}
		if (SDL_GetTicks() > nextTime) {		//날라오는 적들
			nextTime = SDL_GetTicks() + TimeLeft;
			m_gameObjects.push_back(new Enemy(new LoaderParams(-200, 0, 55, 55, "enemy")));
		}
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
			if (i != 0 && SDL_GetTicks() > dynamic_cast<Enemy*>(m_gameObjects[i])->die) {	//enemy가 생성후 7초후(화면밖으로 나가면) 지움
				m_gameObjects.erase(m_gameObjects.begin() + i);
			}
			if (i > 0 && checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[i]))) {
				if (!colli) {		//닿으면 1초간 반짝반짝거리면서 무적상태, 목숨수 -1
					invin = SDL_GetTicks() + invinTime;
					myHeart--;
					if (myHeart == 0) {
						TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
					}
					if (m_heart.size() != 0)
						m_heart.erase(m_heart.begin());
					colli = true;
				}
			}
		}
		for (int i = 0; i < m_heart.size(); i++) {
			m_heart[i]->update();
			if (colli) {
				if (invin < SDL_GetTicks()) {
					colli = false;
				}
			}
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {		//pause상태
		TheGame::Instance()->getStateMachine()->PopupState(PauseState::Instance());
	}
}
void PlayState::render() {
	if (PauseState::Instance()->pause) {
		PauseState::Instance()->render();
	}
	else {
		for (int i = 0; i < m_back.size(); i++) {
			m_back[i]->draw();
		}
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
		for (int i = 0; i < m_heart.size(); i++) {
			m_heart[i]->draw();
		}
	}
}
bool PlayState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/helicopter.png", "helicopter", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Fire.png", "enemy", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/heart.png", "myHeart", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->backLoad("assets/Map.png", "stage1Back", TheGame::Instance()->getRenderer())) {
		return false;
	}
	m_gameObjects.push_back(new Player(new LoaderParams(1000, 400, 128, 55, "helicopter")));

	m_heart.push_back(new Heart(new LoaderParams(1000, 36, 51, 44, "myHeart")));
	m_heart.push_back(new Heart(new LoaderParams(1060, 36, 51, 44, "myHeart")));
	m_heart.push_back(new Heart(new LoaderParams(1120, 36, 51, 44, "myHeart")));
	m_heart.push_back(new Heart(new LoaderParams(1180, 36, 51, 44, "myHeart")));
	myHeart = 4;

	m_back.push_back(new Background(new LoaderParams(0, 0, 2000, 900, "stage1Back")));
	m_back.push_back(new Background(new LoaderParams(2000, 0, 1648, 900, "stage1Back")));
	std::cout << "entering PlayState\n";
	return true;

}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	for (int i = 0; i < m_heart.size(); i++) {
		m_heart[i]->clean();
	}
	m_heart.clear();
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	TheTextureManager::Instance()->clearFromTextureMap("enemy");
	std::cout << "exiting PlayState\n";
	return true;
}


bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->m_position.getX();
	rightA = p1->m_position.getX() + p1->m_width;
	topA = p1->m_position.getY();
	bottomA = p1->m_position.getY() + p1->m_height;

	leftB = p2->m_position.getX();
	rightB = p2->m_position.getX() + p2->m_width;
	topB = p2->m_position.getY();
	bottomB = p2->m_position.getY() + p2->m_height;

	if (rightA > leftB && rightB > leftA && topA < bottomB && topB < bottomA) {

		cout << "충돌" << endl;
		return true;
	}
	return false;
}