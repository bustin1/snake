#include "Food.h"
#include <thread>
#include <iostream>

Food::Food() {
  std::vector<short> a;
  std::vector<short> b;
  a.push_back(0);
  b.push_back(0);
	spawn(a, b, 1);
	rect.h = SIZE;
	rect.w = SIZE;
}

void Food::spawn(std::vector<short> x, std::vector<short> y, int length) {
	srand(time(NULL));
	rect.x = rand() % NUM_IN_ROW * SIZE;
	rect.y = rand() % NUM_IN_COL * SIZE;
	for (int i = 0; i < length; i++) {
		if (abs(x[i] - rect.x) < SIZE && abs(y[i] - rect.y) < SIZE) { 
		//	std::cout << x[i] << ", " << y[i] << std::endl;
			i = 0;
			rect.x = rand() % NUM_IN_ROW * SIZE;
			rect.y = rand() % NUM_IN_COL * SIZE;
		}
	}
}

bool Food::checkEaten(std::vector<short> x1,std::vector<short> y1, int x2, int y2, int length) {
	if (abs(x1[0] - x2) < SIZE && abs(y1[0] - y2) < SIZE) {
		spawn(x1, y1, length);
		return true;
	}
	return false;
}


