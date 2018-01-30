#ifndef TETRISUTILS_H
#define TETRISUTILS_H

#include <vector>

typedef struct SingleBlock {

    int x;
    int y;

    SingleBlock(int x_, int y_) : x(x_), y(y_) {}

    bool sameCoords(int x_test, int y_test)
    {
        return ((x==x_test) && (y==y_test));
    }

} SingleBlock;


enum GameState {
    sStop,  // ?? turhaa?
    sPlay,
    sPause,
    sGameOver,
    sQuit
};

enum BlockType {
    tI,
    tO,
    tT,
    tS,
    tZ,
    tJ,
    tL
};


#endif /* TETRISUTILS_H_ */
