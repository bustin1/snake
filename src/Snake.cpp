#include "Snake.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>
#include <chrono>

/*creates Snake with image*/
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
}

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
  direction.push_back(-1);
  x.push_back(0);
  y.push_back(0);
  for(int i=0; i<NUM_OF_SQUARES; i++)
  {
	  turn[i / 30][i % 30] = -1;
  }

	//initialize snake
	rect = { 0, 0, w, h };

}


void Snake::draw() {

	SDL_SetRenderDrawColor(renderer, 0, 50, 250, 255);
	SDL_RenderFillRect(renderer, &food.rect);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if (changeD != direction[0]) {
		if (x[0] % SIZE == 0 && y[0] % SIZE == 0) {
			direction[0] = changeD;
			turn[x[0] / SIZE][y[0] / SIZE] = direction[0];
		}
	}
	for (char i = 0; i < length; i++) {
		if (x[i] % SIZE == 0 && y[i] % SIZE == 0) {
			if (turn[x[i] / SIZE][y[i] / SIZE] != -1) {
				direction[i] = turn[x[i] / SIZE][y[i] / SIZE];
				if (i == length-1) {
					turn[x[i] / SIZE][y[i] / SIZE] = -1;
				}
			}
			
		}
		if (direction[i] == 0) {
			x[i] -= 1;
		}
		else if (direction[i] == 1) {
			x[i] += 1;
		}
		else if (direction[i] == 2) {
			y[i] -= 1;
		}
		else if (direction[i] == 3) {
			y[i] += 1;
		}
		rect.x = x[i];
		rect.y = y[i];
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
		SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
	}
	if (food.checkEaten(x, y, food.rect.x, food.rect.y, length)) {
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
	if (i > 1 && abs(x[i] - x[0]) < SIZE && abs(y[i] - y[0]) < SIZE) {
		//std::cout << i << std::endl;
		//std::cout << abs(x[i] - x[0]) << std::endl;
		//std::cout << abs(y[i] - y[0]) << std::endl;
		return true;
	}
	return false;
}

void Snake::addLength() {
	direction[length] = direction[length - 1];
	if (direction[length-1] == 0) {
		x.push_back(x[length - 1] + SIZE);
		y.push_back(y[length - 1]);
	}
	else if (direction[length-1] == 1) {
		x.push_back(x[length - 1] - SIZE);
		y.push_back(y[length - 1]);
	}
	else if (direction[length-1] == 2) {
		x.push_back(x[length - 1]);
		y.push_back(y[length - 1] + SIZE);
	}
	else if (direction[length-1] == 3) {
		x.push_back(x[length - 1]);
		y.push_back(y[length - 1] - SIZE);
	}
	length++;
}

bool Snake::hitWall() {
	if (x[0] < 0) {
		x[0] = 0;
		return true;
	}
	if (x[0] + SIZE > WIDTH) {
		x[0] = WIDTH - SIZE;
		return true;
	}
	if (y[0] < 0) {
		y[0] = 0;
		return true;
	}
	if (y[0] + SIZE > HEIGHT) {
		y[0] = HEIGHT - SIZE;
		return true;
	}
	return false;
}

void Snake::pollEvents(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (direction[0] != 1) {
				changeD = 0;
			}
			break;
		case SDLK_RIGHT:
			if (direction[0] != 0) {
				changeD = 1;
			}
			break;
		case SDLK_UP:
			if (direction[0] != 3) {
				changeD = 2;
			}
			break;
		case SDLK_DOWN:
			if (direction[0] != 2) {
				changeD = 3;
			}
			break;
		}	
	}
}

