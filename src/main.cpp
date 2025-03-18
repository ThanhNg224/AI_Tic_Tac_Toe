#include <iostream>
#include <thread>
#include <chrono>
#include "Menu.h"
#include <limits>
#include "Board.h"
#include "Bot.h"
#include "Gameplay.h"
#include "ReplayManager.h" // Add ReplayManager

void playTwoPlayerGame();
void playWithBotGame(int difficulty);
void replayGame(); // Updated implementation

int main() {
    std::vector<std::string> mainOptions = {
        "Play with Other Player",
        "Play with BOT",
        "Replay",
        "Player's Information",
        "Guide",
        "Exit"
    };

    Menu mainMenu("MAIN MENU", mainOptions);

    while (true) {
        mainMenu.display();
        int mainChoice = mainMenu.getUserChoice();

        switch (mainChoice) {
            case 1:
                playTwoPlayerGame();
                break;

            case 2: {
                std::vector<std::string> botOptions = {
                    "Easy Mode",
                    "Normal Mode",
                    "Hard Mode",
                    "Back to MAIN MENU"
                };
                Menu botMenu("Play with BOT", botOptions);
                bool inBotMenu = true;
                while (inBotMenu) {
                    botMenu.display();
                    int botChoice = botMenu.getUserChoice();
                    switch (botChoice) {
                        case 1:
                            std::cout << "Easy Mode selected.\n";
                            playWithBotGame(1);
                            break;
                        case 2:
                            std::cout << "Normal Mode selected.\n";
                            playWithBotGame(2);
                            break;
                        case 3:
                            std::cout << "Hard Mode selected.\n";
                            playWithBotGame(3);
                            break;
                        case 4:
                            std::cout << "Returning to MAIN MENU...\n";
                            inBotMenu = false;
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }

            case 3:
                replayGame(); // Updated
                break;

            case 4:
                std::cout << "Player's Information (TODO: Implement).\n";
                break;

            case 5:
                std::cout << "Guide:\n";
                std::cout << " - The goal is to get 5 marks in a row (horizontal, vertical, or diagonal).\n";
                std::cout << " - Player 1 is 'X', Player 2 (or Bot) is 'O'.\n";
                std::cout << " - Bot Difficulty Levels:\n";
                std::cout << "   * Easy: Bot makes random moves.\n";
                std::cout << "   * Normal: Bot tries to block your winning moves.\n";
                std::cout << "   * Hard: Bot uses advanced strategies to win.\n";
                std::cout << "Press ENTER to return to the menu.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;

            case 6:
                std::cout << "Exiting game. Goodbye!\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please select a valid option from the menu.\n";
                break;
        }
    }

    return 0;
}

void replayGame() {
    ReplayManager replayManager;
    std::string filename;
    std::cout << "Enter filename to load replay: ";
    std::cin >> filename;

    if (!replayManager.loadFromFile(filename)) {
        std::cout << "Failed to load replay.\n";
        return;
    }

    Board board(10); // 10x10 board
    board.display();

    for (const auto &move : replayManager.getMoves()) {
        int row, col, player;
        std::tie(row, col, player) = move;
        std::cout << "Replaying move: Player " << player << " at (" << row << ", " << col << ")\n";
        board.placeMark(row, col, player);
        board.display();
        
    }

    std::cout << "Replay finished.\n";
}
