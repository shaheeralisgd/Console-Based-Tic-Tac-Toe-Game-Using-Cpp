#include <iostream>
using namespace std;

char** board;
char currentPlayer;


void initializeBoard();
void displayBoard();
bool makeMove(int choice);
bool checkWinner();
bool checkDraw();
void switchPlayer();
void freeMemory();

void initializeBoard()
{
    board = new char* [3];

    for (int i = 0; i < 3; i++)
    {
        board[i] = new char[3];
    }

    char position = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = position;
            position++;
        }
    }
}

void displayBoard()
{
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
            {
                cout << " | ";
            }
        }

        cout << endl;

        if (i < 2)
        {
            cout << "---|---|---" << endl;
        }
    }

    cout << endl;
}

bool makeMove(int choice)
{
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' &&
        board[row][col] != 'O')
    {
        board[row][col] = currentPlayer;
        return true;
    }

    return false;
}

bool checkWinner()
{

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            return true;
        }
    }


    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
        {
            return true;
        }
    }


    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return true;
    }


    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return true;
    }

    return false;
}

bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

void switchPlayer()
{
    if (currentPlayer == 'X')
    {
        currentPlayer = 'O';
    }
    else
    {
        currentPlayer = 'X';
    }
}

void freeMemory()
{
    for (int i = 0; i < 3; i++)
    {
        delete[] board[i];
    }

    delete[] board;
}
int main()
{
    char playAgain;

    do
    {
        initializeBoard();

        currentPlayer = 'X';

        bool gameOver = false;

        cout << "=================================" << endl;
        cout << "         TIC TAC TOE GAME        " << endl;
        cout << "=================================" << endl;

        while (!gameOver)
        {
            displayBoard();

            int choice;

            cout << "Player " << currentPlayer
                << ", enter position (1-9): ";

            cin >> choice;

           
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid input!" << endl;
                cout << "Please enter a number between 1 and 9: ";
                cin >> choice;
            }

      
            if (choice < 1 || choice > 9)
            {
                cout << "Position must be between 1 and 9." << endl;
                continue;
            }

     
            if (!makeMove(choice))
            {
                cout << "This position is already occupied." << endl;
                continue;
            }

            if (checkWinner())
            {
                displayBoard();

                cout << "=================================" << endl;
                cout << "Player " << currentPlayer
                    << " Wins the Game!" << endl;
                cout << "=================================" << endl;

                gameOver = true;
            }

        
            else if (checkDraw())
            {
                displayBoard();

                cout << "=================================" << endl;
                cout << "Game Draw!" << endl;
                cout << "=================================" << endl;

                gameOver = true;
            }

            else
            {
                switchPlayer();
            }
        }

        freeMemory();

        cout << endl;
        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << endl;
    cout << "Thank you for playing Tic Tac Toe!" << endl;

    return 0;
}


