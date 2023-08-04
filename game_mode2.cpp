#include "CGame.h"

//=====================================================================================================================================
void CGame :: game_mode2()
{
    //CGame game; int time = 0;
    char spam;
    remove("GameSave.txt");
    restart();
    plays=0;
    char PlayAgain = 'Y';
    bool player, cpu;
    player = cpu = false;
    char name[3]={};
    getdifficulty();
    if(difficulty == 9)
    {
        CPUweapon = 'X';
        weapon = 'O';
    }
    else
        getweapon();

    if(difficulty != 0 && difficulty != 9)
        whoStarts();
    if(difficulty == 0)
    {
        char aux;
        aux = weapon;
        weapon = CPUweapon;
        CPUweapon = aux;
    }
    writeGame();
    Clear();
    printBoard();
    while(PlayAgain == 'Y')
    {
        if(started)
        {
            gameLine="";
            auto start = chrono::steady_clock::now();
            while(!player && !cpu && plays < 42)
            {                                                                     //player starts
                if(!cpu)
                    player = USERplay();
                if(!player)
                    cpu = CPUplay();
                if(plays ==42)
                    cout << "THIS GAME IS A DRAW" << endl;
            }
            auto end = chrono::steady_clock::now();
            time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            if(player && difficulty != 9)
            {
                cout << "YOU HAVE WON THIS GAME IN " << time/1000 << " seconds" << endl;
                ask_name(name);
                savePlayer(name);
                Clear();
                //printallBoards();
                cout<<"PRESS ANY CHARACTER TO CONTINUE";
                cin>>spam;
                Clear();
                classification_menu();
            }
            //cout << endl << time << endl;
            remove("GameSave.txt");
            if(!player)
               // printallBoards();
            cout << "DO YOU WISH TO PLAY AGAIN?" << endl
                 << "IF SO PLEASE PRESS 'Y' TO YES OR 'N' TO NO: ";
            while (!(cin >> PlayAgain) || (PlayAgain != 'n' && PlayAgain != 'N' && PlayAgain != 'y' && PlayAgain != 'Y'))
            {
                cerr << "DO YOU WANT TO RESTART OR NOT" << endl
                     << "INPUT A VALID CHARACTER: ";
                cin.clear();
                cin.ignore(100, '\n');
            }
            remove("GameSave.txt");
            PlayAgain = toupper(PlayAgain);
            plays=0;
            if(PlayAgain == 'Y')
            {
                restart();
                Clear();
                printBoard();
                started = cpu = player = false;
            }
            else if (PlayAgain =='N')
            {
                restart();
                return;
            }

        }
        else if(!started)                           //cpu starts
        {
            gameLine="";
            auto start = chrono::steady_clock::now();
            while(!player && !cpu && plays < 42)
            {

                if(!player)
                    cpu = CPUplay();
                if(!cpu)
                    player = USERplay();
                if(plays == 42)
                    cout << "THIS GAME IS A DRAW" << endl;
            }
            auto end = chrono::steady_clock::now();
            time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            if(player && difficulty != 9)
            {
                cout << "YOU HAVE WON THIS GAME IN " << time/1000 << " seconds" << endl;
                ask_name(name);
                savePlayer(name);
                Clear();
                //printallBoards();
                cout<<"PRESS ANY CHARACTER TO CONTINUE";
                cin>>spam;
                Clear();
                classification_menu();
            }
            if(!player)
               // printallBoards();
            remove("GameSave.txt");

            cout << "DO YOU WISH TO PLAY AGAIN? " << endl
                 << "IF SO PLEASE PRESS 'Y' TO YES OR 'N' TO NO ";
            while (!(cin >> PlayAgain) || (PlayAgain != 'n' && PlayAgain != 'N' && PlayAgain != 'y' && PlayAgain != 'Y'))
            {
                cerr << "DO YOU WANT TO RESTART OR NOT" << endl
                     << "INPUT A VALID CHARACTER: ";
                cin.clear();
                cin.ignore(100, '\n');
            }
            PlayAgain = toupper(PlayAgain);
            plays=0;
            if(PlayAgain == 'Y')
            {
                restart();
                Clear();
                printBoard();
                started=true;
                cpu = player = false;
            }
            else if (PlayAgain =='N')
            {
                restart();
                return;
            }
        }
    }
}
