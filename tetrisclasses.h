#ifndef TETRISCLASSES_H
#define TETRISCLASSES_H

#include <cstdint>
#include <vector>
#include "mainwindow.h"
#include <tetrisutils.h>

#include <QTimer>
#include <QGraphicsRectItem>

class MainWindow;

class TetrisBlock {
public:
    TetrisBlock(const BlockType w_type, int col);
    ~TetrisBlock();

    const BlockType& getType() const;
    const QColor getColor() const;

    std::vector<SingleBlock*> body_;
    std::vector<QGraphicsRectItem*> m_items;

    void move(int x_offset, int y_offset);

    int state = 0;

private:
    BlockType blockType_;
    QColor blockColor_;

};

class TetrisGrid {
public:
    TetrisGrid(uint32_t w_rows, uint32_t w_cols, MainWindow *mainWindow);
    virtual
    ~TetrisGrid();

    void clearAll();

    void tryToMove(int x_offset, int y_offset);
    void tryToRotate();

    void spawnBlock();
    void freeze();
    void checkRows();
    void deleteRow(int row);

    bool canBlockFit(int x_offset, int y_offset);
    bool isBlockAtBottom();
    bool checkRow(int row);

private:

    bool isOccupied(int row, int col);

    int m_rows;
    int m_cols;

    std::vector<SingleBlock> frozenBlocks_;

    MainWindow *mainWindow_ = nullptr;

    TetrisBlock *currBlock_;
    TetrisBlock *nextBlock_;
};


class TetrisGame {
public:
    TetrisGame (TetrisGrid* w_tetrisGrid);
    virtual
    ~TetrisGame ();

    void tick();
    void keyPress(QKeyEvent* key);


private:
    TetrisGrid *tetrisGrid_;

};
#endif /* TETRISCLASSES_H */
