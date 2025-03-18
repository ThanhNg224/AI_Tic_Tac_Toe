#include "Menu.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

// ANSI color codes (you can change these as desired)
#define RESET      "\033[0m"
#define BOLD       "\033[1m"
#define RED        "\033[31m"
#define GREEN      "\033[32m"
#define YELLOW     "\033[33m"
#define BLUE       "\033[34m"
#define MAGENTA    "\033[35m"
#define CYAN       "\033[36m"
#define WHITE      "\033[37m"
#define UNDERLINE  "\033[4m"

Menu::Menu(const std::string& title, const std::vector<std::string>& options)
    : title(title), options(options) {}

void Menu::printHeader(const std::string& text) const {
    // Determine width based on text length
    int width = static_cast<int>(text.size()) + 6; 
    // Print a top border
    std::cout << YELLOW << "*";
    for (int i = 0; i < width; ++i) std::cout << "-";
    std::cout << "*\n";

    // Print the title line
    // Add padding so the title is centered-ish
    std::cout << "|  " << BOLD << text << RESET << YELLOW << "  |\n";

    // Print bottom border
    std::cout << "*";
    for (int i = 0; i < width; ++i) std::cout << "-";
    std::cout << "*" << RESET << "\n";
}

void Menu::display() const {
    // Clear screen (optional): 
    // std::cout << "\033[2J\033[1;1H"; // Clears screen and moves cursor to top-left

    // Print the header
    printHeader(title);

    std::cout << CYAN << "Press number to choose:" << RESET << "\n\n";

    for (size_t i = 0; i < options.size(); ++i) {
        // Color each option differently if you like
        std::cout << GREEN << (i+1) << ". " << RESET << WHITE << options[i] << RESET << "\n";
    }
    std::cout << "\n" << BLUE << "Your choice: " << RESET;
}

int Menu::getUserChoice() const {
    int choice;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(options.size())) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << RED << "Invalid choice. " << RESET << "Please choose between 1 and " 
                      << options.size() << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return choice;
}

void Menu::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Menu::setOptions(const std::vector<std::string>& newOptions) {
    options = newOptions;
}
