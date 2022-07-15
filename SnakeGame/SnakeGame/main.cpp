#include <Windows.h>

#include <iostream>

bool gameOver;
const uint8_t height = 30;
const uint8_t width = 60;
uint8_t x, y, fruitX, fruitY;
int score;
enum Direction {
	LEFT, RIGHT, UP, DOWN, STOP
};
Direction direction;

using namespace std;
void setUp() {

	gameOver = false;
	direction = Direction::STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() / width;
	fruitY = rand() / height;
	score = 0;
}
void draw() {
	system("cls");
	for (int i = 0; i < width; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; ++i) {
		cout << "#";
	}
	cout << endl;
	Sleep(100);
}
void input() {}
void logic() {}
int main() {
	setUp();
	while (!gameOver) {
		draw();
		input();
		logic();
	}
	return 0;
}