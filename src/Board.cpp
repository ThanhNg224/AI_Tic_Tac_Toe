#include "Board.h"
#include <iostream>

Board::Board(int size)
    : size(size), grid(size, std::vector<char>(size, ' '))
{
}

void Board::display() const {
    #define RESET   "\033[0m"
    #define MAGENTA "\033[35m"
    #define YELLOW  "\033[33m"
    #define CYAN    "\033[36m"

    // Print column headers
    std::cout << "     ";
    for (int c = 0; c < size; c++) {
        // Each column number centered in a 3-char wide cell
        if (c < 10) 
            std::cout << " " << MAGENTA << c << RESET << "  ";
        else        
            std::cout << MAGENTA << c << RESET << "  "; 
    }
    std::cout << "\n";

    // Print the top border
    std::cout << "     ";
    for (int c = 0; c < size; c++) {
        std::cout << YELLOW << "+---" << RESET;
    }
    std::cout << YELLOW << "+" << RESET << "\n";

    // Print rows
    for (int r = 0; r < size; r++) {
        // Row index alignment
        if (r < 10) 
            std::cout << "   " << MAGENTA << r << RESET << " ";
        else        
            std::cout << "  " << MAGENTA << r << RESET << " ";

        // Print each cell in the row
        for (int c = 0; c < size; c++) {
            char cell = grid[r][c];
            std::cout << YELLOW << "|" << RESET;
            if (cell == 'X') {
                std::cout << " X ";
            } else if (cell == 'O') {
                std::cout << " O ";
            } else {
                std::cout << "   ";
            }
        }
        // Right border
        std::cout << YELLOW << "|\n" << RESET;

        // Print horizontal separator after each row
        std::cout << "     ";
        for (int c = 0; c < size; c++) {
            std::cout << YELLOW << "+---" << RESET;
        }
        std::cout << YELLOW << "+" << RESET << "\n";
    }

    #undef RESET
    #undef MAGENTA
    #undef YELLOW
    #undef CYAN
}

bool Board::placeMark(int row, int col, char mark) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        std::cout << "Invalid position. Try again.\n";
        return false;
    }
    if (grid[row][col] != ' ') {
        std::cout << "Cell is already occupied. Try another.\n";
        return false;
    }
    if (mark != 'X' && mark != 'O') {
        std::cout << "Invalid mark. Use 'X' or 'O' only.\n";
        return false;
    }

    grid[row][col] = mark;
    return true;
}

bool Board::isCellEmpty(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false;
    }
    return grid[row][col] == ' ';
}

void Board::clearBoard() {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            grid[r][c] = ' ';
        }
    }
}

// Get the character at a specific cell
char Board::getCell(int r, int c) const {
    if (r < 0 || r >= size || c < 0 || c >= size) {
        return ' ';
    }
    return grid[r][c];
}

// Check in a particular direction if we have 5 in a row
bool Board::checkDirection(int row, int col, int dRow, int dCol, char mark) const {
    for (int i = 0; i < 5; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        if (r < 0 || r >= size || c < 0 || c >= size)
            return false;
        if (grid[r][c] != mark)
            return false;
    }
    return true;
}

bool Board::checkForWin(char mark) const {
    // Check horizontally, vertically and diagonally for a 5-in-a-row
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] == mark) {
                // Check all directions
                if (checkDirection(r, c, 0, 1, mark) ||
                    checkDirection(r, c, 1, 0, mark) ||
                    checkDirection(r, c, 1, 1, mark) ||
                    checkDirection(r, c, 1, -1, mark)) {
                    return true;
                }
            }
        }
    }
    return false;
}
