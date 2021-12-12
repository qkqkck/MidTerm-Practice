#include "TextureManager.h"
#include <SDL_image.h>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) return false;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}
bool TextureManager::backLoad(string fileName, string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) return false;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	SDL_SetTextureAlphaMod(pTexture, 180);			//반투명 정도 0~255
	SDL_SetTextureBlendMode(pTexture, SDL_BLENDMODE_BLEND);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}
bool TextureManager::screenShotLoad(string id, SDL_Surface* screenShot, SDL_Renderer* pRenderer) {
	if (screenShot == 0) return false;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, screenShot);
	SDL_FreeSurface(screenShot);
	SDL_SetTextureAlphaMod(pTexture, 170);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}
void TextureManager::draw(string id, int x, int y, int width, int height, int current, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;	//소스파일정보
	SDL_Rect destRect;	//출력정보
	srcRect.x = width * current;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}