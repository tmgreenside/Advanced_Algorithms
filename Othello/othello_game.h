#ifndef OTHELLO_GAME
#define OTHELLO_GAME

#include "board.h"

class Game {
public:
    Game(int boardRows) {
        board = new Board(boardRows);
    }

    ~Game() {
        delete board;
    }

    void playGame() {
        board->displayBoard();
    }
private:
    Board* board;
};

#endif
