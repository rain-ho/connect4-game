#include "CGame.h"

using namespace std;
//=====================================================================================================================================
void game_mode3()
{
    classification_menu();
    char key;
    cout << "PRESS ANY KEY TO EXIT";
    cin >> key;
}

void classification_menu()
{
    string line, input;
    int num_lines;
    int classification =1;
    Clear();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),03);
    cout << endl
         << setw(69) << "PRESENTING THE TOP10" << endl
         << setw(64) << "LEADERBOARD" << endl
         << setw(78) << "ONLY THE COOL KIDS CAN SIT AT THIS TABLE"
         << endl << endl <<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);
    ifstream inputFile("LeaderBoard.txt", ios::in);
    if(!inputFile.is_open())
    {
        cout << "NO ONE HAS EVER WON THIS GAME" << endl;
        return;
    }
    cout << setw(68) << "POSITION  TIMES WON" << endl;
    for (num_lines = 0; num_lines < 10 && getline(inputFile, line); ++num_lines)
    {
        cout << right << setw(52) << classification << " ";
        cout << line << endl;
        classification++;
    }
    inputFile.close();
}
