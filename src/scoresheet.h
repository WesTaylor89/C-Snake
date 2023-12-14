//
// Created by Wesley on 24/11/2023.
//

#ifndef SDL2TEST_SCORESHEET_H
#define SDL2TEST_SCORESHEET_H


#include <string>
#include <vector>
#include <iostream>

class Scoresheet {
public:
    // Constructor
    Scoresheet();

    // Function to insert a pair into the vector in the correct ordered place
    void insertOrdered(const std::pair<std::string, int>& newPair);

    // Function to display scores.
    void displayScores() const;

    // Creates a new player/_score pair.
    std::pair<std::string, int> createPair(std::string name, int score);

    // Set player name
    void setPlayerName(std::string playerName);
    std::string getPlayerName();

private:
    std::vector<std::pair<std::string, int>> scores;
    std::string _playerName;

};


#endif
