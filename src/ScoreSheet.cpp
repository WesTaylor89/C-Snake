//
// Created by Wesley on 24/11/2023.
//

#include "ScoreSheet.h"
#include <iostream>
#include <fstream>
#include <algorithm>

ScoreSheet::ScoreSheet() = default;

// Function to insert a pair into the vector in the correct ordered place
void ScoreSheet::insertOrdered(const std::pair<std::string, int>& newPair) {
    auto it = std::lower_bound(scores.begin(), scores.end(), newPair,
                               [](const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) {
                                   return lhs.second < rhs.second;
                               });

    scores.insert(it, newPair);
}

// Function to display all pairs in the scores vector
void ScoreSheet::displayScores() const {
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}