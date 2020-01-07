#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>
#include <chrono>
#define NUM_OF_SQUARES 1200
#define NUM_IN_ROW 40
#define NUM_IN_COL 30
#define SIZE 20
#define HEIGHT 600
#define WIDTH 800


struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	void start1() {
		start = std::chrono::high_resolution_clock::now();
	}
	float end1() {//returns the change
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration.count()* 1000.0f;
	}
};

class Window {
public:
	//Window();
	Window(const std::string& title);
	~Window();//destructor destorys the renderer and the window

	void pollEvents(SDL_Event &event);//buttons and mouse events
	void clear() ;//rendering

	Timer t;
	bool closed = false;
	bool paused = false;
	void countDown(int time);
	bool countdown = false;

	inline bool isClosed() const { return closed; }//return whether the window is closed

private:
	bool initWindow();//create window and renderer
	std::string title1;
	SDL_Window* window = nullptr;
	

protected:
	SDL_Renderer* renderer = nullptr;

	SDL_Color color;
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Rect Message_rect;


};