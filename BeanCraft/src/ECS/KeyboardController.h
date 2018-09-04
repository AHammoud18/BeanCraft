#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent * transform;
	SpriteComponent *sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{

		if (Game::event.type == SDL_KEYDOWN) //when a keyboard key is pushed down
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w: //when the "w" key is pressed, the velcoity of the player's Y position is set to negative 1, making him move up	
				transform->velocity.y = -1;
				break;
			case SDLK_s:
				transform->velocity.y = 1; //when the "s" key is pressed, the velcoity of the player's Y position is set to 1, making him move down
				break;
			case SDLK_a:
				transform->velocity.x = -1; //this allows the player to move left
				sprite->Play("Walk"); //this loads in the walking sprite animation from SpriteComponent.h to play when the a key is pressed
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 1; //this allows the player to move right
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL; //this flips the walking animation horizontally so the character's animation follows the direction he's moving
				break;
			case SDLK_SPACE:
				transform->velocity.y = -2; //this allows the player to jump although i haven't implemented any gravity, the sprite will just move up at a velocity of -2 along the y axis
				break;
			default:
				break;
			}
		}

		//when key is released
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w: //the velocity is always set to 0 so the player stops moving and halts at the position he's in.
				transform->velocity.y = 0; 
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL; //this flips the characters sprite back, although im trying to fix this, so he can idle the way he was facing previously
				break;
			case SDLK_SPACE:
				transform->velocity.y = 0;
				break;
			default:
				break;
			}
		}
	}
};