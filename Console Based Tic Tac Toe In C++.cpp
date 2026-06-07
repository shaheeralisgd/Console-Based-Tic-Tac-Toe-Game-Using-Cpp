#include <iostream>
using namespace std;

// Global pointers for the game state
char** board;
char currentPlayer;

// Function prototypes
void initializeBoard();
void displayBoard();
bool makeMove(int choice);
bool checkWinner();
bool checkDraw();
void switchPlayer();
void freeMemory();

// Allocates dynamic memory for a 3x3 grid and fills it with '1' through '9'
void initializeBoard()
{
    // Allocate the row array
    board = new char*;

    // Allocate columns for each individual row
    for (int i = 0; i < 3; i++)
    {
        board[i] = new char;
    }

    char position = '1';

    // Populate the board with character labels 1-9
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = position;
            position++;
        }
    }
}

// Renders the current state of the board in a clean ASCII grid
void displayBoard()
{
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            // Vertical grid dividers
            if (j < 2)
            {
                cout << " | ";
            }
        }

        cout << endl;

        // Horizontal grid dividers
        if (i < 2)
        {
            cout << "---|---|---" << endl;
        }
    }

    cout << endl;
}

// Places the current player's mark on the board if the spot is free
bool makeMove(int choice)
{
    // Map the 1-9 input to 2D array row and column indices
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    // Check if the cell still contains its original numeric label
    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = currentPlayer;
        return true;
    }

    return false; // Spot is already taken
}

// Scans rows, columns, and diagonals for a matching trio
bool checkWinner()
{
    // 1. Check all rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i] && board[i] == board[i])
        {
            return true;
        }
    }

    // 2. Check all columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i] && board[i] == board[i])
        {
            return true;
        }
    }

    // 3. Check top-left to bottom-right diagonal
    if (board == board && board == board)
    {
        return true;
    }

    // 4. Check top-right to bottom-left diagonal
    if (board == board && board == board)
    {
        return true;
    }

    return false;
}

// Returns true if the board is completely full and no one has won
bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // If any cell still holds a number, the game can continue
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

// Toggles the turn between X and O
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

// Deallocates heap memory to avoid memory leaks before the program loops or exits
void freeMemory()
{
    // Delete the sub-arrays first
    for (int i = 0; i < 3; i++)
    {
        delete[] board[i];
    }

    // Delete the top-level pointer array
    delete[] board;
}

int main()
{
    char playAgain;

    do
    {
        initializeBoard();
        currentPlayer = 'X'; // X always goes first
        bool gameOver = false;

        cout << "=================================" << endl;
        cout << "         TIC TAC TOE GAME        " << endl;
        cout << "=================================" << endl;

        // Core gameplay loop
        while (!gameOver)
        {
            displayBoard();

            int choice;
            cout << "Player " << currentPlayer << ", enter position (1-9): ";
            cin >> choice;

            // Handle non-integer inputs (e.g., if a user types letters)
            while (cin.fail())
            {
                cin.clear();            // Reset the stream state
                cin.ignore(1000, '\n'); // Purge the bad input from buffer

                cout << "Invalid input!" << endl;
                cout << "Please enter a number between 1 and 9: ";
                cin >> choice;
            }

            // Bound checking
            if (choice < 1 || choice > 9)
            {
                cout << "Position must be between 1 and 9." << endl;
                continue;
            }

            // Try to place the piece
            if (!makeMove(choice))
            {
                cout << "This position is already occupied." << endl;
                continue;
            }

            // Evaluate game state after a valid move
            if (checkWinner())
            {
                displayBoard();
                cout << "=================================" << endl;
                cout << "Player " << currentPlayer << " Wins the Game!" << endl;
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
                switchPlayer(); // Keep rolling if no match or draw
            }
        }

        // Clean up memory before starting a new round or stopping
        freeMemory();

        cout << endl;
        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << endl;
    cout << "Thank you for playing Tic Tac Toe!" << endl;

    return 0;
}
