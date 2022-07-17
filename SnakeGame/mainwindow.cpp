#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <iostream>
#include <QLabel>
#include <QKeyEvent>
int count = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::intro(){
       ui->centralwidget->setStyleSheet("background-color: black;");
       QString text[] ={ "Welcome To SnakeGame, Please Use : ", "        a : to turn LEFT",
                         "        d : to turn RIGHT", "        w : to go UP",
                         "        s : to go DOWN", "        x : to exit the game"};
       ui->textBrowser->setTextColor(QColorConstants::Svg::green);
       ui->textBrowser->setStyleSheet("background-color: black;");
       ui->textBrowser->setText("\n\n\t\t"+text[0]+"\n"+ "\t\t\t"+text[1]+"\n"+ "\t\t\t"+
                                 text[2]+"\n"+ "\t\t\t"+ text[3]+"\n"+ "\t\t\t"+
                                 text[4]+"\n"+ "\t\t\t"+ text[5]+"\n");
       connect(ui->start, SIGNAL(clicked()), this, SLOT(start()));
       ui->start->setStyleSheet("background-color: green;");
       ui->textBrowser_2->setStyleSheet("background-color: black;");
       ui->textBrowser_2->setTextColor(QColorConstants::Svg::green);
       std::string score = std::to_string(game_.score_);
       const QString str = QString::fromStdString(score);
       ui->textBrowser_2->setText("                                               Score : " + str);
       const QSize btnSize = QSize(100, 100);
       for (int i = 0; i < game_.height_; ++i) {

               for (int j = 0; j < game_.width_; ++j) {
                   QPushButton* button = new QPushButton();

                       button->setStyleSheet("background-color: black");
                       button->setFixedSize(btnSize);


                   ui->gridLayout->addWidget(button, i, j);
                   ui->gridLayout->setSpacing(0);
                   }

               }
        //connect(this, SIGNAL(over()), this, SLOT(gameOver()));
}

//void MainWindow::gameOver(){
 //   for (int i = 0; i < game_.height_; ++i) {

 //           for (int j = 0; j < game_.width_; ++j) {
 //               auto button = qobject_cast<QPushButton*>(ui->gridLayout->itemAtPosition(i,j)->widget());
  //            button->setStyleSheet("background-color: black");
  //          }
 //   }
 //   QTextBrowser* text = new QTextBrowser();
 //   text->setStyleSheet("background-color: black;");
 //   text->setTextColor(QColorConstants::Svg::green);
  //  text->setText("GAME OVER");
  //  ui->gridLayout->addWidget(text);
//}
void MainWindow::start(){
    ui->textBrowser->deleteLater();
    ui->start->deleteLater();
    game_.setUp();
    draw();
}

void MainWindow::draw(){
    std::string score = std::to_string(game_.score_);
    const QString str = QString::fromStdString(score);
    ui->textBrowser_2->setText("                                               Score : " + str);
    for ( int i = 0; i < game_.height_; ++i ) {

        for ( int j = 0; j < game_.width_; ++j ) {
           auto button = qobject_cast<QPushButton*>(ui->gridLayout->itemAtPosition(i,j)->widget());
           if (j == 0 || j ==  game_.width_ - 1) {
                 button->setStyleSheet("background-color: black");
                       }
           if (i == game_.x_ && j == game_.y_) {
                button->setStyleSheet("background-color: red");
            }
            else if (i == game_.fruitX_ && j == game_.fruitY_) {
                button->setStyleSheet("background-color: green");
            }
            else {
               bool print = false;
                for (int k = 0; k < game_.tail_; ++k) {
                    if (game_.tailX_[k] == i && game_.tailY_[k] == j && count!=0) {
                        button->setStyleSheet("background-color: red");
                        print = true;
                    }
                }
                if (!print){
                     button->setStyleSheet("background-color: black");

                    }

            }
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    count++;
    //draw();
    game_.direction_ = game_.Direction::STOP;
    switch ( event->key() ) {
            case Qt::Key_W:
                game_.direction_ = game_.Direction::UP;
                break;
            case Qt::Key_S:
                game_.direction_ = game_.Direction::DOWN;
                break;
            case Qt::Key_D:
                game_.direction_ = game_.Direction::RIGHT;
                break;
            case Qt::Key_A:
                game_.direction_ = game_.Direction::LEFT;
                break;
            case Qt::Key_X:
                game_.direction_ =game_.Direction::STOP;
                game_.gameOver = true;
                // this->gameOver();
                break;
            default:
                break;

    }
    logic();
}

void MainWindow::logic() {
    int prevX = game_.tailX_[0];
    int prevY = game_.tailY_[0];
    game_.tailX_[0] = game_.x_;
    game_.tailY_[0] = game_.y_;
    int tempX = 0, tempY = 0;
    for (int i = 1; i < game_.tail_; ++i) {
        tempX = game_.tailX_[i];
        tempY = game_.tailY_[i];
        game_.tailX_[i] = prevX;
        game_.tailY_[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }


    switch (game_.direction_) {

    case game_.Direction::UP:
        --game_.x_;
        break;
    case game_.Direction::DOWN:
        ++game_.x_;
        break;
    case game_.Direction::RIGHT:
        ++game_.y_;
        break;
    case game_.Direction::LEFT:
        --game_.y_;
        break;
    default:
        break;

    }
    if (game_.x_ > game_.width_ || game_.x_ < 0 || game_.y_ < 0 || game_.y_ > game_.height_) {
        game_.gameOver = true;
       // this->gameOver();
    }
    if (game_.x_ == game_.fruitX_ && game_.y_ == game_.fruitY_) {
        game_.score_ += 10;
        ++game_.tail_;
        game_.fruitX_ = rand() % game_.height_;
        game_.fruitY_ = rand() % game_.width_;
    }
    draw();
}

