#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tetrisclasses.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QColor>
#include <QKeyEvent>

class TetrisGame;
class TetrisBlock;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateRequest(TetrisBlock *block);
    void updateSingleBlock(SingleBlock *block);


public slots:
    void keyPressEvent(QKeyEvent* key);

private slots:
    updateNow();

private:

    Ui::MainWindow *ui;

    QGraphicsScene *scene_;

    QTimer *timer_;

    TetrisGame *game_;

    std::vector<QGraphicsLineItem*> lines_;

    std::vector<TetrisBlock*> blocks_;
};

#endif // MAINWINDOW_H
