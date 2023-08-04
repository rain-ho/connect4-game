#ifndef CGAME_H
#define CGAME_H
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <thread>
#include <windows.h>

using namespace std;
//=====================================================================================================================================
class BoardNode{
public:
    char data[6][7];
    BoardNode *next;
};
//=====================================================================================================================================
class CGame
{
private:

    double time;
    int plays;
    int difficulty;
    char weapon;
    char CPUweapon;
    bool started;
    int TimesBack;
    int gameInfo[42];
    //novo
    string gameLine;
    string gameLineAux;
    BoardNode *head, *alternativehead;                         //lista ligada tabuleiros;
    bool win;
//    BoardNode *alternative;
public:
    CGame();
    ~CGame();
    void game_mode1(void);
    void game_mode2(void);
    void printBoard(void);
    void printBoardalternative(void);
    bool checkVictory(char);
    int round(char, int);
    void printallBoards(void);
    void printhead(void);
    void getweapon(void);
    void getdifficulty(void);
    void whoStarts(void);
    bool CPUplay(void);
    bool USERplay(void);
    void restart(void);
    void GoBack(void);
    bool CPUBlock(char);
    void end_time(void);
    bool readGame(void);
    void writeGame(void);

    //novo
    void advancedModeCPU(void);
    void advancedModePlayer(void);
    bool avaliblePlay(int);
    void retroceed(int);
    void GoFoward(void);
    void ClearAlt();
    void connect();
    void four();
    void KeepNodes(void);

};
//=====================================================================================================================================
struct SPlayer
{
    char name[3];
    int numvictories;
};
//=====================================================================================================================================
void printchar(char);
int inicial(void);
void Clear(void);
char getweapon(void);
int getcolumn(int);
void classification_menu(void);
void savePlayer (char*);
void game_mode0(void);
void game_mode1(void);
void game_mode3(void);
void ask_name(char*);
void rr(void);
#endif // CGAME_H
