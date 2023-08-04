#include "CGame.h"
#include "Solver.h"
using namespace GameSolver;
using namespace Connect4;
//=====================================================================================================================================
CGame::CGame()                         //DEFAULT CONSTRUCTOR TO GAME
{
    head = NULL;                                          //there
    alternativehead = NULL;
    BoardNode *newboard=new BoardNode;
    BoardNode * alternat = new BoardNode;
    BoardNode *actual, *alternativeactual;

    for (int i=0; i<6; i++)
    {
        for (int j=0; j <7; j++)
        {
            newboard->data[i][j] = ' ';                     //printing a blank table to the board we are creating
            alternat->data[i][j] = ' ';
        }
    }
    newboard->next=NULL;                                    //the newboard will point to NULL
    alternat->next = NULL;

    if(head==NULL){
        head=newboard;                                      //if there's no elements in the first is the head
    }
    else{
        actual=head;
        while(actual->next!=NULL)                           //else it goes to the end and it is placed there
            actual=actual->next;
        actual->next=newboard;
    }

    if(alternativehead==NULL)
    {
        alternativehead=alternat;                                      //if there's no elements in the first is the head
    }
    else{
        alternativeactual=alternativehead;
        while(alternativeactual->next!=NULL)                           //else it goes to the end and it is placed there
            alternativeactual=alternativeactual->next;
        alternativeactual->next=alternat;
    }

    time= 0;
    weapon = ' ';     //
    plays = 0;
    difficulty = 0;
    started=false;
}
//=====================================================================================================================================
CGame::~CGame(){                       //CLASS DESTRUCTOR
    //    BoardNode *actual, *next;

    //    actual=head;
    //    while(actual!=NULL){
    //        next=actual->next;
    //        delete actual;
    //        actual=next;
    //}

}
//=====================================================================================================================================
void CGame:: printBoard()              //PRINTS THE LAST BOARD / THE LAST NODE OF THE LIST
{
    BoardNode *actual = head;
    int i,j;

    while(actual->next != NULL){                            // it goes on the whole list until it gets to the last element

        actual=actual->next;
    }
    connect();
    cout << endl;

    cout << "                                                  ";
    for(i=0; i<7; i++)
    {                                                                      //PRINT THE NUMBERS ON TOP
        cout << '|';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),03);
        cout << ' ' << i+1 << ' ';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);

    }
    cout << "| " << endl;

    cout << "                                                 ";

    for (i = 0; i<6; i++)
    {

        for (j = 0; j<7; j++)
        {
            cout << " | ";
            if(actual->data[i][j] == 'O')
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),04);
            else if(actual->data[i][j] == 'X')
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),06);
            cout << actual->data[i][j];                                               //prints all the elements of the list
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);

        }

        cout << " | " << endl;
        cout << "                                                 ";


    }
    cout << endl;
    four();
}
//=====================================================================================================================================
void CGame:: printBoardalternative()   //PRINTS THE LAST BOARD / THE LAST NODE OF THE LIST
{
    BoardNode *actual = alternativehead;
    int i,j;
    while(actual->next != NULL){                            // it goes on the whole list until it gets to the last element

        actual=actual->next;
    }
    //    while(actual != NULL)
    //    {
    for(i=0; i<7; i++)
    {
        cout << '|' << i+1;
    }
    cout << "| " << endl;
    for (i = 0; i<6; i++)
    {
        for (j = 0; j<7; j++)
        {
            cout << "|" << actual->data[i][j];            //prints all the elements of the list
        }
        cout << '|' << endl;
    }
    //        actual=actual->next;
    //    }
}
//=====================================================================================================================================
bool CGame::checkVictory(char weapon)  //CHECKS IF ANY GIVEN WEAPON(X OR O) HAS WON THE GAME
{

    BoardNode *actual = head;
    while(actual->next!= NULL)
    {
        actual=actual->next;
    }

    for (int i = 0; i<6; i++)
    {
        for (int j = 0; j<7; j++)
        {
            if(i<3 && j<4 && actual->data[i][j]==weapon && actual->data[i+1][j+1]==weapon && actual->data[i+2][j+2]==weapon && actual->data[i+3][j+3]==weapon)
            {
                //cout << "PLAYER " << weapon << " WON DIAGONALLY WITH BOTTOM PIECE ON " << i << j << endl;
                return true;
            }
            if(i<3 && j>2 && actual->data[i][j]==weapon && actual->data[i+1][j-1]==weapon && actual->data[i+2][j-2]==weapon && actual->data[i+3][j-3]==weapon)
            {
                //cout << "PLAYER " << weapon << " WON DIAGONALLY WITH TOP PIECE ON " << i << j << endl;
                return true;
            }
            if(i<3 && actual->data[i][j]==weapon && actual->data[i+1][j]==weapon && actual->data[i+2][j]==weapon && actual->data[i+3][j]==weapon)
            {
                //cout << "PLAYER " << weapon << " WON VERTICALLY ON ROW " << j << endl;
                return true;
            }
            if(j<4 && actual->data[i][j]==weapon && actual->data[i][j+1]==weapon && actual->data[i][j+2]==weapon && actual->data[i][j+3]==weapon)
            {
                //cout << "PLAYER " << weapon << " WON HORIZONTALLY ON LINE " << i << endl;
                return true;
            }
        }
    }
    return false;
}
//=====================================================================================================================================
void CGame::printhead()                //PRINTS THE HEAD / CLEAN BOARD GAME
{
    cout << "HEAD PRINTING" << endl;
    for(int i=0; i<7; i++)
    {
        cout << '|' << i+1;
    }
    cout << "| " << endl;
    for (int i = 0; i<6; i++)
    {
        for (int j = 0; j<7; j++)
        {
            cout << "|" << head->data[i][j];
        }
        cout << '|' << endl;
    }
}
//=====================================================================================================================================
void CGame::printallBoards()           //PRINTS ALL THE BOARDS ON A HORIZONTAL DISPLAY
{
    // cout << "PRINTING ALL BOARDS" << endl;
    BoardNode *actual= alternativehead , *pointer_reminder=alternativehead, *newhead=alternativehead;

    int num = 0, pointers=0, num_list=0, num_lines, num_rest;
    while(actual->next != NULL)
    {
        actual=actual->next;                            //counts how many boards it needs to display
        num++;
    }
    actual=alternativehead;
    num_lines = (num+1) / 6;                                     //number of lines of the display with 6 columns
    num_rest = (num+1) % 6;                                      //number of columns of the last line (always less than 6)
    //cout << endl << num_lines << endl << num_rest << endl;
    cout << endl << endl;
    for(int seven = 0; seven < num_lines ; seven++)      //the numbers on top of the boards to FULL lines
    {
        {
            for (int l=0; l<6; l++){
                for(int k=0; k<7; k++)
                {
                    cout << '|' << k+1;
                }
                cout << "|   " ;
            }
            cout <<endl;

            for(int i=0; i<6; i++)              //number of lines of the display
            {           //line under this goes through 6 elements of the list
                for(BoardNode *teste= newhead;  teste != newhead->next->next->next->next->next->next; teste=teste->next)
                {
                    for(int j=0;j<7;j++)        //goes through all the columns of all elements of all lines as said before
                    {

                        cout << '|' << actual->data[i][j];

                        if(j==6)            //if the columns is over
                        {
                            actual=actual->next;     num_list++;
                            cout << "|   ";
                            if(teste->next == newhead->next->next->next->next->next->next)  // if last board of the display line it will
                            {                                                               // go back to the first to print other lines
                                cout << endl;
                                actual=newhead;
                            }
                        }
                        if(i==5 && j==6)
                        {
                            pointer_reminder=pointer_reminder->next; pointers++;    //keeps track of how many semi boards are being printed
                        }
                    }
                }
            }
            cout << endl ;
            newhead=pointer_reminder; //when on the second line of the display, the first element of the list of that line will function
        }                             // almost as a new "head"
    }
    //last guys
    for (int l=0; l<num_rest; l++){       // this part of the code is exactly the same but to the last line of the display,
        for(int k=0; k<7; k++)            // where there are not 6 columns of matrixes
        {
            cout << '|' << k+1;
        }
        cout << "|   " ;
    }
    cout <<endl;
    for(int i=0; i<6; i++)
    {
        for(BoardNode *teste= newhead;  teste != NULL; teste=teste->next)
        {
            for(int j=0;j<7;j++)
            {
                cout << '|' << actual->data[i][j];
                if(j==6)
                {
                    actual=actual->next;     num_list++;
                    cout << "|   ";
                    if(teste->next == NULL)
                    {
                        cout << endl ;actual=newhead;
                    }
                }
                if(i==5 && j==6)
                {
                    pointer_reminder=pointer_reminder->next; pointers++;
                }
            }
        }
    }
}
//=====================================================================================================================================
int CGame::round(char weapon, int col) //THIS METHOD PLAYS A ROUND
{
    if(col==-1 || col==8)
    {
        return 0;
    }
    int i;
    BoardNode *actual = head;
    BoardNode *nextnode = new BoardNode;

    while(actual->next != NULL)
    {
        actual=actual->next;                                       //goes to the last board
    }
    for (int i = 0; i<6; i++)
    {
        for (int j = 0; j<7; j++)
        {
            nextnode->data[i][j] = actual->data[i][j];              //copies the information
        }
    }
    for(i=5; i>=0; i--)
    {
        if(nextnode->data[i][col] == ' ')                           //checks whats the lowest free line to where the "chip" will "fall"
        {
            nextnode->data[i][col] = weapon;
            actual->next = nextnode;
            nextnode->next =NULL;
            ClearAlt();
            plays++;
            return 1;
        }
    }
    if(i==-1){
        actual=nextnode;                                            //if the column is full it will erase the last node
        delete(nextnode);
        actual->next=NULL;
        return 0;
    }

    else return 2;

}
//=====================================================================================================================================
void CGame::getweapon()                //ASKS THE PLAYER WHAT PIECE HE WANTS TO PLAY WITH
{
    if(difficulty == 0)
        cout << "PLAYER 1 ";
    else
        cout << "NOW ";
    cout << "CHOOSE YOUR WEAPON. ARE YOU AN 'X' OR AN 'O'?";

    while (!(cin >> weapon) || (weapon != 'O' && weapon != 'X' && weapon != 'x' && weapon != 'o'))
    {
        cerr << "SIR, IM AFRAID YOU CANNOT PLAY WITH THAT WEAPON" << endl << "PLEASE PLAY PICK AN 'O' OR AN 'X'"<< endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
    weapon = toupper(weapon);
    if(weapon == 'X') CPUweapon = 'O';
    else CPUweapon = 'X';

    cout << "PLAYER CHOOSEN: " << this->weapon << endl << endl;
}
//=====================================================================================================================================
void CGame:: getdifficulty()           //ASKS THE PLAYER WHAT DIFFICULT LEVEL HE WANTS TO PLAY
{
    Clear();
    cout << "VERY WISE CHOICE SIR"<< endl;
    cout << "HOW TOUGH ARE YOU?" << endl
         << "LEVEL 1 FOR SKINNY PETE DIFFICULTY" << endl
         << "LEVEL 2 FOR GUSTAVO FRING DIFFICULTY" << endl
         << "LEVEL 3 FOR JESSE PINKMAN DIFFICULTY" << endl
         << "LEVEL 4 FOR HEISENBERG DIFFICULTY" << endl
         << "PRESS 0 TO PLAY MULTYPLAYER MODE" << endl
         << "PRESS 9 TO WATCH THE COMPUTER COMPETE AGAINST HIMSELF" << endl;
    cout << setw(5) << setfill(' ') << "CHOOSE YOUR OPONENT: ";
    while (!(cin >> difficulty) || ((difficulty < 0 || difficulty > 4) && difficulty != 9))
    {
        cerr << "SIR, THAT IS NOT A VALID DIFFICULTY LEVEL" << endl << "PLEASE PICK A NUMBER BETWEEN 0 AND 3 FOR DIFFICULTY"<< endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
    cout << endl;
    if(difficulty == 0) cout << "MULTIPLAYER MODE" << endl;
    if(difficulty == 1) cout << "THIS LEVEL IS CHLID'S PLAY" << endl;
    if(difficulty == 2) cout << "YOU CHOSE 'COMMON MORTAL' DIFFICULTY" << endl;
    if(difficulty == 3) cout << "YOU CHOSE ULTIMATE DIFFICULTY. PREPARE TO BE SMASHED" << endl;
    if(difficulty == 9) cout << "COMPUTER PLAYING WITH HIMSELF" << endl;
}
//=====================================================================================================================================
void CGame:: whoStarts(void)           //ASKS THE PLAYER IF HE WANTS TO BE FIRST OR PLAY AFTER CPU
{
    char start;
    cout << "DO YOU WISH TO START OR SHALL I BEGIN?" << endl
         << "PLEASE PRESS 'M'(ME) TO START OR 'Y (YOU) FOR ME TO START: ";
    while (!(cin >> start) || (start != 'y' && start != 'Y' && start != 'm' && start != 'M'))
    {
        cerr << "SIR THIS GAME IS ONLY MEANT FOR TWO PLAYERS" << endl << "THAT IS NOT ME OR YOU"<< endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
    start = toupper(start);
    if(start == 'Y') started = false;
    if(start == 'M') started = true;        //true for player start and false for cpu to start
}
//=====================================================================================================================================
bool CGame:: CPUplay()                 // MOVES FROM CPU
{
    int column, full_column=0;
//    char spam;
    while(full_column == 0)
    {
        if(difficulty == 0)             //multiplayer mode
        {
            do{
                column = getcolumn(plays)-1;     //gets the columns

                if(column == -1)  // when player wants to bo back on moves
                {
                    GoBack();
                    Clear();
                    printBoard();
                    plays --;
                    plays --;
                    cout << plays;
                }
                full_column = round(CPUweapon, column);        //checks if column is full

                if(full_column == 0 && column != -1)
                {
                    cout << "THIS COLUMN IS FULL. PLEASE INSERT ANOTHER " << full_column << endl;
                }
            }while(full_column == 0);
            gameInfo[plays]=column;
            // plays++;
            Clear();
            printBoard();
            cout << "MOVES:" << plays;
            if(checkVictory(CPUweapon)) return true; //checks if won
            return false;
        }
        if(difficulty == 1)             //level one difficult plays completely random
        {
            column= rand()%7+1;
            full_column = round(CPUweapon, column);
        }
        if(difficulty==2)               //level two difficult plays random except of when it is in position of winning in that round
        {
            bool win;
            win = CPUBlock(CPUweapon);
            if(!win)
            {
                column= rand()%7+1;
                //cin >> column;column-=1;
                full_column = round(CPUweapon, column);
            }
            else if(win)
                return true;
        }
        if(difficulty==3)       //level 3 checks if it can win, if not checks if the player can win next and blocks if possible.
        {                       //then if not possible any of these moves it plays random
            bool win, block;
            win = CPUBlock(CPUweapon);
            full_column = 1;
            if(!win)
            {
                block = CPUBlock(weapon);
                if(!block)
                {
                    column= rand()%7+1;
                    //cin >> column;column-=1;
                    //                    cout << "column";
                    full_column = round(CPUweapon, column);
                }
            }
            else if(win)
                return true;
        }
        if(difficulty==4||difficulty==9)
        {
            BoardNode *actual = head;
            while(actual->next != NULL)
                actual= actual->next;

            if (plays < 4)
            {
                //Verifica para o caso do utilizador criar 3 em linha
                if(actual->data[5][3] == weapon && actual->data[5][2] == weapon)
                {
                    round(CPUweapon,1);
                    gameLine+=(char)(1+'1');
                    gameInfo[plays]=1;
                }
                else if(actual->data[5][3] == weapon && actual->data[5][4] == weapon)
                {
                    round(CPUweapon,5);
                    gameLine+=(char)(5+'1');
                    gameInfo[plays]=5;
                }
                else if(actual->data[5][3] == weapon && actual->data[5][1] == weapon)
                {
                    round(CPUweapon,2);
                    gameLine+=(char)(2+'1');
                    gameInfo[plays]=2;
                }
                else if(actual->data[5][3] == weapon && actual->data[5][5] == weapon)
                {
                    round(CPUweapon,4);
                    gameLine+=(char)(4+'1');
                    gameInfo[plays]=4;
                }
                else
                {
                    column=3;
                    round(CPUweapon,column);
                    gameLine+=(char)(column+'1');
                    gameInfo[plays]=column;
                }
            }
            else
                advancedModeCPU();
            Clear();
            printBoard();
            cout << "MOVES:" << plays;
            if(checkVictory(CPUweapon))
            {
                return true;
                win=false;
            }
            return false;
        }
//        if(difficulty == 9)             //auto mode
//        {
//            while (!(cin >> spam))
//            {
//                cin.clear();
//                cin.ignore(100, '\n');
//            }
//            column= rand()%7+1;
//            if(plays % 2 == 0)
//                full_column = round(CPUweapon, column);
//            else
//            {
//                full_column = round(weapon, column);
//                if(checkVictory(weapon))
//                {
//                    Clear();
//                    printBoard();
//                    return true;
//                }
//            }
//        }
        cout << "COMPUTER THINKING..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        Clear();
        printBoard();
        gameInfo[plays]=column;                                                                                                                 //
        //plays++;
        writeGame();
        cout << "MOVES:" << plays << endl;
    }
    if(checkVictory(CPUweapon)) return true;
    return false;

}
//=====================================================================================================================================
bool CGame:: USERplay()                //MOVES FROM THE PLAYER
{
    int column, full_column;
    if (difficulty == 9)
    {
        BoardNode *actual = head;
        while(actual->next != NULL)
            actual= actual->next;

        if (plays < 4)
        {
            //Verifica para o caso do utilizador criar 3 em linha
            if(actual->data[5][3] == CPUweapon && actual->data[5][2] == CPUweapon)
            {
                round(weapon,1);
                gameLine+=(char)(1+'1');
                gameInfo[plays]=1;
            }
            else if(actual->data[5][3] == CPUweapon && actual->data[5][4] == CPUweapon)
            {
                round(weapon,5);
                gameLine+=(char)(5+'1');
                gameInfo[plays]=5;
            }
            else if(actual->data[5][3] == CPUweapon && actual->data[5][1] == CPUweapon)
            {
                round(weapon,2);
                gameLine+=(char)(2+'1');
                gameInfo[plays]=2;
            }
            else if(actual->data[5][3] == CPUweapon && actual->data[5][5] == CPUweapon)
            {
                round(weapon,4);
                gameLine+=(char)(4+'1');
                gameInfo[plays]=4;
            }
            else
            {
                column=3;
                round(weapon,column);
                gameLine+=(char)(column+'1');
                gameInfo[plays]=column;
            }
        }
        else
            advancedModePlayer();
        Clear();
        printBoard();
        cout << "MOVES:" << plays;
        if(checkVictory(weapon))
        {
            return true;
            win=false;
        }
        return false;
    }
    else
    {
        do{
            column = getcolumn(plays)-1;     //gets the columns
            if(column == -1)  // when player wants to bo back on moves
            {
                while(column == -1)
                {
                    KeepNodes();
                    KeepNodes();
                    TimesBack ++;
                    GoBack();
                    //printallBoards();
                    //Clear();
                    //printBoardalternative();
                    printBoard();
                    plays --;
                    plays --;
                    cout <<"MOVES:" << plays;
                    column = getcolumn(plays)-1;
                }
            }
            if(column == 8)
            {
                if(alternativehead->next ==NULL)
                {
                    cout << "THERE ARE NO PREVIOUS 'NEXT MOVES'" << endl;
                }
                else
                {
                    Clear();
                    GoFoward();
                    printBoard();
                    cout << "MOVES:" << plays << endl;
                }

            }
            full_column = round(weapon, column);                                           //checks if column is full

            if(full_column == 0 && column != -1 && column !=8)
            {
                cout << "THIS COLUMN IS FULL. PLEASE INSERT ANOTHER " << full_column << endl;
            }
        }while(full_column == 0);
        gameInfo[plays]=column;
        gameLine+=(char)(column+'1');
        //plays++;
        writeGame();
        Clear();
        printBoard();
        cout << "MOVES:" << plays << endl;
    }
    if(checkVictory(weapon))
        return true; //checks if won
    else
        return false;
}
//=====================================================================================================================================
void CGame:: restart()                 //WHEN THE GAME ENDS IT ERASES THE BOARD TO PREPARE A NEW GAME
{
    BoardNode *actual= head->next, *next;
    while(actual != NULL)
    {
        next=actual->next;
        actual->next=NULL;
        delete(actual);
        actual=next;
    }
    for (int i=0; i<6; i++)
    {
        for (int j=0; j <7; j++)
        {
            head->data[i][j] = ' ';
        }
    }
    head->next=NULL;

}
//=====================================================================================================================================
void CGame:: KeepNodes(void)           //KEEPS THE NODES FROM WHERE IT NEEDS TO RETROCEED THE PLAYS
{
    BoardNode *temp, *actual;     //last refers to the last piece we want to keep
    BoardNode *nextnode = new BoardNode;
    temp = head;

    while(temp != NULL)
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j <7; j++)
            {
                nextnode->data[i][j] = temp->data[i][j];
            }
        }
        temp = temp->next;
    }
    nextnode->next = NULL;
    actual = alternativehead;
    while(actual->next != NULL)
        actual = actual->next;
    actual->next = nextnode;
}
//====================n=================================================================================================================
void CGame:: GoBack()                  //GOES BACK ONE MOVE
{
    BoardNode *temp, *last;     //last refers to the last piece we want to keep

    last = temp = head;
    while (temp && temp->next != NULL && temp->next->next != NULL) {
        last = temp;
        temp = temp->next;
    }
    if (last == head) {
        if (head) {
            delete(head->next);
        }
        delete(head);
        head = NULL;
    } else {                                //deletes the last two nodes
        delete(last->next->next);
        delete(last->next);
        last->next = NULL;
    }
    //printallBoards();
    Clear();
}
//=====================================================================================================================================
void CGame:: GoFoward()                //GOES TO MOVES FOWARD
{
    BoardNode *actualalt = alternativehead, *actual = head, *last;
    BoardNode *newboard = new BoardNode;
    BoardNode *newboard2 = new BoardNode;
    plays++;
    plays++;


    while(actualalt && actualalt->next != NULL && actualalt->next->next != NULL )
        actualalt = actualalt->next;
    while(actual->next != NULL)
        actual = actual->next;

    for (int i=0; i<6; i++)
    {
        for (int j=0; j <7; j++)
        {
            newboard->data[i][j] = actualalt->next->data[i][j];
            newboard2->data[i][j] = actualalt->next->data[i][j];
        }
    }
    newboard->next = NULL;
    newboard2->next = NULL;
    actual->next = newboard;
    newboard->next = newboard2;
    actualalt = alternativehead;

    while (actualalt && actualalt->next != NULL && actualalt->next->next != NULL)
    {
        last = actualalt;
        actualalt = actualalt->next;
    }
    delete(last->next->next);
    delete(last->next);
    last->next = NULL;
}
//=====================================================================================================================================
void CGame:: ClearAlt()                //CLEARS ALL THE STORED PREVIOUS MOVES
{
    BoardNode *actualalt = alternativehead->next, *next;


    while (actualalt != NULL)
    {
        next = actualalt->next;
        delete(actualalt);
        actualalt = next;
    }

    alternativehead->next = NULL;
    //printallBoards();

}
//=====================================================================================================================================
bool CGame::CPUBlock(char weapon)      //CHECKS ALL THE POSSIBLE "PRE" WON GAMES. WORKS BOTH TO LEVEL 2 AND 3. CHECKS POSITIONS SUCH AS
{                                       // "XXX ", "XX X", "X XX" OR " XXX" in all directions in both 'X' and 'O'
    BoardNode *actual = head;
    while(actual->next!= NULL)
    {
        actual=actual->next;
    }
    for (int i = 0; i<6; i++)
    {
        for (int j = 0; j<7; j++)
        {
            if(i<4 && j<5 && actual->data[i][j]==weapon && actual->data[i+1][j+1]==weapon && actual->data[i+2][j+2]==weapon)
            {
                //cout << "PLAYER " << CPUweapon << " BLOCK DIAGONALLY WITH BOTTOM PIECE ON " << i << j << endl;
                if(j<4 && i<3 && actual->data[i+3][j+3] == ' ' && actual->data[i+4][j+3] != ' ')
                {
                    actual->data[i+3][j+3] = CPUweapon;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // diagonally missing bottom spot right
                }
                else if(i>0 && actual->data[i-1][j-1] == ' ' && actual->data[i][j-1] != ' ')
                {
                    actual->data[i-1][j-1] = CPUweapon;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // diagonally missing top spot left
                }

            }
            if(i<4 && j>1 && actual->data[i][j]==weapon && actual->data[i+1][j-1]==weapon && actual->data[i+2][j-2]==weapon)
            {
                // cout << "PLAYER " << CPUweapon << " BLOCK DIAGONALLY WITH TOP PIECE ON este " << i << j << endl;
                if(j>2 && i<2 && actual->data[i+3][j-3] == ' ' && actual->data[i+4][j-3] != ' ')
                {
                    actual->data[i+3][j-3] = CPUweapon;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // diagonally bottom spot left
                }
                else if(j<6 && i>0 && actual->data[i-1][j+1] == ' ' && actual->data[i][j+1] != ' ')
                {
                    actual->data[i-1][j+1] = CPUweapon;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // diagonally missing top spot right
                }
            }
            if(i<4 && actual->data[i][j]==weapon && actual->data[i+1][j]==weapon && actual->data[i+2][j]==weapon)
            {
                if(i>0 && actual->data[i-1][j] == ' ' )
                {
                    //cout << "PLAYER " << CPUweapon << " BLOCK VERTICALLY ON ROW " << j << endl;
                    actual->data[i-1][j] = CPUweapon;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // vertically missing top spot
                }
            }
            if(j<5 && actual->data[i][j]==weapon && actual->data[i][j+1]==weapon && actual->data[i][j+2]==weapon)
            {
                if(j>0 && actual->data[i][j-1] == ' ' && actual->data[i+1][j-1] != ' ')
                {
                    actual->data[i][j-1] = CPUweapon;
                    //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // horizontally missing first spot
                }
                else if(j<4 && actual->data[i][j+3] == ' ' && actual->data[i+1][j+3] != ' ')
                {
                    actual->data[i][j+3] = CPUweapon;
                    //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                    cout << "COMPUTER THINKING..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    Clear();
                    printBoard();
                    return true;                    // horizontally missing last spot
                }
            }
            if(j<4 && actual->data[i][j] ==weapon && actual->data[i][j+1] == ' ' && actual->data[i+1][j+1] !=' ' && actual->data[i][j+2] == weapon && actual->data[i][j+3] == weapon)
            {
                actual->data[i][j+1] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                    // horizontally missing third spot
            }
            if(j<4 && actual->data[i][j] ==weapon && actual->data[i][j+2] == ' ' && actual->data[i+1][j+2] !=' ' && actual->data[i][j+1] == weapon && actual->data[i][j+3] == weapon)
            {
                actual->data[i][j+2] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                     // horizontally missing second spot
            }
            if(i>3 && j<6 && actual->data[i][j] ==weapon && actual->data[i-1][j+1] == ' ' && actual->data[i][j+1] != ' ' && actual->data[i-2][j+2] ==weapon && actual->data[i-3][j+3] == weapon)
            {
                actual->data[i-1][j+1] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                     // ascending diagonal missing second spot
            }
            if(i>2 && j<4 && actual->data[i][j] ==weapon && actual->data[i-2][j+2] == ' ' && actual->data[i-1][j+2] != ' ' && actual->data[i-1][j+1] ==weapon && actual->data[i-3][j+3] == weapon)
            {
                actual->data[i-2][j+2] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                     // ascending diagonal missing third spot
            }
            if(i<3 && j<4 && actual->data[i][j]==weapon && actual->data[i+1][j+1]==' ' && actual->data[i+2][j+1]!=' ' && actual->data[i+2][j+2]==weapon && actual->data[i+3][j+3]==weapon)
            {
                actual->data[i+1][j+1] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                     // descending diagonal missing second spot
            }
            if(i<3 && j<4 && actual->data[i][j]==weapon && actual->data[i+1][j+1]==weapon && actual->data[i+3][j+2]!=' ' && actual->data[i+2][j+2]==' ' && actual->data[i+3][j+3]==weapon)
            {
                actual->data[i+2][j+2] = CPUweapon;
                //cout << "PLAYER " << CPUweapon << " BLOCK HORIZONTALLY ON LINE " << i << endl;
                cout << "COMPUTER THINKING..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                Clear();
                printBoard();
                return true;                     // descending diagonal missing third spot
            }
        }
    }
    return false;
}
//=====================================================================================================================================
void rr()                              //SECRET MODE
{
    cout << "YOU JUST GOT RICKROLLED :)" << endl;
    return;
}
//=====================================================================================================================================
void CGame::writeGame()                //SAVE GAME INFOS
{
    int startedFile, weaponFile,i;
    ofstream outputFile("GameSave.txt");
    if (!outputFile.is_open())
    {
        cout << "COULD NOT OPEN FILE" << endl;
        return;
    }
    if(weapon=='X')
        weaponFile=0;
    else
        weaponFile=1;
    if(!started)
        startedFile=0;
    else
        startedFile=1;
    outputFile << difficulty << endl << weaponFile << endl << startedFile << endl;
    for(i=0; i<plays;i++)
        outputFile<<gameInfo[i]<<endl;
    outputFile.close();
}
//=====================================================================================================================================
bool CGame::readGame()                 //STORES THE GAME INTO A FILE
{
    CGame game;
    int i,j;
    i=0;
    int gameInfoFile[45]={};
    ifstream inputFile("GameSave.txt", ios::in);
    if (!inputFile.is_open())
    {
        return false;
    }
    while(!inputFile.eof())
    {
        inputFile>>gameInfoFile[i];
        i++;
    }
    i--;
    inputFile.close();
    plays=i-3;
    difficulty=gameInfoFile[0];
    if(gameInfoFile[1]==0)
    {
        weapon = 'X';
        CPUweapon = 'O';
    }
    else if(gameInfoFile[1]==1)
    {
        weapon = 'O';
        CPUweapon = 'X';
    }
    if(gameInfoFile[2]==0)
        started=false;
    else if(gameInfoFile[2]==1)
        started=true;
    for(j=3;j<i;j++)
        gameInfo[j-3]=gameInfoFile[j];
    return true;
}
//=====================================================================================================================================
void CGame:: connect(){                //LAYOUT
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),04);
    cout << "       44444      444444      444     44  444     44  44444444     44444  44444444444   " << endl;
    cout << "      44        444    444    4444    44  4444    44  44444444    44      44444444444   " << endl;
    cout << "     44        444      444   44 44   44  44 44   44  44         44           444       " << endl;
    cout << "    44        444        444  44  44  44  44  44  44  4444      44            444       " << endl;
    cout << "     44        444      444   44   44 44  44   44 44  44         44           444       " << endl;
    cout << "      44        444    444    44    4444  44    4444  44444444    44          444       " << endl;
    cout << "       44444      444444      44     444  44     444  44444444     44444      444       " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);

}
//=====================================================================================================================================
void CGame:: four(){                    //LAYOUT
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),04);

    cout  << "                                                            44444444     444444      444    444    4444444444          " << endl
          << "                                                            44444444   444    444    444    444    444    444          " << endl
          << "                                                            44        444      444   444    444    444   444           " << endl
          << "                                                            4444     444        444  444    444    444444              " << endl
          << "                                                            4444      444      444   444    444    44  444             " << endl
          << "                                                            44         444    444     444  444     44   444            " << endl
          << "                                                            44           444444        444444      44     444          " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);

}
bool CGame::avaliblePlay(int col)      //THIS METHOD PLAYS A ROUND
{
    int i;
    BoardNode *actual = head;
    BoardNode *nextnode = new BoardNode;

    while(actual->next != NULL)
    {
        actual=actual->next;                                       //goes to the last board
    }
    for (int i = 0; i<6; i++)
    {
        for (int j = 0; j<7; j++)
        {
            nextnode->data[i][j] = actual->data[i][j];              //copies the information
        }
    }
    for(i=5; i>=0; i--)
    {
        if(nextnode->data[i][col] == ' ')                           //checks whats the lowest free line to where the "chip" will "fall"
        {
            actual->next = nextnode;
            nextnode->next =NULL;
            return true;
        }
    }
    if(i==-1){
        actual=nextnode;                                            //if the column is full it will erase the last node
        delete(nextnode);
        actual->next=NULL;
        return false;
    }
    else return false;

}
void CGame::advancedModeCPU(void)
{
    Position P;
    int scores[7], bestMove;
    Solver solver;
    bestMove = 0;
    win = CPUBlock(CPUweapon);
    if(!win)
    {
        for(int i = 0; i < 7; i++)
        {
            P.reset();
            gameLineAux = gameLine;
            if(!avaliblePlay(i)) continue;
            gameLineAux=gameLineAux+(char)(i+'1');
            cout<<gameLineAux<<endl;
            P.play(gameLineAux);
            scores[i] = solver.solve(P);
            if(scores[i] < scores[bestMove]) bestMove = i;

        }
//        for(int i = 0; i < 7; i++) {
//            cout << "scores[" << i << "] = " << scores[i] << endl;
//            this_thread::sleep_for(chrono::milliseconds(1500));
//        }
        round(CPUweapon, bestMove);
    }
    gameLine=gameLine+(char)(bestMove+'1');
    gameInfo[plays]=bestMove;
}

void CGame::advancedModePlayer(void)
{
    Position P;
    int scores[7], bestMove;
    Solver solver;
    bestMove = 0;
    win = CPUBlock(weapon);
    if(!win)
    {
        for(int i = 0; i < 7; i++)
        {
            P.reset();
            gameLineAux = gameLine;
            if(!avaliblePlay(i)) continue;
            gameLineAux=gameLineAux+(char)(i+'1');
            cout<<gameLineAux<<endl;
            P.play(gameLineAux);
            scores[i] = solver.solve(P);
            if(scores[i] < scores[bestMove]) bestMove = i;

        }
//        for(int i = 0; i < 7; i++) {
//            cout << "scores[" << i << "] = " << scores[i] << endl;
//            this_thread::sleep_for(chrono::milliseconds(1500));
//        }
        round(weapon, bestMove);
    }
    gameLine=gameLine+(char)(bestMove+'1');
    gameInfo[plays]=bestMove;
}
