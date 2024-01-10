//
// Created by Wesley on 24/11/2023.
//

#include "scoresheet.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Scoresheet::Scoresheet() = default;

// Function to insert a pair into the vector in the correct ordered place
void Scoresheet::insertOrdered(const std::pair<std::string, int>& newPair) {
    auto it = std::lower_bound(scores.begin(), scores.end(), newPair,
                               [](const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) {
                                   return lhs.second < rhs.second;
                               });

    scores.insert(it, newPair);
}

// Function to display all pairs in the scores vector
void Scoresheet::displayScores() const {
    for (const auto &pair: scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

std::pair<std::string, int> Scoresheet::createPair(std::string name, int score) {
    return std::make_pair(name, score);
}

void Scoresheet::setPlayerName(std::string playerName) {
    _playerName = playerName;
}

std::string Scoresheet::getPlayerName() {
    return _playerName;
}

const std::vector<std::pair<std::string, int>> &Scoresheet::getScores() const {
    return scores;
}

