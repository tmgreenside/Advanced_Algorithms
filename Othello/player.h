#ifndef PLAYER
#define PLAYER

#include <string>

#include "board.h"

using namespace std;

class Player {
public:
    Player(string colorIn) {
        if (!colorIn.compare("black")) colorMarker = 'b';
        else colorMarker = 'w';
    }

    ~Player(){
        return;
    }

    void movesAvailable(Board* board) {
        board->showMoves(colorMarker);
    }

private:
    char colorMarker;
};

class PlayerAI : public Player {
public:
    PlayerAI(string colorIn) : Player(colorIn) {
        cout << "Just ran subclass constructor" << endl;
    }
};

#endif
