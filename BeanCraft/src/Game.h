#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game   //these are all variables and functions decalred from Game.cpp
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen); //this is set in main.cpp, char* title is set to "Bean Craft", int width and int height is the window's width and height, lastly the bool operator for fullscreen. 

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int id, int x, int y); //this is for map generation, int id related to numbers on the map, int x being the x coords related to the numbers and y being the y coords.
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	bool isRunning;
	int cnt = 0; //this is no longer used, but was used in Game.cpp's update function to display numbers just to prove that the game is running
	SDL_Window *window;
};
