#ifndef BOWLINGPROGRAM_BOWLINGHEADER_H
#define BOWLINGPROGRAM_BOWLINGHEADER_H

#include <iostream>
#include <iomanip>
using namespace std;

struct player
{
    int f_scores[10];  //Final scores for each frame.
    int b_scores[21];  //Scores for each box in a frame.
};

class Bowling  //Bowling class
{

public:

    void MainMenu();  //Function that just displays the menu.

    bool validCharCheck(char c);  //Function that checks if the input that the user entered is valid.

    void grabBoxScores(struct player p_player[]);  //Function that grabs the scores for every box in every frame.

    void calculateFrames(struct player p_player[]); //Function that calculates the scores for every frame.

    void displayFrames(struct player p_player[]);  //Function that displays the frame scores.

    void displayTotal(struct player p_player[]);  //Function that displays the total ending score (The last frame value)

    void start();  //Function used to display the starting menu and allow user choice to be made.

private:

    player n_players[5];  //Make an array of player structures.

    int MAX_FRAMES = 10;  //Max number of frames per game.
    const int ASCII_conv = 48;  //Constant used to convert characters to realistic "real" numbers.
    int roll = 0;  //Variable used to keep track of what roll you are on.
    char c_flag = 0;  //Flag used to check if a strike or spare is present
    int choice;  //Choice for the switch statement and amount of players.

};

#endif //BOWLINGPROGRAM_BOWLINGHEADER_H
