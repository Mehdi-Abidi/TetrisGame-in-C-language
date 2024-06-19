Tetris Game
This is a console-based Tetris game implemented in C. It runs on Windows and uses basic console graphics and keyboard input for controls.

Features
->Simple Console Graphics: Uses ASCII characters to represent Tetris blocks and the game board.
->Keyboard Controls: Arrow keys for left, right, and down movement; 'e' to exit; 'p' to pause.
->Score Tracking: Saves the highest score achieved in a score.txt file.

Setup
Prerequisites
->Windows OS (due to the use of <Windows.h> for console handling)
->C compiler (like MinGW or Visual Studio with C++/C support)

Installation
1) Clone the repository:
bash
git clone https://github.com/Mehdi-Abidi/TetrisGame-in-C-language.git

2)Navigate to the project directory:
bash
cd TetrisGame-in-C-language

3)Compile the code (using GCC):
bash
gcc maingame.c -o tetris.exe

Usage

1)Run the executable:
bash
./tetris.exe

2)Main Menu:
->Use arrow keys to navigate through the menu options.
->Press 's' to start the game.
->Follow on-screen instructions for controls (left, right, down arrow keys).

3)During the Game:
->Use arrow keys to move the falling block.
->Press 'e' to exit the game.
->Press 'p' to pause the game.

4)Game Over:
->When the game ends, your score will be displayed.
->If your score beats the previous best score (stored in score.txt), it will be updated.

Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
