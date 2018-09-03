#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map; //map pointer
Manager manager; //manager pointer

SDL_Renderer* Game::renderer = nullptr; //this pointer is set to null at the begining so no memory leaks happen
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders; 

auto& player(manager.addEntity()); //reference to our player

enum groupLabels : std::size_t //this sets and references players,maps and enemies, you'll see it being used below
{
	groupMap,
	groupPlayers,
	groupEnemies
};

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen) //this function renders the screen
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;  //if the boolean is set to true, this statement will run, making the game fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //Window is initialized
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Color of the windows, right now it's set to white
		}

		isRunning = true; //when the game is running, the bool "isRunning" that was in Game.h is set to true over here
	}
	map = new Map();

	Map::LoadMap("assets/map1.map", 25, 20); //this loads in a .map file from the assets folder to draw into the game

	player.addComponent<TransformComponent>(2);								
	player.addComponent<SpriteComponent>("assets/orangeanims.png", true); //this loads in the sprite sheet, the "true" statement come from Animation.h, this lets the SpriteComponent know that its supposed to be animated
	player.addComponent<KeyboardController>(); //this implements keyboard inputs to the player
	player.addComponent<ColliderComponent>("player"); //this is a collider component called player
	player.addGroup(groupPlayers); //this puts the player in the "groupPlayers" section from line 18 in Game.cpp
}

void Game::handleEvents()  //this function runs when the console is quit
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() //this is the update function to give a constant refresh to the screen
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
	
}

auto& tiles(manager.getGroup(groupMap));	//references to the groups from line 18
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()//this is the game's render function
{   //below renders the order of what should be seen on screen, from bottom to top.
	SDL_RenderClear(renderer); 
	for (auto& t : tiles)//this draws the tiles below the player
	{
		t->draw();
	}

	for (auto& p : players)//this draws the player above the tiles
	{
		p->draw();
	}
	for (auto& e : enemies)//this draws the enemies above the player.
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() //this erases the memory of the game that was run, just to clean up space when quit
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y) //this loads in the tiles from map.map in the assets folder and places them according to their x and y positions
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}