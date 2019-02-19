#ifndef OTHELLO_GAME
#define OTHELLO_GAME

#include "board.h"
#include "player.h"

using namespace std;

class Game {
public:
    Game(int boardRows) {
        board = new Board(boardRows);

        player1 = new Player("black");
        player2 = new PlayerAI("white");
    }

    ~Game() {
        delete board;
        delete player1;
        delete player2;
    }

    void playGame() {
        do {
            board->displayBoard();
        } while (this->movesAvailable());
    }

    bool movesAvailable() {
        return false;
    }


private:
    Board* board;
    Player* player1;
    Player* player2;
};

#endif
