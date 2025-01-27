# Checkers Game

Welcome to the **Checkers Game**! This project is a console-based implementation of the classic game of strategy and skill.
(implemented as a learning exercise in C++ programming.)

## Project Description
This is a two-player Checkers game written in **C++**. Players take turns moving their pieces diagonally across the board with the goal of capturing all of the opponent's pieces or leaving them with no valid moves. The game supports standard checkers rules, including king promotion and multi-capture sequences.

## Features
- **Interactive Main Menu**:
  - Start a new game.
  - Learn how to play with detailed instructions.
  - Exit the program.
- **Game Rules**:
  - Standard diagonal movement for regular pieces.
  - King pieces can move and capture in both forward and backward directions.
  - Double or multi-captures are supported.
- **Win Condition**:
  - The game ends when one player captures all opponent pieces or leaves them with no valid moves.
- **Dynamic Board Display**:
  - The board updates after every move, showing the current state of the game.

## File Structure
- **`main.cpp`**: The main logic of the game, including game initialization, player inputs, and move validation.
- **`winColors.hpp`**: Provides terminal color customization for an enhanced visual experience in the console.

## How to Play
1. Start the game from the main menu by selecting option `1`.
2. The board will display the positions of pieces:
   - **Red (`r`)**: Regular pieces for Player 1.
   - **Green (`g`)**: Regular pieces for Player 2.
   - **Red King (`R`)**: King pieces for Player 1.
   - **Green King (`G`)**: King pieces for Player 2.
   - `*`: Empty squares.
3. Players take turns entering moves in the format: `ROW COLUMN`.
4. The game enforces rules for valid moves, captures, and promotions.
5. The game ends when one player wins by capturing all opposing pieces or preventing further moves.

### Example Gameplay
1. Select "Start Game" from the menu.
2. Player 1 moves a piece by entering coordinates (e.g., `3 4`).
3. Player 2 takes their turn, repeating the process.
4. Capture opponents' pieces by jumping over them.
5. Reach the opponent's back row to promote a piece to a king.
6. Continue until one player wins.

## Libraries Used
- **Standard Library**:
  - `<iostream>` for input and output handling.
  - `<vector>` for managing the board structure.
  - `<string>` for handling text.
- **`winColors.hpp`**:
  - Custom header for colored console output.
  - Functions like `setTerminalColor()` are used to enhance the visual appeal.

## How to Compile and Run
1. Ensure you have a C++ compiler installed (e.g., GCC or Clang).
2. Clone the repository and navigate to the project directory.
3. Compile the program.

Ivan Soboliev - van.sob4625@gmail.com
