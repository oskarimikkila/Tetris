#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

const int UPDATE_TIME = 200;

static GameState gameState = sPlay;

static const double cFPS = 60;
static const double cDeltaTime = 1 / cFPS;

static const double cTickRate = 1.0 / 120.0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Set up graphics
    scene_ = new QGraphicsScene(this);
    scene_ ->setSceneRect(0, 0, 100, 200);
    ui->graphicsView->setScene(scene_);


    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);


    int frameW = 400;
    int frameH = 800;
    int sceneW = 100;
    int sceneH = 200;

    ui->graphicsView->scale(frameW / sceneW, frameH / sceneH);

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for (int i = 0; i < 21; i++) {

        lines_.push_back(scene_->addLine(0, i*10, 100, i*10, blackPen));

    }

    for (int i = 0; i < 11; i++) {

        lines_.push_back(scene_->addLine(i*10, 0, i*10, 200, blackPen));

    }

    // Set up game

    TetrisGrid *fgrid = new TetrisGrid(20, 10, this);
    game_ = new TetrisGame(fgrid);

    // set up timer

    timer_ = new QTimer(this);

    timer_->start(UPDATE_TIME);

    connect(timer_, SIGNAL(timeout()), SLOT(updateNow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateRequest(TetrisBlock *block)
{
    int x_coord;
    int y_coord;

    QColor color = block->getColor();

    for (int j = 0; j < block->body_.size(); j++) {

        x_coord = block->body_[j]->x * 10;
        y_coord = (block->body_[j]->y - 5)* 10;

        if (block->m_items[j] == nullptr) {
            block->m_items[j] = scene_->addRect(0, 0, 10, 10, QPen(Qt::black), QBrush(color));
        }
        block->m_items[j]->setPos(x_coord, y_coord);

    }
}

void MainWindow::updateSingleBlock(SingleBlock *block)
{

}

MainWindow::updateNow()
{

    game_->tick();
    timer_->start(UPDATE_TIME);
}


void MainWindow::keyPressEvent(QKeyEvent* key)
{
    game_->keyPress(key);
}
