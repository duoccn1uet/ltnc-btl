
#include "Animation.h"

Animation::Animation(string name, int duration) :name(name), duration(duration) {}

Animation::Animation(string name, int duration, int wait_time) : name(name), duration(duration), wait_time(wait_time){}

Animation::Animation(string name, int duration, double angle_rotate, int wait_time): name(name), duration(duration), angle_rotate(angle_rotate), wait_time(wait_time) {
	if (name != "Rotate")
		cerr << "Invalid " << name << " animation" << endl;
}

Animation::Animation(string name, int duration, SDL_Point transform_vector, int wait_time): name(name), duration(duration),transform_vector(transform_vector), wait_time(wait_time)
{
	//if (name != "Transform") cerr << "Invalid animation" << endl;
}
Animation::Animation(string name, int duration, SDL_Texture* temp_texture, int wait_time) : name(name), duration(duration), temp_texture(temp_texture), wait_time(wait_time)
{
	if (name != "Switch Texture")
		cerr << "Invalid " << name << " animation" << endl;
}
Animation::~Animation()
{
}



