#include "CGame.h"

//=====================================================================================================================================
int allPlayers(void)
{
    int numPlayers=0;
    string line;
    ifstream inputFile("LeaderBoard.txt", ios::in);
    if(!inputFile.is_open())
        return 0;                            //se o ficheiro não existir retorna 0 para permitir a criação de um novo
    while(!inputFile.eof())
    {
        getline(inputFile, line);
        numPlayers++;
        if(line.empty())
            numPlayers--;
    }
    inputFile.close();
    return numPlayers;
}
//=====================================================================================================================================
int trocaqs (const void *player1, const void *player2)
{
    int k=0;
    if(((struct SPlayer *) player1) -> numvictories < ((struct SPlayer *) player2) -> numvictories)
        k = 1;
    else if (((struct SPlayer *) player1) -> numvictories > ((struct SPlayer *) player2) -> numvictories)
        k = -1;
    else
        k = 0;
    return k;
}
//=====================================================================================================================================
int checkExistName(struct SPlayer *player, string name, int numPlayers)
{
    int index;
    for(index=0; index<numPlayers; index++)
    {
        if(name==player[index].name)
        {
            return index;
        }
    }
    return -1;
}
//=====================================================================================================================================
void savePlayer (char* name)
{
    int numPlayers;
    int i;
    bool nameExist=false;
    char confirm;
    int verify=0;
    numPlayers=allPlayers();
    i=0;
    struct SPlayer player[numPlayers];                                                                                                              //

    ifstream inputFile("LeaderBoard.txt", ios::in);

    while(!inputFile.eof() && i<numPlayers) //Armazena todos os dados do ficheiro numa struct
    {
        inputFile >> player[i].name >> player[i].numvictories;
        i++;
    }
    inputFile.close();

    ofstream outputFile("LeaderBoard.txt"); //Verifica se o ficheiro abriu
    if (!outputFile.is_open())
    {
        cout << "COULD NOT OPEN FILE" << endl;
        return;
    }

    for(i=0; i<numPlayers; i++)
    {
        if(strstr(player[i].name,name))    //compara os nomes do ficheiro com o nome dado e, se for igual, coloca um novo
        {
            while(verify!=-1)
            {
                cout << "THIS NAME ALREADY EXIST. DO YOU WANT A DIFFERENT NAME? ";
                cin >> confirm;
                if(toupper(confirm)=='N')
                {
                    verify=checkExistName(player, name, numPlayers);
                    nameExist = true;
                    player[verify].numvictories += 1;
                    verify=-1;
                }
                else if(toupper(confirm)=='Y')
                {
                    i=0;
                    name[3]={};
                    cout << "INSERT A NEW NAME: ";
                    ask_name(name);
                    verify=checkExistName(player, name, numPlayers);
                }
             }
        }
    }
    qsort((void *) player, numPlayers, sizeof(SPlayer), trocaqs);
    for(i=0; i<numPlayers; i++)
        outputFile << left << setw(7) << player[i].name << right << setw(5) << player[i].numvictories << endl;
    if(!nameExist)
        outputFile << left << setw(7) << name << right << setw(5) << 1 << endl;
    outputFile.close();
    //ABC        9
    //BCD        1
    //CDE        7
    //DEF        6
    //POL        6
    //FGH        2
}
