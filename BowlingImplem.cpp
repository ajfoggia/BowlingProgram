#include "bowlingHeader.h"
#include <iostream>
#include <iomanip>  //Library used for setw() for formatting
using namespace std;

void Bowling::MainMenu()  //Function that displays the menu to the terminal.
{
    cout << "What would you like to do?\n";
    cout << "1. Create a game\n";
    cout << "2. Display the frames of the previous game\n";
    cout << "3. Display the total score of the previous game\n";
    cout << "4. Show this menu again\n";
    cout << "5. Exit the program\n";
}

bool Bowling::validCharCheck(char c)  //Function to check if the user input is valid.
{
    int reg_num = 0;
    reg_num = c - ASCII_conv;

    if(c == 'X' || c == 'x')  //If there is a x, it is valid.
        return true;
    else if(c == '/')  //If there is a /, it is valid.
        return true;
    else if(reg_num <= 9)  //If it is less than or equal to 9, it is valid.
        return true;
    else  //Anything else is not valid either.
        return false;
}


void Bowling::grabBoxScores(struct player p_player[])  //Function that grabs the scores of every box in every frame.
{
    bool valid;  //Variable to hold whether a user's input is valid.

    for (int p = 1; p <= 4; p++)  //Loop that keeps track of which player is being totaled.
    {
        roll = 0;  //Roll number is re-initialized.
        cout << "\nPlayer " << p << "'s score is now being totaled.";

        for (int f = 1; f <= MAX_FRAMES; f++)  //Loop that controls which frame is being totaled.
        {
            if (f != MAX_FRAMES)   //As long as it isn't the last frame, calculate the other frames.
            {
                cout << "\nPlease enter in the score for the first box in frame " << f << ": ";
                cin >> c_flag;

                valid = validCharCheck(c_flag);  //Check to make sure that the input is valid.

                if (valid == true)  //If the input is valid, put the input in the box.
                {
                    if (c_flag == 'X' || c_flag == 'x')  //If the input is a strike.
                    {
                        p_player[p].b_scores[roll] = 10;  //Set first box to 10.
                        cout << "STRIKE!!!!\n";
                        cout << "First box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                        roll++;
                        p_player[p].b_scores[roll] = 0;  //Set second box to 0.
                        roll++;
                    }
                    else  //Otherwise, the input is just a number between 0-9.
                    {
                        p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                        cout << "First box for frame " << " = " << p_player[p].b_scores[roll] << "\n";
                        roll++;

                        c_flag = 0;  //Re-initialize the flag.

                        cout << "\nNow enter in the score for the second box: ";
                        cin >> c_flag;

                        if (c_flag == '/')  //If the input is a spare.
                        {
                            p_player[p].b_scores[roll] = 10 - p_player[p].b_scores[roll - 1];  //Find the difference out of 10 to put correct value in box.
                            cout << "SPARE!!!!\n";
                            cout << "Second box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                        else  //Otherwise, the input is just another number between 0-9.
                        {
                            p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                            cout << "Second box for frame " << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }

                        c_flag = 0;  //Re-initialize the flag.
                    }
                }
                else  //Otherwise, the first input was not valid.
                {
                    cout << "Sorry, that output is not accepted.\n";
                    cout << "Inputting a 0 for this frame.\n";
                    p_player[p].b_scores[roll] = 0;  //Fill the roll with a 0.
                    roll++;
                    p_player[p].b_scores[roll] = 0; //Fill the next roll with a 0.
                    roll++;

                    c_flag = 0;
                }
            }
            else  //It is the last frame.
            {
                c_flag = 0;
                cout << "\nPlease enter the score for the first box in the final frame (number " << f << "): ";
                cin >> c_flag;

                valid = validCharCheck(c_flag);  //Check if the input is valid.

                if (valid == true)  //If the input is valid.
                {
                    if (c_flag == 'X' || c_flag == 'x')  //If first score in final frame is a strike, two more boxes are allowed.
                    {
                        p_player[p].b_scores[roll] = 10;  //Put 10 into the first box.
                        cout << "STRIKE!!!\n";
                        cout << "First box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                        roll++;
                        c_flag = 0;

                        cout << "\nNow enter in the score for the second box: ";
                        cin >> c_flag;

                        if (c_flag == 'X' || c_flag == 'x')  //If second score is a strike, set second score to 10.
                        {
                            p_player[p].b_scores[roll] = 10;
                            cout << "SECOND STRIKE!!!!\n";
                            cout << "Second box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                        else  //Otherwise, the second score is just a number between 0-9.
                        {
                            p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                            cout << "Second box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }

                        c_flag = 0;

                        cout << "\nFinally enter in the score for the last box: ";
                        cin >> c_flag;

                        if (c_flag == 'X' || c_flag == 'x')  //If the last score is a strike, set the last score to 10.
                        {
                            p_player[p].b_scores[roll] = 10;
                            cout << "THIRD STRIKE (TURKEY)!!!\n";
                            cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                        else if (c_flag == '/')  //If the last score makes a spare, find the difference to put into the last score.
                        {
                            p_player[p].b_scores[roll] = 10 - p_player[p].b_scores[roll - 1];
                            cout << "SPARE!!!!\n";
                            cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                        else  //Otherwise, it is just a number between 0-9.
                        {
                            p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                            cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                    }
                    else  //Otherwise, the first score on the final frame is not a strike and just a number between 0-9.
                    {
                        p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                        cout << "First box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                        roll++;
                        c_flag = 0;
                        cout << "\nNow enter in the score for the second box: ";
                        cin >> c_flag;
                        if (c_flag == '/')  //If the second score makes a spare, find the difference to put into the second score.
                        {
                            p_player[p].b_scores[roll] = 10 - p_player[p].b_scores[roll - 1];
                            cout << "SPARE!!!!\n";
                            cout << "Second box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                            c_flag = 0;
                            cout << "\nFinally enter in the score for the last box: ";
                            cin >> c_flag;

                            if (c_flag == 'X' || c_flag == 'x')  //If the last score is a strike, set the last score to 10.
                            {
                                p_player[p].b_scores[roll] = 10;
                                cout << "STRIKE!!!\n";
                                cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                                roll++;
                            }
                            else  //Otherwise, it is just a number between 1-9.
                            {
                                p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                                cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                                roll++;
                            }
                        }
                        else  //Otherwise, the second box is just a number between 1-9.
                        {
                            p_player[p].b_scores[roll] = (int) c_flag - ASCII_conv;
                            cout << "Third box for frame " << f << " = " << p_player[p].b_scores[roll] << "\n";
                            roll++;
                        }
                    }
                }
                else  //Otherwise, the first input was not valid.
                {
                    cout << "Sorry, that output is not accepted.\n";
                    cout << "Inputting a 0 for this frame.\n";
                    p_player[p].b_scores[roll] = 0;  //Fill the roll with a 0.
                    roll++;
                    p_player[p].b_scores[roll] = 0;  //Fill the next roll with 0.
                    roll++;

                    c_flag = 0;
                }
            }
        }
    }
}

void Bowling::calculateFrames(player p_player[])  //Function that finds the totals for all the frames.
{
    for(int p = 1; p <= 4; p++)  //Loop that keeps track of which player you are totaling.
    {
        roll = 0;  //Initialize the roll you are on.
        for (int f = 1; f <= MAX_FRAMES; f++)  //Loop that keeps track of which frame you are on.
        {
            if (p_player[p].b_scores[roll] == 10)  //If roll is a strike, grab the next two rolls.
            {
                if (f == 1)  //If it is the first frame, there is no previous total to add to.
                {
                    p_player[p].f_scores[f] = 10;  //Set starting total to 10
                    roll++;  //Increment to skip over the 0 in box 2.
                    if (p_player[p].b_scores[roll + 1] == 10)  //If there is a second strike consecutively, add another 10
                    {
                        p_player[p].f_scores[f] += 10;
                        if (p_player[p].b_scores[roll + 3] == 10)  //If there is a third strike, add the last 10.
                        {
                            p_player[p].f_scores[f] += 10;
                            roll++;
                        }
                        else  //Otherwise, there is no third strike and you just grab the next roll.
                        {
                            p_player[p].f_scores[f] += p_player[p].b_scores[roll + 3];
                            roll++;
                        }
                    }
                    else
                    {
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll + 1] + p_player[p].b_scores[roll + 2];  //Then add the next two rolls to the total.
                        roll++;
                    }
                }
                else  //Otherwise, it is another frame and you can add the frame to the previous total.
                {
                    p_player[p].f_scores[f] = p_player[p].f_scores[f - 1] + 10;  //Add 10 to the previous total.
                    roll++;  //Increment to skip over the 0 in box 2.
                    if (f == MAX_FRAMES)  //If it is the last frame, add the extra rolls.
                    {
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll];
                        roll++;
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll];
                    }
                    else if (p_player[p].b_scores[roll + 1] == 10)  //If there is a second strike consecutively, add another 10
                    {
                        p_player[p].f_scores[f] += 10;

                        if (p_player[p].b_scores[roll + 3] == 10)  //If there is a third strike, add the last 10.
                        {
                            p_player[p].f_scores[f] += 10;
                            roll++;
                        }
                        else if (f == MAX_FRAMES - 1)  //If it is the 9th frame then just add the second roll of the final frame.
                        {
                            p_player[p].f_scores[f] += p_player[p].b_scores[roll + 2];
                            roll++;
                        }
                        else  //Otherwise, there is no third strike and you just grab the next roll.
                        {
                            p_player[p].f_scores[f] += p_player[p].b_scores[roll + 3];
                            roll++;
                        }
                    }
                    else  //Otherwise, there are no consecutive strikes and it is totaled normally.
                    {
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll + 1] + p_player[p].b_scores[roll + 2];  //Then add the next two rolls to the total.
                        roll++;
                    }
                }
            }
            else if (p_player[p].b_scores[roll] + p_player[p].b_scores[roll + 1] == 10)  //If it is a spare
            {
                if (f == 1)  //If it is the first frame.
                {
                    p_player[p].f_scores[f] = 10;  //Set starting total to 10.
                    roll++;  //Increment to skip over box 2.
                    if (p_player[p].b_scores[roll + 1] == 10)  //If there is a strike in the next box, add another 10.
                    {
                        p_player[p].f_scores[f] += 10;
                    }
                    else
                    {
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll + 1];  //Then add the next roll to the total.
                        roll++;
                    }
                }
                else if (f == MAX_FRAMES)   //If it is the final frame, add the next frame and then you get a bonus roll.
                {
                    p_player[p].f_scores[f] = p_player[p].f_scores[f - 1] + 10;
                    roll++;
                    p_player[p].f_scores[f] += p_player[p].b_scores[roll + 1];
                }
                else  //Otherwise, it is not the first frame.
                {
                    p_player[p].f_scores[f] = p_player[p].f_scores[f - 1] + 10;  //Add 10 to the previous total.
                    roll++;  //Increment to skip over the 0 in box 2.
                    if (p_player[p].b_scores[roll + 1] == 10)  //If there is a second strike consecutively, add another 10
                    {
                        p_player[p].f_scores[f] += 10;
                    }
                    else //It is just another frame.
                    {
                        p_player[p].f_scores[f] += p_player[p].b_scores[roll + 1];  //Then add the next roll to the total.
                        roll++;
                    }
                }
            }
            else  //Otherwise, a strike was not rolled and you just total the frame normally.
            {
                if (f == 1)  //If it is the first frame, there is no previous total to add to.
                {
                    p_player[p].f_scores[f] = p_player[p].b_scores[roll];  //Add first roll to total.
                    roll++;
                    p_player[p].f_scores[f] += p_player[p].b_scores[roll];  //Then add the next roll to the total.
                    roll++;
                }
                else  //Otherwise, it is another frame and you can add the frame to the previous total.
                {
                    p_player[p].f_scores[f] = p_player[p].f_scores[f - 1] + p_player[p].b_scores[roll];  //Add first roll to previous total.
                    roll++;
                    p_player[p].f_scores[f] += p_player[p].b_scores[roll];  //Then add the next roll.
                    roll++;
                }
            }
        }
    }
}

void Bowling::displayFrames(struct player p_player[])
{

    calculateFrames(p_player);  //Calculate the frame totals before displaying.

    for(int p = 1; p <= 4; p++)
    {
        cout << "/////////////////////////////////////////////////////////////////\n";
        cout << setw(11) << "Player" << setw(10) << "Frame" << setw(18) << "Frame Score\n";
        cout << setw(9) << p;
        for(int f = 1; f <= MAX_FRAMES; f++)
        {
            if(f == 1)  //If it is the first frame.
            {
                cout << setw(10) << f << setw(15) << p_player[p].f_scores[f] << "\n";
            }
            else  //Otherwise, it is another frame
            {
                cout << setw(19) << f << setw(15) << p_player[p].f_scores[f] << "\n";
            }
        }
    }
}

void Bowling::displayTotal(struct player p_player[])
{

    cout << setw(11) << "Player" << setw(16) << "Total Score\n";

    for(int p = 1; p <= 4; p++)
    {
        cout << setw(9) << p << setw(12) << p_player[p].f_scores[10] << "\n";  //Display the last frames total because that is the total score.
    }

}

void Bowling::start()
{

    cout << "Welcome to my bowling program!\n";
    MainMenu();  //Open the menu
    cin >> choice;  //Grab the users choice
    while(choice && choice != 5)  //While the choice for exit is not selected, execute switch
    {
        switch(choice)  //Switch statement to handle the choice.
        {
            case 1:  //Case 1 is creation of the game.
                cout << "Game creation in progress\n";

                grabBoxScores(n_players);

                cout << "\nGame has successfully been created!";
                break;
            case 2:  //Case 2 is displaying the previous games.

                displayFrames(n_players);

                cout << "\nFrame scores have successfully been displayed!";
                break;
            case 3:  //Case 3 is displaying the total score for each player.

                displayTotal(n_players);

                break;
            case 4:
                MainMenu();  //Case 4 is to re-display the menu
                break;
            case 5:
                break;  //Case 5 is to exit the program
            default:
                cout << "Invalid choice. Please choose again.\n";  //Default option is that the choice is invalid.
                MainMenu();
                break;
        }
        cin >> choice;  //Grab next command
    }
    cout << "Have a great day!\n";
    cout << "Good Bye!";
}