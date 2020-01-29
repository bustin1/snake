#pragma once

#include <SDL.h>
#include <vector>
#include "Window.h"
#include "Food.h"

enum class Direction {inactive, up, left, right, down};

class Snake : public Window {
public:
	Snake(const Window &window, Food food, int r, int g, int b, int a);
	//Snake(const Window &window, Food food, const std::string &image_path);
	~Snake();
	void draw();
	void pollEvents(SDL_Event &event);
	void changeScore();
	void init();
	bool hitWall();
	bool hitSelf(int);
  	std::vector<short> bodyX;
 	std::vector<short> bodyY;
	std::pair <int, int> coor;
	int getScore();
	inline bool isDead() { return dead; };

private:
	SDL_Rect rect;
	Food food;

  	//std::vector<char> direction;
	//char turn[NUM_IN_ROW][NUM_IN_COL];
	std::vector<Direction> dir;
	//std::pair <int, int> dimensions;
	//int w = SIZE, h = SIZE;//one body segment dimensions
	char r, g, b, a;
	int length = 1;
	Direction changeDir = Direction::inactive;
	bool dead = false;
	int score = 0;
	SDL_Texture* snakeTexture = nullptr;


private:
	void addLength();

};
