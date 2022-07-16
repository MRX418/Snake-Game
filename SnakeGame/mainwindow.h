#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snakegame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override = default;;
    void intro();
    void draw();
    void logic();
signals:
    void set();
protected:
     void keyPressEvent(QKeyEvent *event) override;
public slots:
    void start();

private:
    Ui::MainWindow *ui;
    SnakeGame game_;
};
#endif // MAINWINDOW_H