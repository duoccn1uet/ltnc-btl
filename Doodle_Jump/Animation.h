#ifndef ANIMATION_H
#define ANIMATION_H

#include "CommonFunc.h"

class Animation
{
public:
	string name = "";
	int duration = 0;
	int angle_rotate = 0;
	Uint32 temp_time = 0;
	Uint32 start_time = 0;
	Uint32 wait_time = 0;
	bool ended = false;
	SDL_Point transform_vector = { 0, 0 };
	SDL_Texture* temp_texture = 0;
	Animation(string name, int duration);
	Animation(string name, int duration, int wait_time);
	Animation(string name, int duration, double angle_rotate, int wait_time);
	Animation(string name, int duration, SDL_Point transform_vector, int wait_time);
	Animation(string name, int duration, SDL_Texture* temp_texture, int wait_time);
	~Animation();
};

#endif ///ANIMATION_H