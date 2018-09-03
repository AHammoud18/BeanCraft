#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;  //let the header file know if the object is animated or not
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated) //this relates to Game.cpp, for example in line 56 of Game.cpp, the const char* path as shown here, is the file path written over there, and a bool set to true to have the function below run
	{
		animated = isAnimated; //if it is animated

		Animation idle = Animation(0, 5, 100); // in Animation(0, 5, 100) the 0 references the Y value of the sprite sheet, this being the very first sprite animation, 5 is the number of frames in that animation, and 100 is the delay between each frame in miliseconds
		Animation walk = Animation(1, 4, 100); //the same applies to this and the rest below
		Animation idlesword = Animation(2, 5, 100);
		Animation walksword = Animation(3, 4, 100);

		animations.emplace("Idle", idle); //this makes it easier to address what our animation will be
		animations.emplace("Walk", walk); //this makes it easier to address what our animation will be, look in KeyboardComponent.h to see this run when we press the "w" key
		animations.emplace("IdleSword", idlesword); //these are not implemented in our keyboard input yet, but will be used later
		animations.emplace("WalkSword", walksword); //these are not implemented in our keyboard input yet, but will be used later

		Play("Idle"); //this is the first animation played when starting the game, you could change this to the others above
		
		setTex(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}


	void setTex(const char* path)
	{
		/*if something were to happen to a texture,
		for example it broke, a texture change will happen here */
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}


	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};