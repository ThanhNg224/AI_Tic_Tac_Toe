#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include <string>
#include <vector>
#include <tuple>

class ReplayManager {
public:
    void recordMove(int row, int col, char player); // Record a move
    void saveToFile(const std::string &filename);   // Save moves to a file
    bool loadFromFile(const std::string &filename); // Load moves from a file
    const std::vector<std::tuple<int, int, char>>& getMoves() const; // Get all moves

private:
    std::vector<std::tuple<int, int, char>> moves; // Stores moves as (row, col, player)
};

#endif
