#ifndef BOARD
#define BOARD

using namespace std;

class Board {
public:
    Board(int rowCount) {
        rows = rowCount;
        board = new char*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new char[rows];
            for (int j = 0; j < rows; j++) {
                board[i][j] = 'g';
            }
        }

        // init board
        board[rowCount/2][rowCount/2] = 'w';
        board[(rowCount/2)-1][(rowCount/2)-1] = 'w';
        board[(rowCount/2)][(rowCount/2)-1] = 'b';
        board[(rowCount/2)-1][(rowCount/2)] = 'b';
    }

    ~Board() {
        for (int i = 0; i < rows; i++) {
            delete [] board[i];
        }
        delete [] board;
    }

    void displayBoard() {
        for (int i = 0; i < rows; i++) {
            printf("[");
            for (int j = 0; j < rows; j++) {
                printf("%c", board[i][j]);
                if (j != rows - 1) printf(" ");
            }
            printf("]\n");
        }
    }

    void movesAvailable(string colorMarker) {
        
    }

private:
    char** board;
    int rows;
};

#endif
