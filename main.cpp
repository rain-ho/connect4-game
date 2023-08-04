/*
 * UNIVERSIDADE DE COIMBRA 2021
 * MESTRADO INTEGRADO EM ENGENHARIA ELETROTECNICA E DE COMPUTADORES
 * ESTRUTURAS DE DADOS E ALGORITMOS
 * ESTE JOGO FOI PRODUZIDO POR RAFAEL RAINHO LUÍS, 2018289409 E JOSÉ _______ CASCA, ________________
 *
 * ESTE JOGO ENGLOBA 3 NIVEIS DE DIFICULDADE E DA-NOS A OPORTUNIDADE DE ESCOLHER SE QUEREMOS OU NÃO COMEÇAR A JOGAR E QUAL O CARACTER,
 * ENTRE 'X' E 'O' COM QUE QUEREMOS JOGAR.
 * CADA TABULEIRO É UMA MATRIZ[i][j] INSERIDO NUM NO DE UMA LISTA LIGADA.
 * PODEMOS RETROCEDER AS JOGADAS QUE QUISERMOS EXCLUIDO A PRIMEIRA PRESSIONANDO A TECLA '0'
 * O JOGO GUARDA EM FICHEIRO TODOS OS JOGADORES QUE ALGUMA VEZ GANHARAM ESTE JOGO E TEM A FUNCIONALIDADE DE NOS MOSTRAR ESTE TOP-10
 * EXISTE UM METODO DA CLASSE QUE DISPOE LADO A LADO OS TABULEIROS MAS TEM UM PEQUENO BUG EM QUE NA LINHA DE CIMA GUARDA A COLUNA JOGADA MAS
 * APENAS A MOSTRA PASSADAS 6 JOGADAS.
*/
//=====================================================================================================================================
#include "CGame.h"
//=====================================================================================================================================
int main()
{
    srand (time(NULL));
    char yes;
    int game_mode = -1;
    CGame game;
    while(game_mode != 4)
    {
        Clear();
        //cout << game_mode;
        game_mode = inicial();

        if(game_mode == 0) game_mode0();
        if(game_mode == 1) game.game_mode1();
        if(game_mode == 2)
        {
            ifstream inputfile("GameSave.txt", ios::in);
            if(inputfile.is_open())
            {
                {
                    cout << "THERE'S A GAME IN PROGRESS WOULD YOU LIKE TO CONTINUE IT?" << endl;
                }
                inputfile.close();
                while (!(cin >> yes) || (yes != 'n' && yes != 'y' && yes != 'N' && yes != 'Y' ))
                {
                    cerr << "INPUT A VALID CHARACTER: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                }
                yes = toupper(yes);
                if(yes == 'Y')
                {
                    game.game_mode1();
                    remove("GameSave.txt");
                    game.restart();
                    Clear();
                }
                else if (yes == 'N')
                    game.game_mode2();
            }
            else if(!inputfile.is_open())
                game.game_mode2();
        }
        if(game_mode == 3) game_mode3();
        if(game_mode == 4)
        {
            cout << endl
                 << endl
                 << "IT WAS A PLEASURE TO SERVE YOU WITH THIS GAME SIR" << endl
                 << "WE HOPE YOU HAD SO MUCH FUN PLAYING THIS GAME AS WE HAD CREATING IT" << endl
                 << "THE CREATORS:" << endl
                 << "RAFAEL LUIS" << endl
                 << "JOSE CASCA" << endl;
        }
    }
}
