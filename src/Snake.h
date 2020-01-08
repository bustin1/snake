#pragma once

#include <SDL.h>
#include "Window.h"
#include "Food.h"

class Snake : public Window {
public:
	Snake(const Window &window, Food food, int r, int g, int b, int a);
	Snake(const Window& window, Food food, const std::string &image_path);
	~Snake();
	void draw();
	void pollEvents(SDL_Event &event);
	void changeScore();
	void init();
	bool hitWall();
	bool hitSelf(int);
	int x[NUM_OF_SQUARES];
	int y[NUM_OF_SQUARES];
	int getScore();
	inline bool isDead() { return dead; };

private:
	SDL_Rect rect;
	Food food;

	int direction[NUM_OF_SQUARES];
	int turn[NUM_IN_ROW][NUM_IN_COL];
	int w = SIZE, h = SIZE;
	int r, g, b, a;
	int length = 1;
	int changeD = -1;

	bool dead = false;

	int score = 0;

	SDL_Texture* snakeTexture = nullptr;


private:
	void addLength();

};