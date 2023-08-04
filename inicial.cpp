#include "CGame.h"
//=====================================================================================================================================
int inicial()
{
    int game_mode;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),03);
    cout << setw(102) << "##########################################################################" << endl
         << setw(29) << '#' << setw(46) << right << "WELCOME TO CONNECT 4" << setw(27) << right << '#' << endl
         << setw(29) << '#' << setw(65) << right << "THIS MARVELLOUS GAME IS BROUGHT TO YOU BY RAFAEL LUIS" << setw(8) << right << "#" << endl
         << setw(29) << '#' << setw(57) << right  << "DATA STRUCTURES AND ALGORITHMS 2020/2021" << setw(16) << '#' << endl
         << setw(102) << "##########################################################################" << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),04);
    cout << setw(70) << "GAME MENU" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);
    cout << "PRESS 1 TO CONTINUE YOUR LAST GAME" << endl
         << "PRESS 2 TO START A NEW GAME" << endl
         << "PRESS 3 TO SEE ALL TIME TOP SCORERS" << endl
         << "PRESS 4 TO LEAVE THE GAME" << endl
         << "WHAT MODE WOULD YOU WISH TO START? ";

    do
    {

        while (!(cin >> game_mode) || (game_mode < 0 || game_mode > 4))
        {
            cerr << "INPUT A VALID NUMBER: ";
            cin.clear();
            cin.ignore(100, '\n');
        }
    }while(game_mode != 0 && game_mode != 1 && game_mode != 2 && game_mode != 3 && game_mode != 4);
    return game_mode;

}
