#pragma once
#include "snakegame.h"

void SnakeGame::setUp() {
    gameOver = false;
    direction_ = Direction::STOP;
    x_ = width_ / 2;
    y_ = height_ / 2;
    fruitX_ = rand() %  height_;
    fruitY_ = rand() % width_;
}


