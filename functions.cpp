#include "CGame.h"
//=====================================================================================================================================
int getcolumn(int plays)
{
    int column;
    do{
    cout << endl << endl << "WHICH COLUMN WOULD YOU WISH TO PLAY? ";

    while (!(cin >> column) || ((column > 7 || column < 0) && column != 9))
    {
        cerr << "ERROR INPUT A VALID GAME COLUMN" << endl;
        cin.clear();
        cin.ignore(100, '\n');

    }
    if(column == 0 && plays <= 2)
        cout << "YOU MUST NOT RETROCEED YOUR FIRST MOVE" << endl;
    }while((column == 0 && plays <= 2) /*|| (column == 8 &&  )*/);
    return column;
}
//=====================================================================================================================================
void ask_name(char*name)
{
    cout << "WHAT'S YOUR NAME?"
         << "INSERT 3 CHARACTERS: ";
    while (!(cin >> name) && strlen(name) != 3)
    {
        cerr << "ONLY 3 CHARACTERS ARE ALLOWED: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    for(int i=0;i<(int)strlen(name);i++){
            name[i] = toupper(name[i]);
        }
}
