//
// Created by Wesley on 24/11/2023.
//

#include "scoreSheet.h"
#include <iostream>
#include <fstream>
#include <algorithm>

scoreSheet::scoreSheet() = default;

// Function to insert a pair into the vector in the correct ordered place
void scoreSheet::insertOrdered(const std::pair<std::string, int>& newPair) {
    auto it = std::lower_bound(scores.begin(), scores.end(), newPair,
                               [](const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) {
                                   return lhs.second < rhs.second;
                               });

    scores.insert(it, newPair);
}

// Function to display all pairs in the scores vector
void scoreSheet::displayScores() const {
    for (const auto &pair: scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

std::pair<std::string, int> scoreSheet::createPair(std::string name, int score) {
    return std::make_pair(name, score);
}

void scoreSheet::setPlayerName() {
    std::cout << "Enter your name: ";
    std::string playerName;
    std::getline(std::cin, playerName);
    _playerName = playerName;
}

std::string scoreSheet::getPlayerName() {
    return _playerName;
}

