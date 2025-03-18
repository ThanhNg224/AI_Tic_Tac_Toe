#include "ReplayManager.h"
#include <fstream>
#include <tuple>
#include <iostream>

void ReplayManager::recordMove(int row, int col, char player) {
    moves.emplace_back(row, col, player);
}

void ReplayManager::saveToFile(const std::string &filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }
    std::cout << "Replay saved to: " << filename << "\n"; // Print save location
    for (const auto &move : moves) {
        outFile << std::get<0>(move) << " " << std::get<1>(move) << " " << std::get<2>(move) << "\n";
    }
    outFile.close();
}


bool ReplayManager::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filename << "\n";
        return false;
    }

    moves.clear();
    int row, col;
    char player;
    while (inFile >> row >> col >> player) {
        moves.emplace_back(row, col, player);
    }
    inFile.close();
    return true;
}

const std::vector<std::tuple<int, int, char>>& ReplayManager::getMoves() const {
    return moves;
}
