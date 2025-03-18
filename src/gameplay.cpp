#include "gameplay.h"
#include "Board.h"
#include "Bot.h"
#include <iostream>
#include <limits>

void playTwoPlayerGame() {
    Board board(10); // 10x10 board
    board.display();

    char currentPlayer = 'X'; // Player 1 is 'X', Player 2 is 'O'
    int moves = 0;
    int maxMoves = board.getSize() * board.getSize();

    while (moves < maxMoves) {
        int row, col;
        std::cout << "Player " << (currentPlayer == 'X' ? 1 : 2)
                  << " (" << currentPlayer << "), enter row and col: ";
        std::cin >> row >> col;

        // Input validation
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter two integers.\n";
            continue;
        }

        // Place the mark
        if (board.placeMark(row, col, currentPlayer)) {
            board.display();
            moves++;

            // Check for a winner
            if (board.checkForWin(currentPlayer)) {
                std::cout << "Player " << (currentPlayer == 'X' ? 1 : 2)
                          << " (" << currentPlayer << ") wins!\n";
                break;
            }

            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

        } else {
            std::cout << "Invalid move. Try again.\n";
        }

        // Check for a draw
        if (moves == maxMoves) {
            std::cout << "It's a draw! No more moves left.\n";
        }
    }
}

void playWithBotGame(int difficulty) {
    Board board(10); // 10x10 board
    board.display();

    char humanMark = 'X'; // Human is 'X'
    char botMark = 'O';   // Bot is 'O'
    Bot bot(difficulty, botMark, humanMark);

    int moves = 0;
    int maxMoves = board.getSize() * board.getSize();
    char currentPlayer = humanMark; // Human always starts

    while (moves < maxMoves) {
        if (currentPlayer == humanMark) {
            // Human's turn
            int row, col;
            std::cout << "Your turn (X), enter row and col: ";
            std::cin >> row >> col;

            // Input validation
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers.\n";
                continue;
            }

            // Place the human's mark
            if (board.placeMark(row, col, humanMark)) {
                moves++;
                board.display();

                // Check for a winner
                if (board.checkForWin(humanMark)) {
                    std::cout << "You win!\n";
                    break;
                }

                // Switch to bot's turn
                currentPlayer = botMark;

            } else {
                std::cout << "Invalid move. Try again.\n";
            }

        } else {
            // Bot's turn
            std::cout << "Bot (O) is thinking...\n";

            // Get the bot's move
            auto move = bot.getMove(board);
            int r = move.first;
            int c = move.second;

            if (r == -1 || c == -1) {
                // No valid moves left
                std::cout << "No moves left. It's a draw!\n";
                break;
            }

            // Place the bot's mark
            board.placeMark(r, c, botMark);
            moves++;
            board.display();

            // Check for a winner
            if (board.checkForWin(botMark)) {
                std::cout << "Bot (O) wins!\n";
                break;
            }

            // Switch to human's turn
            currentPlayer = humanMark;
        }

        // Check for a draw
        if (moves == maxMoves) {
            std::cout << "It's a draw! No more moves left.\n";
        }
    }
}
