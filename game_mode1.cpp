#include "CGame.h"
#include <iostream>
#include <thread>
#include <chrono>

void CGame::game_mode1(void)
{
      int i;
      bool player, cpu;
      player=cpu=false;
    if(!readGame())
    {
        cout << "THERE IS NOT ANY GAME CURRENTLY IN PROGRESS" << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        return;
    }

    if(started)
    {
        for(i=0;i<plays;i++)
        {
            round(weapon,gameInfo[i]);
            i++;
            if(i<plays)
                round(CPUweapon,gameInfo[i]);
        }
        this_thread::sleep_for(chrono::milliseconds(4500));
        Clear();
        printBoard();

        while(!player && !cpu && plays < 42)
        {
            if(!cpu && plays%2 == 0)
            {
                player = USERplay();
            }
            if(!player && plays%2 != 0)
                cpu = CPUplay();
            if(plays ==42)
                cout << "THIS GAME IS A DRAW" << endl;
            if(player || cpu)
                remove("GameSave.txt");
        }
    }
    if(!started)
    {
        for(i=0;i<plays;i++)
        {
            round(CPUweapon,gameInfo[i]);
            i++;
            if(i<plays)
                round(weapon,gameInfo[i]);
        }

        Clear();
        printBoard();
        while(!player && !cpu && plays < 42)
        {

            if(!player && plays%2 == 0)
            {
                cpu = CPUplay();
            }
            if(!cpu && plays%2!=0)
            {
                player = USERplay();
            }
            if(plays ==42)
                cout << "THIS GAME IS A DRAW" << endl;
            if(player || cpu)
                remove("GameSave.txt");
        }
    }

    remove("GameSave.txt");
}

