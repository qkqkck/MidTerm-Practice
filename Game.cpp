#include "Game.h"
#include "TextureManager.h"

SDL_Window* m_pWindow = 0;
SDL_Renderer* m_pRenderer = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow != 0)
    {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1 ,0);
      
      if(m_pRenderer != 0)
      {
        if(!TheTextureManager::Instance()->load("Assets/animate-alpha.png","animate", m_pRenderer))
        {
          return false;
        }
        GameObject* m_go = new GameObject();
        GameObject* m_player = new Player();
        m_go->load(100, 100, 128, 82,"animate");
        m_player->load(300, 300, 128, 82,"animate");
        m_gameObjects.push_back(m_go);
        m_gameObjects.push_back(m_player);
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255); //배경

      }else
      { 
        return false;
      }
    } else
      {
        return false;
      }
  } else
    {
    return false;
    }

 m_bRunning = true;
 return true;
}

void Game::update()
{
  for(int i=0; i<m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->update();
  }
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  for(int i=0; i<m_gameObjects.size(); i ++)
  {
    m_gameObjects[i]->draw(m_pRenderer);
  }
  SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
      m_bRunning = false;
      break;
      default:
      break;
    }
  }
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}