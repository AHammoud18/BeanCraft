#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int id, int x, int y);
	static SDL_Renderer *renderer;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Event event;
	static SDL_Rect camera;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders
	};

private:
	bool isRunning;
	int cnt = 0;
	SDL_Window *window;
};
