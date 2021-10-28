#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "vector"

class Game
{
  public:
  Game() {}
  ~Game() {}

  bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
  void render();
  void update();
  bool running();
  void handleEvents();
  void clean();

  private:
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  TextureManager m_textureManager;
  std::vector<GameObject*>m_gameObjects;
  int m_currentFrame;
  bool m_bRunning;
};