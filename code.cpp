// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT6L 
// Names: DOAA NOAH| ALHALAH RAED | ALHAWBANI HUSAM
// IDs: 1211310715 | 1221302663 | 1221303182 
// Emails: 1211310715@student.mmu.edu.my | 1221302663@student.mmu.edu.my  | @student.mmu.edu.my  
// Phones: 116456258 | 109006407 | 166084068
// ********************************************************* 
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

class Alien
{
public:
    int x, y, life, attack;
    char direction;
};

class Zombie
{
public:
    int x, y, life, attack, range;
    char name;
};

int Rows = 5, Columns = 9, zombie = 1;
char **getboard();
void Continue(),PlacePlayers(Alien &, char **), Settings(), boardcustom(), Placeobjects(char **), displayboard(char **), Players(Alien &, vector<Zombie> &), makeboard(Alien &a, vector<Zombie> &zombies, char **board);
 

void Continue()
{
    cout << "Press any key to continue..." << endl
         << endl;
}

void Settings()
{
    string choice;
    cout << "Default Game Settings" << endl;
    cout << "------------------------" << endl;
    cout << "Board Rows :" << Rows << endl;
    cout << "Board Columns :" << Columns << endl;
    cout << "Zombie Count :" << zombie << endl;
    cout << "Do you wish to change the game settings (yes/no)?\n";
    cin >> choice;

    if (choice == "yes" || choice == "YES")
    {
        boardcustom();
        cout << "Settings updated" << endl
             << endl;
        cout << "Alien vs Zombies" << endl;
    }
    else
    {
        cout << "Alien vs Zombies" << endl;
        Columns = (Columns * 2) + 1;
        Rows = (Rows * 2) + 1;
    }
}

void boardcustom()
{
    int Row_temp = 1, Col_temp = 1;
    do
    {
        if (Row_temp % 2 == 0 || Col_temp % 2 == 0)
            cout << "Invalid input, rows and columns must be odd.\n";
        cout << "Enter the number of rows => ";
        cin >> Row_temp;
        cout << "Enter the number of columns columns => ";
        cin >> Col_temp;
    } while (Row_temp % 2 == 0 || Col_temp % 2 == 0);
    Columns = (Col_temp * 2) + 1;
    Rows = (Row_temp * 2) + 1;
do
    {
        if (zombie <= 0 )
            cout << "Invalid input. Number of zombies must be a higher than 0.\n";
        cout << "Enter number of zombies => ";
        cin >> zombie;
    }
    while (zombie <= 0 );
    Continue();
}

char **getboard()
{
    char **temp = new char *[Rows];
    for (int i = 0; i < Rows; i++)
        temp[i] = new char[Columns];
    return temp;
}

void displayboard(char **board)
{
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Columns; j++)
            cout << board[i][j];
        cout << endl;
    }
}


void Players(Alien &a, vector<Zombie> &zombies)
{
    a.life = rand() % 100 + 1;
    a.attack =rand() % a.life + 1;
    for (int i = 0; i < zombie; i++)
    {
        Zombie z;
        z.name = i + '1';
        z.life = rand() % 50 + 50;        
        z.attack = rand() % 20 + 10;
        z.range = rand() % (min(Rows, Columns) / 2) + 1;
        z.x = rand() % (Rows - 1) | 1;
        z.y = rand() % (Columns - 1) | 1;
        zombies.push_back(z);
    }
}
void Placeobjects(char **board)
{
    char nonTrailObjects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' '};

    int numberOfObjects = rand() % (Rows * Columns - 1);
    int randX, randY;

    // vector<GameObject> gameObjects;
    for (int i = 0; i < numberOfObjects; i++)
    {
        int randomIndex = rand() % (sizeof(nonTrailObjects) / sizeof(nonTrailObjects[0]));
        // GameObject obj;
        char type = nonTrailObjects[randomIndex];
        randX = (rand() % (Rows - 1)) | 1;
        randY = (rand() % (Columns - 1)) | 1;

        board[randX][randY] = type;
    }
}
void PlacePlayers(Alien &alien, char **board)
{
    alien.x = Rows / 2;
    alien.y = Columns / 2;
    board[alien.x][alien.y] = 'A';
}
void PlaceZombie(vector<Zombie> &zombies,Alien alien,char **board)
{
    // Place the zombies randomly on the board
    for (int i = 0; i < zombies.size(); i++)
    {
        bool occupied = true;
        do
        {
            zombies[i].x = (rand() % (Rows - 1)) | 1;
            zombies[i].y = (rand() % (Columns - 1)) | 1;

            occupied = false;
            for (int j = 0; j < i; j++)
            {
                if (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y || (zombies[i].x == alien.x && zombies[i].y == alien.y))
                {
                    occupied = true;
                    break;
                }
            }

        } while (occupied);

        board[zombies[i].x][zombies[i].y] = zombies[i].name;
    }
}
void makeboard(Alien &alien, vector<Zombie> &zombies, char **board)
{
   
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    board[i][j] = '+';
                }
                else
                {
                    board[i][j] = '-';
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    board[i][j] = '|';
                }
                else
                {
                    board[i][j] = ' ';
                }
            }
        }
    }
    Placeobjects(board);
    PlacePlayers(alien,board);
    PlaceZombie(zombies,alien,board);
}
int main()
{
    srand(time(0));
    Alien a;
    vector<Zombie> zombies;
    Settings();
    char **board = getboard();
    Players(a, zombies);
    makeboard(a, zombies, board);
    displayboard(board);
    return 0;
}