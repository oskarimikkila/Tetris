#include <iostream>

#include "tetrisclasses.h"
#include "tetrisutils.h"

const BlockType blocks[] = {tI, tO, tT, tS, tZ, tJ, tL};

/*
 *  TETRIS BLOCK CLASS FUNCTION
 */
TetrisBlock::TetrisBlock(const BlockType w_type, int col) : blockType_(w_type)
{

    switch(w_type) {
        case tI: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(0 + col, -1), new SingleBlock(0 + col, -2), new SingleBlock(0 + col, -3)};
            blockColor_ = Qt::red;
            break;
        }
        case tO: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(0 + col, -1), new SingleBlock(-1 + col, 0), new SingleBlock(1 + col, 0)};
            blockColor_ = Qt::blue;
            break;
        }
        case tT: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(0 + col, -1), new SingleBlock(-1 + col, 0), new SingleBlock(1 + col, 0)};
            blockColor_ = Qt::green;
            break;
        }
        case tS: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(1 + col, 0), new SingleBlock(1 + col, -1), new SingleBlock(2 + col, -1)};
            blockColor_ = Qt::yellow;
            break;
        }
        case tZ: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(0 + col, -1), new SingleBlock(-1 + col, -1), new SingleBlock(1 + col, 0)};
            blockColor_ = Qt::darkMagenta;
            break;
        }
        case tJ: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(1 + col, 0), new SingleBlock(1 + col, -1), new SingleBlock(1 + col, -2)};
            blockColor_ = Qt::darkCyan;
            break;
        }
        case tL: {
            body_ = {new SingleBlock(0 + col, 0), new SingleBlock(1 + col, 0), new SingleBlock(0 + col, -1), new SingleBlock(0 + col, -2)};
            blockColor_ = Qt::darkRed;
            break;
        }
        default: {
            break;
        }
    }

    m_items.resize(body_.size(), nullptr);
}

TetrisBlock::~TetrisBlock()
{
    for (auto b: body_) {

        delete b;

    }

}

const BlockType& TetrisBlock::getType() const
{
    return blockType_;
}

const QColor TetrisBlock::getColor() const
{
    return blockColor_;
}

void TetrisBlock::move(int x_offset, int y_offset)
{
    for (auto sBlock : body_) {
        sBlock->y = sBlock->y + y_offset;
        sBlock->x = sBlock->x + x_offset;
    }
}

/*
 *  TETRIS PLAYGRID CLASS FUNCTIONS
 */
TetrisGrid::TetrisGrid(uint32_t w_rows, uint32_t w_cols, MainWindow *mainWindow)
    : m_rows(w_rows + 4), m_cols(w_cols),
      mainWindow_(mainWindow)
{
    currBlock_ = new TetrisBlock(tO, 3);
    nextBlock_ = new TetrisBlock(tL, 3);

}

TetrisGrid::~TetrisGrid()
{

}

bool TetrisGrid::canBlockFit(int x_offset, int y_offset)
{

    for (auto sBlock : currBlock_->body_) {
        if (int (sBlock->y + y_offset) > int(m_rows)) {
            return false;

        } else if (int (sBlock->x + x_offset) >= int(m_cols)) {
            return false;

        } else if (int(sBlock->x + x_offset) < 0 ) {
            return false;

        }

        for (auto fBlock : frozenBlocks_) {

            if (fBlock.sameCoords(sBlock->x + x_offset, sBlock->y + y_offset)) {
                    return false;
            }
        }
    }
    return true;
}

bool TetrisGrid::isOccupied(int row, int col)
{
    return row==col;
}


void TetrisGrid::tryToMove(int x_offset, int y_offset)
{
    if (canBlockFit(x_offset, y_offset)) {
        currBlock_->move(x_offset, y_offset);
        mainWindow_->updateRequest(currBlock_);
    }
}

void TetrisGrid::tryToRotate()
{
    // Turn around these
    int turn_x = currBlock_->body_[0]->x;
    int turn_y = currBlock_->body_[0]->y;
    int x_offs;
    int y_offs;

    for (int i = 1; i < currBlock_->body_.size(); i++) {

        x_offs = currBlock_->body_[i]->x - turn_x;
        y_offs = currBlock_->body_[i]->y - turn_y;

        currBlock_->body_[i]->y = currBlock_->body_[i]->y + x_offs - y_offs;
        currBlock_->body_[i]->x = currBlock_->body_[i]->x - y_offs - x_offs;
    }

}

void TetrisGrid::spawnBlock()
{
    delete currBlock_;
    currBlock_ = new TetrisBlock(nextBlock_->getType(), 3);

    delete nextBlock_;
    nextBlock_ = new TetrisBlock(blocks[ ( rand()%(8) ) ], 5);
}

bool TetrisGrid::isBlockAtBottom()
{
    return !canBlockFit(0, 1);
}

void TetrisGrid::freeze() // TODO: return false
{

    for (auto blck : currBlock_->body_) {
        frozenBlocks_.push_back(*blck);
    }

    spawnBlock();
}

void TetrisGrid::checkRows()
{
    for (int i = 0; i <= m_rows; i++) {
        if (checkRow(i)) {
            std::cout << "row " << i << std::endl;
            deleteRow(i);
        }

    }
}

void TetrisGrid::deleteRow(int row)
{
    std::vector<SingleBlock*> pointers;

    for (auto block : frozenBlocks_) {

        if (block.y = row) {
            pointers.push_back(&block);
        }
    }


    for (auto blk : pointers) {

        blk->y


        //mainWindow_->updateSingleBlock(blk);
    }
}

bool TetrisGrid::checkRow(int row) {

    std::vector<int> found_x;

    for (auto block : frozenBlocks_) {
        if (block.y == row) found_x.push_back(block.x);
    }

    for (int col = 0; col < m_cols; col++) {
        if (std::find(found_x.begin(), found_x.end(), col) == found_x.end()) return false;
    }

    return true;
}

/*
 *  GAME PLACEHOLDER CLASS FUNCTIONS
 */
TetrisGame::TetrisGame(TetrisGrid * w_tetrisGrid) : tetrisGrid_(w_tetrisGrid)
{

}

TetrisGame::~TetrisGame ()
{
    // TODO Auto-generated destructor stub
}

void TetrisGame::tick()
{

    if (tetrisGrid_->isBlockAtBottom()) {
        tetrisGrid_->freeze();
    } else {
        tetrisGrid_->tryToMove(0, 1);
    }

    tetrisGrid_->checkRows();

}

void TetrisGame::keyPress(QKeyEvent *key)
{
    if (key->key() == Qt::Key_Left) {
        tetrisGrid_->tryToMove(-1, 0);
    } else if (key->key() == Qt::Key_Right) {
        tetrisGrid_->tryToMove(1, 0);
    } else if (key->key() == Qt::Key_Down) {
        tick();
    } else if (key->key() == Qt::Key_Up) {
        tetrisGrid_->tryToRotate();
    }
}




