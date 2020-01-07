#include "Food.h"
#include <thread>
#include <iostream>

Food::Food() {
	int a = 0;
	int b = 0;
	spawn(&a, &b, 1);
	rect.h = SIZE;
	rect.w = SIZE;
}

void Food::spawn(int *x, int *y, int length) {
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

bool Food::checkEaten(int *x1, int *y1, int x2, int y2, int length) {
	if (abs(x1[0] - x2) < SIZE && abs(y1[0] - y2) < SIZE) {
		spawn(x1, y1, length);
		return true;
	}
	return false;
}


