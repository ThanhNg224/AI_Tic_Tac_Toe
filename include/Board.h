#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board(int size = 10);

    void display() const;
    bool placeMark(int row, int col, char mark);
    bool isCellEmpty(int row, int col) const;
    int getSize() const { return size; }
    void clearBoard();

    // Method to check if a given mark ('X' or 'O') has won
    bool checkForWin(char mark) const;

    // Get the character at a specific cell
    char getCell(int r, int c) const;

    // New method: Remove a mark from a specific cell
    bool removeMark(int row, int col);

private:
    int size;
    std::vector<std::vector<char>> grid;

    // Helper method for winner checking
    bool checkDirection(int row, int col, int dRow, int dCol, char mark) const;
};

#endif // BOARD_H
