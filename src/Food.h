#pragma once

#include <SDL.h>
#include <vector>
#include "Window.h"

class Food {
public:
	Food();
	bool checkEaten(std::vector<short>, std::vector<short>, int, int, int);
	void spawn(std::vector<short>, std::vector<short>, int);
	SDL_Rect rect;

};
