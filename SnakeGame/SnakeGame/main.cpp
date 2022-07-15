#include <Windows.h>
#include <conio.h>
#include <iostream>

bool gameOver;
const uint8_t height = 30;
const uint8_t width = 30;
uint8_t x, y;
int score, fruitX, fruitY, tail, tailX[100], tailY[100]; // Since we will be using rand() we cant use uint8_t
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
				bool print = false;
				for (int k = 0; k < tail; ++k) {
					if (tailX[k] == i && tailY[k] == j) {
						cout << "o";
						print = true;
					}
				}
				if (!print){
					cout << " ";
				}
				
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
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int tempX = 0, tempY = 0;
	for (int i = 1; i < tail; ++i) {
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}


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
		++tail;
		fruitX = rand() % height;
		fruitY = rand() % width;
	}

}

void GameOver() {
	std::cout << R"(

		
 ________  ________  _____ ______   _______           ________  ___      ___ _______   ________     
|\   ____\|\   __  \|\   _ \  _   \|\  ___ \         |\   __  \|\  \    /  /|\  ___ \ |\   __  \    
\ \  \___|\ \  \|\  \ \  \\\__\ \  \ \   __/|        \ \  \|\  \ \  \  /  / | \   __/|\ \  \|\  \   
 \ \  \  __\ \   __  \ \  \\|__| \  \ \  \_|/__       \ \  \\\  \ \  \/  / / \ \  \_|/_\ \   _  _\  
  \ \  \|\  \ \  \ \  \ \  \    \ \  \ \  \_|\ \       \ \  \\\  \ \    / /   \ \  \_|\ \ \  \\  \| 
   \ \_______\ \__\ \__\ \__\    \ \__\ \_______\       \ \_______\ \__/ /     \ \_______\ \__\\ _\ 
    \|_______|\|__|\|__|\|__|     \|__|\|_______|        \|_______|\|__|/       \|_______|\|__|\|__|
                                                                                                    
                                                                                                    
                                                                                                    




		)" << '\n';
}

int main() {

	setUp();
	while (!gameOver) {
			draw();
			input();
			logic();
	}
	system("cls");
	GameOver();
	return 0;

}