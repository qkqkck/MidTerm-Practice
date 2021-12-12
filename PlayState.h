#pragma once
#include "GameState.h"
#include "SDLGameObject.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	virtual std::string getStateID() const { return s_playID; }
	static PlayState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	bool colli = false;		//닿았으면 실행 + player 무적상태 체크
private:
	static const std::string s_playID;
	static PlayState* s_pInstance;
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_heart;
	std::vector<GameObject*> m_back;
	int TimeLeft = 250;	//1000 -> 1초
	int invinTime = 1700;	//1.7초 무적
	int nextTime = 0;			//다음 적이 나오는 시간 (현재시간 + TimeLeft 로 조절)
	int myHeart = 4;		//목숨수
	int invin = 0;	//무적시간 체크


};