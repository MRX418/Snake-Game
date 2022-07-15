#include <Windows.h>
#include <conio.h>
#include <iostream>

bool gameOver;
const uint8_t height = 30;
const uint8_t width = 30;
uint8_t x, y;
int score, fruitX, fruitY; // Since we will be using rand() we cant use uint8_t
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
	fruitX = rand() %  height;
	fruitY = rand() % width;
	score = 0;
	cout << "Welcome To SnakeGame, Please Use :";
	cout << endl;
	cout << " a : to turn LEFT";
	cout << endl;
	cout << " d : to turn RIGHT";
	cout << endl;
	cout << " w : to go UP";
	cout << endl;
	cout << " s : to go DOWN";
	cout << endl;
	cout << " x : to exit the game";
	cout << endl;
	cout << "Please press ESC to start the Game";
	if (_getch() == '\033') {
		return;
	}
}

void draw() {

	system("cls");
	cout << "Score : " << score;
	cout << endl;
	for ( int i = 0; i < width; ++i ) {
		cout << "#";
	}
	cout << endl;
	for ( int i = 0; i < height; ++i ) {

		for ( int j = 0; j < width; ++j ) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else if (i == x && j == y) {
				cout << "O";
			}
			else if (i == fruitX && j == fruitY) {
				cout << "F";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

	for ( int i = 0; i < width; ++i ) {
		cout << "#";
	}
	cout << endl;
	Sleep(100);

}

void input() {
	direction = STOP;
		switch (_getch()) {

		case 'w':   
			direction = UP;
			break;
		case 's':   
			direction = DOWN;
			break;
		case 'd':    
			direction = RIGHT;
			break;
		case 'a':    
			direction = LEFT;
			break;
		case 'x':
			direction = STOP;
			gameOver = true;
			break;
		default:
			break;

		}
	
}

void logic() {

	switch (direction) {

	case UP:
		--x;
		break;
	case DOWN:
		++x;
		break;
	case RIGHT:
		++y;
		break;
	case LEFT:
		--y;
		break;
	default:
		break;

	}
	if (x > width || x < 0 || y < 0 || y > height) {
		gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % height;
		fruitY = rand() % width;
	}

}

int main() {

	setUp();
	while (!gameOver) {
			draw();
			input();
			logic();
	}
	system("cls");
	cout << "Game Over";
	return 0;

}