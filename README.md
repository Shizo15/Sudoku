# Sudoku CLI

**Sudoku CLI** is a text-based Sudoku game written in C. The program allows the user to play Sudoku of various sizes and difficulty levels without the need for a graphical interface.

### 🎮 Gameplay

![sudoku](https://github.com/user-attachments/assets/429aaeea-8c67-484b-8ba7-a0ccc0e8ca29)

### **Rest of the functionality:**

![functions](https://github.com/user-attachments/assets/5437ec83-9785-489b-aa2c-44edff5d318e)




## 🧩 Features

- Board sizes: `4x4`, `9x9`, `16x16`
- Three difficulty levels:
  - Easy (more hints)
  - Medium
  - Hard (fewer hints)
- Text-based interface (terminal)
- Save and load game state
- Validate solution correctness
- Game timer, empty cell counter, and mistake tracker
- Built-in help/instructions
- Error handling and input validation

## 🛠️ Compilation (Windows, with MinGW)

You’ll need a C compiler (e.g. `gcc`). Make sure the `sudoku.h` header file is in the same directory. Open `cmd` or another terminal, navigate to the game folder, and run:

```bash
gcc main.c -o sudoku.exe

sudoku.exe
```


## 📋 Controls
1. Start a new game or load a previously saved one.
2. Choose the board size and difficulty level.
3. Use the game menu to:
   -  Make a move (enter row, column, and value separated by spaces)
   -  Save the game
   -  Show instructions
4. To clear a cell, enter `0` as the value.
5. Some cells (hints) are locked and cannot be modified.

## ⚠️ Known Issues & Limitations
- No validation for unique Sudoku solutions (a generated puzzle may have more than one valid solution).
- The `clearConsole()` function is commented out and must be adjusted to your OS (`system("cls")` / `system("clear")`). Its use may cause issues.
- No undo feature (you can overwrite a move or clear it by entering 0, but you can't revert it directly).

Memiki budowlane na poprawę humoru :)

<img src="https://github.com/user-attachments/assets/39272a89-7888-4cd6-b041-a8b07713711f" alt="meme1" width="450">

Another:

<img src="https://github.com/user-attachments/assets/4d815ab6-5f3f-474b-a6bf-c2431d6221b1" alt="meme2" width="450">

And another: 

<img src="https://github.com/user-attachments/assets/686c5760-f175-4fe6-83fc-8945a4def1db" alt="meme3" width="450">

