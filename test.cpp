#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "winColors.hpp"

using namespace std;

constexpr int ROWS = 8;
constexpr int COLS = 8;

enum Piece
{
    EMPTY = 1,
    RED = 2,
    GREEN = 3,
    REDKING = 4,
    GREENKING = 5
};

void runGame(vector<vector<int>> &board, int i, int k, char l, char j, string move_from, string move_to);
void printDisplay(const vector<vector<int>> &board);
void swapIJKL(vector<vector<int>> &board, int i, int j, int k, int l);
char valueToSymbol(int i);
int Playersturn(vector<vector<int>> &board, int player, int i, int j, int k, int l);

void printDisplay(const vector<vector<int>> &board)
{
    cout << "    a   b   c   d   e   f   g   h\n";
    cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int rr = 0; rr < ROWS; ++rr)
    {
        cout << rr + 1 << " |";
        for (int cc = 0; cc < COLS; ++cc)
        {
            cout << " ";
            switch (board[rr][cc])
            {
            case RED:
                setTerminalColor(1);
                break;
            case GREEN:
                setTerminalColor(2);
            default:
                break;
            }
            wcout << valueToSymbol(board[rr][cc]);
            setTerminalColor(0);
            cout << " |";
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
}

void swapIJKL(vector<vector<int>> &board, int i, int j, int k, int l)
{
    swap(board[i][j], board[k][l]);
}

char valueToSymbol(int i)
{
    switch (i)
    {
    case EMPTY:
        return '*';
    case RED:
        return 'r';
    case GREEN:
        return 'g';
    case REDKING:
        return 'R';
    case GREENKING:
        return 'G';
    default:
        return ' ';
    }
}

int Playersturn(vector<vector<int>> &board, int player, int i, int j, int k, int l)
{
    int jmp_r, jmp_c;

    cout << (player == RED ? "RED" : "GREEN") << " move from "
         << i + 1 << "," << j + 1 << " to " << k + 1 << "," << l + 1 << "\n";

    if (i < 0 || i >= ROWS || j < 0 || j >= COLS || k < 0 || k >= ROWS || l < 0 || l >= COLS)
    {
        cout << "Move is out of bounds\n";
        return -1;
    }

    if ((player == RED && board[i][j] != RED) || (player == GREEN && board[i][j] != GREEN))
    {
        cout << "Move your own piece!\n";
        return -1;
    }

    if (board[k][l] != EMPTY)
    {
        cout << "You must move to an empty location\n";
        return -1;
    }

    if ((player == RED && i >= k) || (player == GREEN && i <= k))
    {
        cout << (player == RED ? "RED" : "GREEN") << " player must move in the correct direction\n";
        return -1;
    }

    if ((i - k == -1 || i - k == 1) && (j - l == 1 || j - l == -1))
    {
        swapIJKL(board, i, j, k, l);
        return 0;
    }

    if ((i - k == -2 || i - k == 2) && (j - l == -2 || j - l == 2))
    {
        jmp_r = i + ((k > i) ? 1 : -1);
        jmp_c = j + ((l > j) ? 1 : -1);

        if ((player == RED && board[jmp_r][jmp_c] != GREEN) || (player == GREEN && board[jmp_r][jmp_c] != RED))
        {
            cout << "You can only jump over an enemy player\n";
            return -1;
        }

        board[jmp_r][jmp_c] = EMPTY;
        swapIJKL(board, i, j, k, l);
        return 0;
    }

    cout << "You can only move diagonally\n";
    return -1;
}

// generate the menu, start the game or exit
void showMenu(bool &isStarted)
{
    int userOption = 0;
    setTerminalColor(2);
    cout << "=======================================\n";
    setTerminalColor(1);
    cout << "       Welcome to my checkers game!    \n";
    setTerminalColor(2);
    cout << "=======================================\n\n";
    setTerminalColor(0);
    cout << "Get ready to play a classic game of ";
    setTerminalColor(1);
    cout << "strategy, ";
    setTerminalColor(2);
    cout << "skill, ";
    setTerminalColor(3);
    cout << "and fun!\n\n";
    setTerminalColor(0);
    while (true) // Infinite loop to keep asking for valid input
    {
        setTerminalColor(1);
        cout << "MAIN MENU:\n";
        setTerminalColor(0);
        cout << "1. Start Game\n";
        cout << "2. How to Play\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userOption;
        cout << "\n";

        if (cin.fail())
        {
            cin.clear();               // Clear the fail state
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number (1, 2, or 3).\n\n";
            continue; // Loop again
        }

        if (userOption == 1)
        {
            isStarted = true;
            break; // Exit the loop and start the game
        }
        else if (userOption == 2)
        {
            setTerminalColor(1);
            cout << "HOW TO PLAY:\n";
            setTerminalColor(0);
            cout << "1. Move your pieces diagonally on the board.\n";
            cout << "2. Capture your opponent's pieces by jumping over them.\n";
            cout << "3. Try to reach the opponent's side of the board to get a KING piece!\n";
            cout << "Input your moves in the format: ROWCOLUMN (e.g., 3a or 6h).\n\n";
        }
        else if (userOption == 3)
        {
            exit(0); // Exit the program
        }
        else
        {
            cout << "Invalid input. Please enter a valid option (1, 2, or 3).\n\n";
        }
    }
}

void runGame(vector<vector<int>> &board, int i, int k, char l, char j, string move_from, string move_to)
{
    while (true)
    {
        printDisplay(board);
        while (true)
        {
            cout << "Red's turn (format 3a): \n";
            cout << "From: ";
            cin >> move_from;
            cout << "To: ";
            cin >> move_to;

            cout << move_from[0] - '1' << endl;
            cout << move_from[1] - 'a' << endl;

            // Parse the input if it matches the expected format
            if (move_from.length() == 2 && move_to.length() == 2 &&
                isdigit(move_from[0]) && isalpha(move_from[1]) &&
                isdigit(move_to[0]) && isalpha(move_to[1]))
            {
                i = move_from[0] - '1'; // Convert row from char to int index
                j = move_from[1];
                k = move_to[0] - '1';
                l = move_to[1];

                // Execute the move if valid
                if (Playersturn(board, RED, i, j - 'a', k, l - 'a') == 0)
                    break;
            }
            else
            {
                cout << "Invalid input format. Please enter as DigitLetter (e.g., 3a).\n";
            }
            cout << "Illegal move, try again\n\n";
        }

        printDisplay(board);
        while (true)
        {
            cout << "GREEN's turn (format a3): \n";
            cout << "From: ";
            cin >> move_from;
            cout << "To: ";
            cin >> move_to;

            if (move_from.length() == 2 && move_to.length() == 2 &&
                isdigit(move_from[0]) && isalpha(move_from[1]) &&
                isdigit(move_to[0]) && isalpha(move_to[1]))
            {
                i = move_from[0] - '1';
                j = tolower(move_from[1]) - 'a';
                k = move_to[0] - '1';
                l = tolower(move_to[1]) - 'a';

                if (Playersturn(board, GREEN, i, j, k, l) == 0)
                    break;
            }
            else
            {
                cout << "Invalid input format. Please enter as DigitLetter (e.g., 3a).\n";
            }
            cout << "Illegal move, try again\n\n";
        }
    }
}

int main()
{

    vector<vector<int>> board = {
        {0, RED, 0, RED, 0, RED, 0, RED},
        {RED, 0, RED, 0, RED, 0, RED, 0},
        {0, RED, 0, RED, 0, RED, 0, RED},
        {EMPTY, 0, EMPTY, 0, EMPTY, 0, EMPTY, 0},
        {0, EMPTY, 0, EMPTY, 0, EMPTY, 0, EMPTY},
        {GREEN, 0, GREEN, 0, GREEN, 0, GREEN, 0},
        {0, GREEN, 0, GREEN, 0, GREEN, 0, GREEN},
        {GREEN, 0, GREEN, 0, GREEN, 0, GREEN, 0}};

    int i, k;
    char j, l;
    string move_from, move_to;
    bool isStarted = false;
    bool isFinished = false;

    showMenu(isStarted);

    if (isStarted)
    {
        while (true)
        {
            runGame(board, i, k, l, j, move_from, move_to);
        }
    }

    return 0;
}