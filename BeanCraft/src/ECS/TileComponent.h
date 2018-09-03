#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	Vector2D position;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) //this loads in our tiles from assets
	{
		position.x = x;
		position.y = y;
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id; //each texture's id number

		switch (tileID) //a switch statement is used to determine which textures apply to which integer displayed in "map.map"
		{
		case 0: //the sky texture will relate to the 0 integer in the map file, the same applies to the rest below
			path = "assets/sky.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/dirt.png";
			break;
		case 3:
			path = "assets/dirtbottom.png";
			break;
		case 4:
			path = "assets/grass1.png";
			break;
		case 5:
			path = "assets/grass2.png";
			break;
		case 6:
			path = "assets/grasscorner.png";
			break;
		case 7:
			path = "assets/grasscorner2.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}

}; 