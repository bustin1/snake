#pragma once

#include <SDL.h>
#include "Window.h"

class Food {
public:
	Food();
	bool checkEaten(int*, int*, int, int, int);
	void spawn(int*, int*, int);
	SDL_Rect rect;

};