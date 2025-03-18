#ifndef BOT_H
#define BOT_H

#include "Board.h"
#include <utility> // for std::pair
#include <vector>

class Bot {
public:
    // difficulty: 1 = Easy, 2 = Normal, 3 = Hard
    Bot(int difficulty, char botMark, char humanMark);

    // Get next move for the bot
    std::pair<int,int> getMove(const Board &board);

private:
    int difficulty;
    char botMark;
    char humanMark;

    // Easy: random move
    std::pair<int,int> getEasyMove(const Board &board);

    // Normal: tries to block human if they are about to win, else random
    std::pair<int,int> getNormalMove(const Board &board);

    // Hard: uses a simple minimax search
    std::pair<int,int> getHardMove(const Board &board);

    // Helpers
    bool canBlockWin(const Board &board, int &outRow, int &outCol);
    bool isMoveWinning(Board board, int r, int c, char mark);

    // Minimax related
    int evaluateBoard(const Board &board) const;
    int minimax(Board board, int depth, bool isMaximizing, int alpha, int beta);

    // Check how many potential 5-lines exist for a mark (simplified scoring)
    int countPotentialFives(const Board &board, char mark) const;
    bool canFormFive(const Board &board, int startR, int startC, int dR, int dC, char mark) const;
};

#endif
