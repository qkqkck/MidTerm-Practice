#pragma once
#include"SDLGameObject.h"
#include"InputHandler.h"

class Heart : public SDLGameObject
{
public:
	Heart(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
};