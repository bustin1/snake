#include "Window.h"
#include "Snake.h"
#include "Food.h"
#include <SDL.h>//graphics
#include <thread>//timer
#include <chrono>//timer
#include <iostream>//printing
#include <fstream>//file streaming
#include <vector>//vectors

/*
polls events for both the snake and window.
This is probably not the best way to do this.
*/
void pollEvents(Window &window, Snake &snake) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		window.pollEvents(event);
		if(!window.paused)
			snake.pollEvents(event);
	}
}

/*
reads ENTIRE file and
returns vector of names and scores
*/
std::vector<std::string> readFile(std::string fileName) {
	std::vector<std::string> data;
	std::ifstream infile;
	infile.open(fileName);
	std::string oneLine = "";
	while (!infile.eof()) {
		getline(infile, oneLine);
		data.push_back(oneLine);
	}
	infile.close();
	return data;
}

/*
finds the place the player scored 
returns that place. Also modifies data 
*/
int getPlace(int score, std::vector<std::string> &data) {
	int index = 0;
	std::string temp = data[data.size()-1];
	while (score < stoi(data[index].substr(data[index].find(" ")+1)) && index != data.size()-1) {
		index++;
	}
	for (int i = data.size()-1; i >= index + 1; i--) {
		data[i] = data[i - 1];
	}
	data[index] = temp;
	return index + 1;
}

int main(int argc, char* argv[]) {

	//records file
	std::ifstream infile;
	std::string fileName = "SnakeAllTime.txt";
	infile.open(fileName);

	//list of all the top scorers
	std::vector<std::string> data = readFile(fileName);

	//highest scorest name
	std::string name = data[0].substr(0, data[0].find(" "));
	std::string score = data[0].substr(data[0].find(" ") + 1);
	if (name == "") {
		std::cout << "You're the first to play!!\n";
		data.pop_back();
	}
	else {
		std::cout << name << " is on top with a score of " << score << std::endl;
	}
	std::cout << "To be on the leaderboard, you must get top 10\n";
	
	/*prints the other people who scored
	well in the past*/
	for (int i = 0; i < (int)data.size(); i++) {
		std::cout << i+1 << ": " << data[i] << std::endl;
	}

	/*all these are considered objects*/
	Window window("First Window");//the window
	Food food;//the food
	Snake snake(window, food, 0, 200, 100, 255);//the snake
	Timer t;//timer, in window.h
	
	t.start1();

	/*while playing the game and haven't died*/
	while (!window.isClosed() && !snake.hitWall() && !snake.isDead()) {
		//std::cout << t.end1() << std::endl;
		if (t.end1() > 2) {//change this value for speed
			pollEvents(window, snake);
			if (!window.paused) {
				if (window.countdown) {//make sure whene pausing you get time to get ready
					window.countDown((int)((5000-window.t.end1())/1000));
					if (window.t.end1() > 5000) {
						window.countdown = false;
					}
				}
				else {
					//all the drawing
					window.clear();
					snake.draw();
					t.start1();
				}
			}
			else {
				window.countdown = true;
			}
		}
	}

	/*if you beat the first place guy*/
	if (name == "" || data.size() < 10 || snake.getScore() > stoi(data[9].substr(data[9].find(" ") + 1))) {

		/*make sure name is not too short*/
		std::cout << "What is your name?" << std::endl;
		getline(std::cin, name);
		while (name.length() < 3) {
			std::cout << "name is too short. Enter different name" << std::endl;
			getline(std::cin, name);
		}
		
		data.push_back(name + " " + std::to_string(snake.getScore()));
		int place = getPlace(snake.getScore(), data);
		
		std::ofstream outfile;

		/*print top 10 names*/
		outfile.open(fileName);
		for (int i = 0; i < (int)data.size(); i++) {
			outfile << data[i].substr(0, data[i].find(" ")) << " " << data[i].substr(data[i].find(" ")+1);
			if (i != data.size() - 1) {
				outfile << "\n";
			}
		}
		outfile.close();
		std::cout << "Congrats on scoring " << snake.getScore() << " points.\n"<< place << " place!" << std::endl;
		return 0;
	}
	std::cout << "Nice try, better luck next time\n";
	return 0;
}

