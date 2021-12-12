#pragma once
#include"TextureManager.h"
#include<SDL_image.h>
#include <algorithm>

class Blur {
public:
	static Blur* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Blur();
			return s_pInstance;
		}
		return s_pInstance;
	}
	void fastblur(SDL_Surface* image, int radius);
private:
	static Blur* s_pInstance;
};

typedef Blur TheBlur;