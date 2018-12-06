#include <iostream>
#include <cstdlib>

#include "othello_game.h"

using namespace std;

int main() {
    Game* theGame = new Game(8);
    theGame->playGame();
    delete theGame;
    cout << "Execution completed" << endl;
}
