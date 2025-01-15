#include <iostream>
#include <vector>
#include <string>
#include "winColors.hpp"
using namespace std;

const int BOARD_SIZE = 8;

enum Piece
{
    EMPTY,
    RED,
    GREEN,
    RED_KING,
    GREEN_KING
};
enum Player
{
    RED_PLAYER,
    GREEN_PLAYER
};

struct Position
{
    int row, col;
};

// function for showing the starting menu
void showMenu(bool &isStarted)
{
    int userOption = 0;
    setTerminalColor(2);
    cout << "==========================================\n";
    setTerminalColor(1);
    cout << "        Welcome to my checkers game!     \n";
    setTerminalColor(2);
    cout << "==========================================\n\n";
    setTerminalColor(0);
    cout << "Get ready to play a classic game of\n";
    setTerminalColor(1);
    cout << "strategy, ";
    setTerminalColor(2);
    cout << "skill, ";
    setTerminalColor(3);
    cout << "and fun!\n\n";
    setTerminalColor(0);
    while (true) // Infinite loop to keep asking for valid input
    {
        setTerminalColor(2);
        cout << "MAIN MENU:\n";
        setTerminalColor(0);
        cout << "1. Start Game\n";
        cout << "2. How to Play\n";
        cout << "3. Exit\n";
        setTerminalColor(4);
        cout << "Enter your choice: ";
        cin >> userOption;
        setTerminalColor(0);
        cout << "\n";

        if (cin.fail())
        {
            cin.clear();               // Clear the fail state
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number (1, 2, or 3).\n\n";
            continue;
        }

        if (userOption == 1)
        {
            isStarted = true;
            break; // Exit the loop and start the game
        }
        else if (userOption == 2)
        {
            setTerminalColor(2);
            cout << "HOW TO PLAY:\n";
            setTerminalColor(0);
            cout << "1. Your goal is to win by capturing all of your opponent's pieces or leaving them with no valid moves.\n";
            cout << "2. Move your pieces diagonally on the star squares of the board.\n";
            cout << "3. Regular pieces can move only one square forward diagonally.\n";
            cout << "4. Capture your opponent's pieces by jumping over them. Multiple jumps are allowed if possible.\n";
            cout << "5. Reach the opponent's back row to promote your piece to a KING.\n";
            cout << "6. Kings can move both forward and backward diagonally and can capture opponent pieces from any distance if the path is clear.\n";
            cout << "7. Input your moves in the format: ROW COLUMN (e.g., 3 4 or 6 7).\n\n";
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

// function for printing the board
void printBoard(const vector<vector<Piece>> &board)
{
    // printing the column headers
    cout << "    ";
    setTerminalColor(4);
    for (int col = 0; col < BOARD_SIZE; ++col)
        cout << col + 1 << "   ";
    setTerminalColor(0);
    cout << endl;
    cout << "  +---+---+---+---+---+---+---+---+\n";

    // printing the rows
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        setTerminalColor(4);
        cout << row + 1;
        setTerminalColor(0);
        cout << " |";
        // printing each piece on the board
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            cout << " ";
            switch (board[row][col])
            {
            case EMPTY:
                cout << (((row + col) % 2 == 1) ? "*" : " ");
                break;
            case RED:
                setTerminalColor(1);
                cout << "r";
                setTerminalColor(0);
                break;
            case GREEN:
                setTerminalColor(2);
                cout << "g";
                setTerminalColor(0);
                break;
            case RED_KING:
                setTerminalColor(1);
                cout << "R";
                setTerminalColor(0);
                break;
            case GREEN_KING:
                setTerminalColor(2);
                cout << "G";
                setTerminalColor(0);
                break;
            default:
                cout << " ";
                break;
            }
            cout << " |";
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
}

// function for initializing the board
void initializeBoard(vector<vector<Piece>> &board)
{
    // placing the pieces on the board
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (row < 3 && (row + col) % 2 == 1)
            {
                board[row][col] = RED;
            }
            else if (row > 4 && (row + col) % 2 == 1)
            {
                board[row][col] = GREEN;
            }
            else
            {
                board[row][col] = EMPTY;
            }
        }
    }
}

// function for checking if the move is valid
bool isValidMove(const vector<vector<Piece>> &board, Player currentPlayer, Position start, Position end)
{
    // Check if the destination is within bounds
    if (end.row < 0 || end.row >= BOARD_SIZE)
        return false;
    if (end.col < 0 || end.col >= BOARD_SIZE)
        return false;

    // Ensure moves occur only on star squares
    if ((start.row + start.col) % 2 == 0)
        return false;
    if ((end.row + end.col) % 2 == 0)
        return false;

    // Ensure if user points on his piece and not opponent's
    Piece piece = board[start.row][start.col];
    if ((currentPlayer == RED_PLAYER && piece != RED && piece != RED_KING) ||
        (currentPlayer == GREEN_PLAYER && piece != GREEN && piece != GREEN_KING))
        return false;

    // Ensure destination is empty
    if (board[end.row][end.col] != EMPTY)
        return false;

    int rowDiff = abs(end.row - start.row);
    int colDiff = abs(end.col - start.col);

    // Standard pieces (RED and GREEN)
    if (piece == RED || piece == GREEN)
    {
        if (currentPlayer == RED_PLAYER && end.row - start.row == 1 && colDiff == 1)
            return true;
        if (currentPlayer == GREEN_PLAYER && end.row - start.row == -1 && colDiff == 1)
            return true;

        if (rowDiff == 2 && colDiff == 2)
        {
            Position middle = {(start.row + end.row) / 2, (start.col + end.col) / 2};
            if ((currentPlayer == RED_PLAYER && board[middle.row][middle.col] == GREEN) ||
                (currentPlayer == GREEN_PLAYER && board[middle.row][middle.col] == RED))
                return true;
        }
    }

    // Kings (RED_KING and GREEN_KING)
    else if (piece == RED_KING || piece == GREEN_KING)
    {
        if (rowDiff == colDiff)
        { // Ensure it's a diagonal move
            int rowStep = (end.row - start.row > 0) ? 1 : -1;
            int colStep = (end.col - start.col > 0) ? 1 : -1;

            bool encounteredOpponent = false;

            for (int i = 1; i < rowDiff; ++i)
            {
                int currentRow = start.row + i * rowStep;
                int currentCol = start.col + i * colStep;

                // If there's an opponent piece in the path
                if (board[currentRow][currentCol] == (currentPlayer == RED_PLAYER ? GREEN : RED) ||
                    board[currentRow][currentCol] == (currentPlayer == RED_PLAYER ? GREEN_KING : RED_KING))
                {
                    if (encounteredOpponent)
                        return false; // Can't jump more than one piece
                    encounteredOpponent = true;
                }
                // If there's any other piece (including a friendly piece), move is invalid
                else if (board[currentRow][currentCol] != EMPTY)
                {
                    return false;
                }
            }

            // If it's an attack move, ensure exactly one opponent piece was encountered
            if (encounteredOpponent)
            {
                return board[end.row][end.col] == EMPTY; // Ensure destination is empty
            }

            // If no opponent was encountered, it's a valid non-attack move
            return true;
        }
    }

    return false;
}

// function for making the move
void makeMove(vector<vector<Piece>> &board, Player currentPlayer, Position start, Position end, bool &isCaptured)
{
    Piece piece = board[start.row][start.col];
    board[end.row][end.col] = piece;
    board[start.row][start.col] = EMPTY;
    // Handle jumps (for both regular pieces and kings)
    int rowDiff = abs(end.row - start.row);
    int colDiff = abs(end.col - start.col);
    isCaptured = false;

    if (rowDiff > 1 && colDiff > 1)
    { // Jump occurred
        int rowStep = (end.row - start.row > 0) ? 1 : -1;
        int colStep = (end.col - start.col > 0) ? 1 : -1;
        isCaptured = true;

        for (int i = 1; i < rowDiff; ++i)
        {
            int currentRow = start.row + i * rowStep;
            int currentCol = start.col + i * colStep;
            isCaptured = false;

            // If the king jumps over an opponent piece, remove it
            if (board[currentRow][currentCol] == (currentPlayer == RED_PLAYER ? GREEN : RED) ||
                board[currentRow][currentCol] == (currentPlayer == RED_PLAYER ? GREEN_KING : RED_KING))
            {
                board[currentRow][currentCol] = EMPTY;
                isCaptured = true;
                break;
            }
        }
    }

    // Promote to king if applicable
    if (currentPlayer == RED_PLAYER && end.row == BOARD_SIZE - 1 && piece == RED)
    {
        board[end.row][end.col] = RED_KING;
    }
    else if (currentPlayer == GREEN_PLAYER && end.row == 0 && piece == GREEN)
    {
        board[end.row][end.col] = GREEN_KING;
    }
}

// function for checking if the player has any moves left
bool hasMoves(const vector<vector<Piece>> &board, Player player)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if ((player == RED_PLAYER && (board[row][col] == RED || board[row][col] == RED_KING)) ||
                (player == GREEN_PLAYER && (board[row][col] == GREEN || board[row][col] == GREEN_KING)))
            {
                Position start = {row, col};
                for (int dr = -1; dr <= 1; dr += 2)
                {
                    for (int dc = -1; dc <= 1; dc += 2)
                    {
                        Position end = {row + dr, col + dc};
                        if (isValidMove(board, player, start, end))
                        {
                            setTerminalColor(3);
                            cout << "Valid move for " << (player == RED_PLAYER ? "Red" : "Green")
                                 << " from (" << start.row + 1 << " " << start.col + 1 << ") to ("
                                 << end.row + 1 << " " << end.col + 1 << ")" << endl;
                            setTerminalColor(0);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// function for checking if the player has won
bool hasWon(const vector<vector<Piece>> &board, Player player)
{
    Piece opponentPiece = (player == RED_PLAYER) ? GREEN : RED;
    Piece opponentKing = (player == RED_PLAYER) ? GREEN_KING : RED_KING;

    bool opponentExists = false;

    for (const auto &row : board)
    {
        for (Piece piece : row)
        {
            if (piece == opponentPiece || piece == opponentKing)
            {
                opponentExists = true;
            }
        }
    }

    if (!opponentExists)
    {
        setTerminalColor(3);
        cout << "Opponent has no pieces left." << endl;
        setTerminalColor(0);
        return true;
    }

    Player opponent = (player == RED_PLAYER) ? GREEN_PLAYER : RED_PLAYER;
    if (!hasMoves(board, opponent))
    {
        setTerminalColor(3);
        cout << "Opponent has no valid moves left." << endl;
        setTerminalColor(0);
        return true;
    }

    return false;
}

// function for getting the input from the user
void getInput(Position &pos, const string &prompt)
{
    while (true)
    {
        cout << prompt;
        cin >> pos.row >> pos.col;
        if (cin.fail() || pos.row < 1 || pos.row > BOARD_SIZE || pos.col < 1 || pos.col > BOARD_SIZE)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTerminalColor(1);
            cout << "Invalid input. Enter numbers between 1 and 8.\n";
            setTerminalColor(0);
        }
        else
        {
            pos.row--;
            pos.col--;
            break;
        }
    }
}

// function for running the game
void playGame()
{
    vector<vector<Piece>> board(BOARD_SIZE, vector<Piece>(BOARD_SIZE, EMPTY));
    initializeBoard(board);

    Player currentPlayer = RED_PLAYER;
    bool isCaptured = false;

    while (true)
    {
        printBoard(board);

        if (!hasMoves(board, currentPlayer))
        {
            if (currentPlayer == RED_PLAYER)
            {
                setTerminalColor(2);
                cout << "Green wins!" << endl;
                setTerminalColor(0);
            }
            else
            {
                setTerminalColor(1);
                cout << "Red wins!" << endl;
                setTerminalColor(0);
            }
            break;
        }
        if (currentPlayer == RED_PLAYER)
        {
            setTerminalColor(1);
            cout << "Red's turn" << endl;
            setTerminalColor(0);
        }
        else
        {
            setTerminalColor(2);
            cout << "Green's turn" << endl;
            setTerminalColor(0);
        }

        Position start, end;
        getInput(start, "Enter start position (row col): ");
        getInput(end, "Enter end position (row col): ");
        cout << "\n\n";

        if (isValidMove(board, currentPlayer, start, end))
        {
            makeMove(board, currentPlayer, start, end, isCaptured);
            if (!isCaptured)
            {
                currentPlayer = (currentPlayer == RED_PLAYER) ? GREEN_PLAYER : RED_PLAYER;
            }
        }
        else
        {
            setTerminalColor(1);
            cout << "Invalid move. Try again.\n\n";
            setTerminalColor(0);
        }
    }
}

int main()
{
    bool isStarted = false;
    bool isFinished = false;

    showMenu(isStarted);
    if (isStarted)
    {
        playGame();
    }
    system("Pause");
}