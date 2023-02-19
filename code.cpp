// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT6L
// Names: DOAA NOAH| ALHALAH RAED | ALHAWBANI HUSAM
// IDs: 1211310715 | 1221302663 | 1221303182
// Emails: 1211310715@student.mmu.edu.my | 1221302663@student.mmu.edu.my  | 1221303182@student.mmu.edu.my
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

int Rows = 5, Columns = 9, zombie = 1, current = 0;
char **getboard();
int infectNearestZombie(Alien &alien, vector<Zombie> &zombies);
void Continue(), PlacePlayers(Alien &, char **), Settings(), boardcustom(), Placeobjects(char **), displayboard(char **), alienmov(Alien &alien, char **board, vector<Zombie> &zombies), inputCommand(Alien &alien),
    Players(Alien &, vector<Zombie> &), makeboard(Alien &a, vector<Zombie> &zombies, char **board), checkNextStop(char nextLocation, Alien &alien, vector<Zombie> &zombies), Status(Alien a, vector<Zombie> z);

void Continue()
{
    cout << "Press any key to continue..." << endl
         << endl;
    cin.ignore();
    cin.ignore();
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
        if (zombie <= 0)
            cout << "Invalid input. Number of zombies must be a higher than 0.\n";
        cout << "Enter number of zombies => ";
        cin >> zombie;
    } while (zombie <= 0);
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
    a.attack = rand() % a.life + 1;
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
void PlaceZombie(vector<Zombie> &zombies, Alien alien, char **board)
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
    PlacePlayers(alien, board);
    PlaceZombie(zombies, alien, board);
}

void checkNextStops(char nextLocation, Alien &alien, vector<Zombie> &zombies)
{
    int zombieNumber;
    switch (nextLocation)
    {
    case '^':
    case 'v':
    case '<':
    case '>':
        alien.direction = nextLocation;
        alien.attack += 20;
        cout << "Alien changes direction to " << nextLocation << endl;
        break;
    case 'h':
        alien.life += 20;
        cout << "Alien locates a health pack " << endl;
        cout << "Alien's life increased by 20 " << endl
             << endl;
        break;
    case 'p':
        zombieNumber = infectNearestZombie(alien, zombies);
        cout << "Zombie " << zombieNumber << " has been damaged by 10. " << endl;
        break;
    case ' ':
    case '.':
        cout << "Alien locates an empty space" << endl;
        break;
    default:
        // invalid input
        break;
    }
}
char nonTrailObject()
{
    char nonTrailObjects[] = {'^', 'v', '<', '>', 'h', 'p', 'r', ' '};
    int randomIndex = rand() % (sizeof(nonTrailObjects) / sizeof(nonTrailObjects[0]));
    return nonTrailObjects[randomIndex];
}
void alienmov(Alien &alien, char **board, vector<Zombie> &zombies)
{
    inputCommand(alien);
    while (true)
    {
        int nextX = alien.x;
        int nextY = alien.y;
        // calculate the next location based on the current direction
        switch (alien.direction)
        {
        case '^':
            nextX -= 2;
            break;
        case 'v':
            nextX += 2;
            break;
        case '<':
            nextY -= 2;
            break;
        case '>':
            nextY += 2;
            break;
        }

        if (nextX < 0 || nextX >= Rows || nextY < 0 || nextY >= Columns)
        {
            cout << "Alien reaches a board border, turn ended." << endl;
            return;
        }

        char nextLocation = board[nextX][nextY];

        if (nextLocation == 'r')
        {
            cout << "Alien hits a rock and can't move" << endl;

            while (board[nextX][nextY] == 'r')
            {
                board[nextX][nextY] = nonTrailObject();
            }

            break;
        }

        checkNextStops(nextLocation, alien, zombies);
        board[nextX][nextY] = 'A';
        board[alien.x][alien.y] = '.';
        alien.x = nextX;
        alien.y = nextY;
        Continue();
        system("CLS");
        displayboard(board);
        Status(alien, zombies);
    }
}
void inputCommand(Alien &alien)
{
    cout << "\n\nEnter command or help to show the menu " << endl;
    string command;
    cin >> command;
    if (command == "up")
    {
        alien.direction = '^';
    }
    else if (command == "down")
    {
        alien.direction = 'v';
    }
    else if (command == "left")
    {
        alien.direction = '<';
    }
    else if (command == "right")
    {
        alien.direction = '>';
    }
    else if (command == "help")
    {
        cout << "Commands: up, down, left, right, help, save, load, quit" << endl;
    }
    else if (command == "quit")
    {
        cout << "Are you sure you want to quit? yes/no" << endl;
        string confirm;
        cin >> confirm;
        if (confirm == "yes")
        {
            exit(0);
        }
    }
    else
    {
        cout << "Invalid command. Type 'help' for a list of commands." << endl;
    }
    return;
}
int infectNearestZombie(Alien &alien, vector<Zombie> &zombies)
{
    int closestZombieIndex = -1;
    int minDistance = INT_MAX;
    for (int i = 0; i < zombies.size(); i++)
    {
        int distance = abs(alien.x - zombies[i].x) + abs(alien.y - zombies[i].y);
        if (distance < minDistance)
        {
            minDistance = distance;
            closestZombieIndex = i;
        }
    }
    if (closestZombieIndex != -1)
    {
        zombies[closestZombieIndex].life -= 10;
        cout << "Zombie " << closestZombieIndex << " has been damaged." << endl;
    }
    return closestZombieIndex;
}
void Status(Alien a, vector<Zombie> z)
{
    if (0 == current)
    {
        cout << "->  ";
    }
    cout << "Alien  "
         << "  Life   : " << a.life << "    Attack: " << a.attack << endl;

    for (int i = 0; i < z.size(); i++)
    {
        if (z[i].name - '0' == current)
        {
            cout << "->  ";
        }

        cout << "Zombie " << i + 1 << ":"
             << "    Life: " << z[i].life << "     Attack: " << z[i].attack << "     Range: " << z[i].range << endl;
    }
    cout << endl
         << endl;
}
bool valid(int x, int y, char **b)
{

    if (b[x][y] != 'A' && (b[x][y] < '1' || b[x][y] > '9'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void zombies_turn(Alien &alien, char **board, Zombie &zombie)
{

    int x = zombie.x;
    int y = zombie.y;
    char moves[4] = {'v', '^', '<', '>'};
    int moveIndex;
    string moveDirection;
    do
    {
        moveIndex = rand() % 4;
        char move = moves[moveIndex];
        if (move == 'v')
        { 
            x = zombie.x + 2;
            moveDirection = "Down";
        }
        else if (move == '^')
        { 
            x = zombie.x - 2;
            moveDirection = "Up";
        }
        else if (move == '>')
        { 
            y = zombie.y + 2;
            moveDirection = "Right";
        }
        else if (move == '<')
        { 
            y = zombie.y - 2;
            moveDirection = "Left";
        }
    } while (!(valid(x, y, board)));

    cout << "Zombie moves " << moveDirection << endl;
    
    board[zombie.x][zombie.y] = ' ';
    zombie.x = x;
    zombie.y = y;
    board[zombie.x][zombie.y] = zombie.name;

   
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
    Status(a, zombies);
    while (true)
    {

        alienmov(a, board, zombies);
        for (int i = 0; i < zombies.size(); i++)
        {
            current++;
            Continue();
            system("CLS");
            displayboard(board);
            Status(a, zombies);

            zombies_turn(a, board, zombies[i]);
            Continue();
            system("CLS");
            displayboard(board);
            Status(a, zombies);
        }
    }
    return 0;
}
