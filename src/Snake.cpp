#include "Snake.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>
#include <chrono>

/*creates Snake with image*/
/*
Snake::Snake(const Window& window, Food food, const std::string &image_path)
	: Window(window), food(food)
{
	SDL_Surface *surface = IMG_Load(image_path.c_str());
	if (!surface) {
		std::cerr << "Failed to create surface\n";
	}
	snakeTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!snakeTexture) {
		std::cerr << "Failed to create texture\n";
	}

	SDL_FreeSurface(surface);

	init();
}*/

/*creates Snake without image*/
Snake::Snake(const Window &window, Food food, int r, int g, int b, int a) 
	: Window(window), food(food), r(r), g(g), b(b), a(a)
{

	init();
	
}

Snake::~Snake() {
	SDL_DestroyTexture(snakeTexture);

}

void Snake::init() {

	//initalize each snakes body parts direction(-1 means not moving)

	dir.push_back(Direction::inactive);

	bodyX.push_back(0);
	bodyY.push_back(0);
	
	rect = { 0, 0, SIZE, SIZE };

}


void Snake::draw() {

	SDL_SetRenderDrawColor(renderer, 0, 50, 250, 255);//blue
	SDL_RenderFillRect(renderer, &food.rect);//draw food
	SDL_SetRenderDrawColor(renderer, r, g, b, a);//set color to color of snake to draw

	if (changeDir != dir[0]) {
		if (bodyX[0] % SIZE == 0 && bodyY[0] % SIZE == 0) {
			dir[0] = changeDir;
		}
	}

	for (char i = 0; i < length; i++) {

		switch(dir[i]){
			case Direction::up:
				bodyY[i]--;
				break;
			case Direction::down:
				bodyY[i]++;
				break;
			case Direction::left:
				bodyX[i]--;
				break;
			case Direction::right:
				bodyX[i]++;
				break;
		}

		if(i > 0){
			if(bodyX[i] % SIZE == 0 && bodyY[i] % SIZE == 0){
				if(bodyX[i] < bodyX[i-1]){
					dir[i] = Direction::right;
				}
				else if(bodyX[i] > bodyX[i-1]){
					dir[i] = Direction::left;
				}
				else if(bodyY[i] < bodyY[i-1]){
					dir[i] = Direction::down;
				}
				else if(bodyY[i] > bodyY[i-1]){
					dir[i] = Direction::up;
				}
			}
		}

		rect.x = bodyX[i];
		rect.y = bodyY[i];

		if (snakeTexture) {
			SDL_RenderCopy(renderer, snakeTexture, NULL, &rect);
		}
		else {
			SDL_RenderFillRect(renderer, &rect);
		}

		dead = hitSelf(i);
		if (dead) {
			break;
		}
		SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);//draw text
	}

	if (food.checkEaten(bodyX, bodyY, food.rect.x, food.rect.y, length)) {
		addLength();
		changeScore();
	}
}

int Snake::getScore() {
	return score;
}

void Snake::changeScore() {
	score++;
	std::string text = "SCORE: " + std::to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

bool Snake::hitSelf(int i) {
	if (i > 1 && abs(bodyX[i] - bodyX[0]) < SIZE && abs(bodyY[i] - bodyY[0]) < SIZE) {
		//std::cout << i << std::endl;
		//std::cout << abs(x[i] - x[0]) << std::endl;
		//std::cout << abs(y[i] - y[0]) << std::endl;
		return true;
	}
	return false;
}

void Snake::addLength() {
	dir.push_back(dir[length - 1]);
	if (dir[length-1] == Direction::right) {
		bodyX.push_back(bodyX[length - 1] + SIZE);
		bodyY.push_back(bodyY[length - 1]);
	}
	else if (dir[length-1] == Direction::left) {
		bodyX.push_back(bodyX[length - 1] - SIZE);
		bodyY.push_back(bodyY[length - 1]);
	}
	else if (dir[length-1] == Direction::up) {
		bodyX.push_back(bodyX[length - 1]);
		bodyY.push_back(bodyY[length - 1] + SIZE);
	}
	else if (dir[length-1] == Direction::down) {
		bodyX.push_back(bodyX[length - 1]);
		bodyY.push_back(bodyY[length - 1] - SIZE);
	}
	length++;
}

bool Snake::hitWall() {
	if (bodyX[0] < 0) {
		bodyX[0] = 0;
		return true;
	}
	if (bodyX[0] + SIZE > WIDTH) {
		bodyX[0] = WIDTH - SIZE;
		return true;
	}
	if (bodyY[0] < 0) {
		bodyY[0] = 0;
		return true;
	}
	if (bodyY[0] + SIZE > HEIGHT) {
		bodyY[0] = HEIGHT - SIZE;
		return true;
	}
	return false;
}

void Snake::pollEvents(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (dir[0] != Direction::right) {
				changeDir = Direction::left;
			}
			break;
		case SDLK_RIGHT:
			if (dir[0] != Direction::left) {
				changeDir = Direction::right;
			}
			break;
		case SDLK_UP:
			if (dir[0] != Direction::down) {
				changeDir = Direction::up;
			}
			break;
		case SDLK_DOWN:
			if (dir[0] != Direction::up) {
				changeDir = Direction::down;
			}
			break;
		}	
	}
}

