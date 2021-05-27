# battleship_grp30
![](https://github.com/horaceyin/Battleship_grp30/blob/main/images/battleship2.jpg)
## Team member:
```
Wong Ho Yin Horace (3035762580) - horaceyin
Pang Sze Hang Karen (3035592650) - karenpsh54
```
## Game objective:
* Try and destroy all of your opponent’s (computer’s) ships before the computer destroys all of your ships
## Game Description:
* This is a two-player game, where your opponent is the computer.
* There are two game boards for each player - the Ocean Grid and Tracking Grid. The Ocean Grid is for you to place the ships while the Tracking Grid is for you to mark down your “hit” and “miss” of the opponents’ ships. 
* There are five types of ships - Carrier (occupies 5 spaces), Battleship (4), Submarine (4), Destroyer (3), and Patrol Boat(2). 
* Please be reminded that ships are not allowed to be placed diagonally and they cannot overlap each other.

## How to play:
1. Before the start of the game, place the 5 ships on your Ocean Grid. At the same time, the computer will generate a random Ocean Grid with the 5 ships placed.
2. After the game starts, players are not allowed to move the ships.
3. Players take turns to make guesses about the coordinates of the opponent’s ships. You can type in the coordinates of the ship to enter your guess.
4. A Game Status Board below the grids will appear. If the coordinates you entered corresponds to a ship on the computer’s Ocean Grid, the value of "Target Hit" in the Game Status Board will increase by 1. Otherwise, the value of "Target Miss" will increase by 1. 
5. Automatically, the program will help you mark down your guesses on your Tracking Grid. “H.” means hit and “M.” means miss.
6. When the computer hits your ship, the corresponding coordinate on your Ocean Grid will be marked with “X.”. Otherwise, it will be marked with "M.".
7. The first player to destroy all the opponent’s ships wins.

## Features to be implemented:
1. Generation of random game sets or events
   * Random game sets: The opponent is a computer and it places 5 ships on the Ocean Grid randomly before the start of each game.
   * Random events: The opponent will also guess a point like A3 or D10 and hit it.
2. Data structures for storing game status
   * There are some data types or structures, e.g. arrays, pointers etc., used to store the game status including number of rounds, how many ships remain or whose turn it is. More importantly, we need to store the coordinates that the computer or player guessed on the Tracking Grids.
3. Dynamic memory management
   * Prompt the user the size of the grid she/he wants to play. At the beginning of the program, we will ask the operation system to reserve some memories and save the size of the grid into an array. If the user says that she/he wants to play Battleship with 10 x 10 grid. A dynamic array with size of 100 will be created. Some reserved memories will be used to create this array, while the remaining reserved memories will be released to the operation system after the end of the program.
4. File input/output (e.g., for loading/saving game status)
   * Saving game status and output it as a text file (named as player's name) which involves the player's name, grid size, latest Grids, attack coordination history and values in the Game Status Board before you exit the game.
5. Program codes in multiple files
   * Use the object-oriented concept to develop the game. 
   * There are multiple header files and .cpp for different functions, which will be compiled together with the use of Makefile to generate the program for the game.
    1. main.cpp: contains the main structure of the game
    2. tutorial.cpp: shows the user how to play with graphics
    3. menu.cpp: shows graphics for the menu and process user's selected menu item

## Compilation and execution instructions
1. Put gameboard.cpp, menu.cpp, menu.h, tutorial.cpp, tutorial.h and makefile into the same directory.
2. Change the current working directory.
    + `cd directoryname/`
3. Use makefile to compiler `*.cpp` files.
    + `make battleship_grp30`
4. Run the executable file to execute the program.
    + `./battleship_grp30`

5. Then, you will see the first screen.
![](https://github.com/horaceyin/Battleship_grp30/blob/main/images/The%20first%20screen.png)

6. Enter the number: 1 - 4 to go to the next step.
    + `1: Start a new game, and require a new player name`
    + `2: Resume the game, and enter a player name to resume`
    + `3: Start a tutorial`
    + `4: Quit the program`
   
## Contact us:
**Wong Ho Yin Horace**
> E-mail: u3576258@connect.hku.hk

**Pang Sze Hang Karen**
> E-mail: karenpsh@connect.hku.hk
