#pragma once
#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <QObject>

class SnakeGame: public QObject {
    Q_OBJECT
public:
    SnakeGame() =  default;
    bool gameOver;
   enum Direction {
       LEFT, RIGHT, UP, DOWN, STOP
   };
    const uint8_t height_ = 30;
    const uint8_t width_ = 30;
    uint8_t x_ , y_ ;
    int score_ = 0 , fruitX_, fruitY_, tail_, tailX_[50], tailY_[50];
    Direction direction_;
    void setUp();
};




#endif // SNAKEGAME_HPP
