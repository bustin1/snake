#include "Window.h"
#include <iostream>
#include <SDL_image.h>

Window::Window(const std::string& title) 
	: title1(title)
{
	Message_rect.x = 100;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 50; // controls the width of the rect
	Message_rect.h = 20; // controls the height of the rect
	closed = !initWindow();
}

Window::~Window() {
	SDL_DestroyTexture(textTexture);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

}

bool Window::initWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initalize SDL.\n";
		return 0;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		std::cerr << "Failed to initalize SDL.image\n";
		return false;
	}

	window = SDL_CreateWindow(
		title1.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		0
	);

	if (window == nullptr) {
		std::cerr << "Failed to create a window\n";
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer\n";
		return 0;
	}

	TTF_Init();
	font = TTF_OpenFont("arial.ttf", 24);
	color = { 255, 50, 50 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "SCORE: 0", color);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); 

	return true;
}

void Window::pollEvents(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		std::cout << "Exited." << std::endl;
		closed = true;
		break;
		
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			closed = true;
			break;
		case SDLK_p:
			paused = !paused;
			if (!paused) {
				t.start1();
			}
			break;
		}
		break;
		

	case SDL_MOUSEBUTTONDOWN:
		std::cout << event.motion.x << ',' << event.motion.y << std::endl;
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Window::countDown(int time) {
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);//draws the color

	std::string text = std::to_string(time);
	
	Message_rect.w = 50; // controls the width of the rect
	Message_rect.h = 80; // controls the height of the rect
	Message_rect.x = WIDTH / 2 - Message_rect.w/2;  //controls the rect's x coordinate 
	Message_rect.y = HEIGHT / 2 - Message_rect.h / 2; // controls the rect's y coordinte
	font = TTF_OpenFont("arial.ttf", 50);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);

	SDL_RenderPresent(renderer);
}

void Window::clear() {
	SDL_RenderPresent(renderer);//puts everything on the screen

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);//draws the color

}
