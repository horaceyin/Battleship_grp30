#include <iostream>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "menu.h"
#include "tutorial.h"

using namespace std;

#define MAXSHIP 5
#define ALLPOINT 17

//to get a input line from player without function of cin.ignore(), By Horace
string my_getline()
{
    string result;

    while (!getline(cin, result) || result.empty());

    return result;
}



// data structure to keep game parameters
// initialize the game parameters by input board grid size;
struct game{
//    char hit = 'X', miss = 'M';
//    string empty = "--";
//    int size = 0 , maxship = 0, maxshot = 0;
    string empty, hit, miss, sizeString, sizeStringTemp, playerName;
    int size, maxshot;

    //get the size and the name from player
    void getboardsize(){

        cout << "Hello !!\nBefore we start, what is your name? ";
        playerName = my_getline();

        if (playerName == "-1") {
          exit(1);
        }

        while (isNameExist(playerName)) {
            cout << "\"" << playerName << "\"" << " has been used before.  Please give me another name: ";
            playerName = my_getline();
        }

        cout << "Nice to meet you, " << playerName << ".";
        cout << "\n\nPlease enter the gameboard size(6-20): ";

        size = 0;
        sizeString = my_getline();
        istringstream getFirstWord(sizeString);
        getFirstWord >> sizeStringTemp;
        stringstream toInt(sizeStringTemp);
        toInt >> size;

        while (size < 6 || size > 20) {
            cout << "\nThe size you entered is out of range!" << endl;
            cout << "Please enter the gameboard size(6-20): ";

            size = 0;
            sizeString = my_getline();
            istringstream getFirstWord(sizeString);
            getFirstWord >> sizeStringTemp;
            stringstream toInt(sizeStringTemp);
            toInt >> size;
        }
    }

    //init a game data
    void initpara(){
        maxshot = size * size;
        hit = "X.";
        miss = "M.";
        empty = "--";
    }

    //start a game
    void startgame(){
        getboardsize();
        initpara();
    }

    //check if the game exist
    bool isNameExist(string newPlayerName){
        string PlayerName = newPlayerName;
        newPlayerName += ".txt";
        ifstream fin;
        fin.open(newPlayerName.c_str());

        char bNewGame = 'X';

        if (fin.fail()){
            fin.close();
            return false;
        }else{
            fin.close();
        }
        while (bNewGame != 'Y' && bNewGame != 'N'){
            cout << PlayerName << ", you have saved a game before, start a new game anyway with same name (Y/N) ?" << endl;
            cin >> bNewGame;
            bNewGame = toupper(bNewGame);
        }

        if (bNewGame =='Y')
            return false;
        else{
            return true;
        }

    }


  //function of resume data for a game object
    void ResumeData(int reSize, string rePlayerName){
        size = reSize;
        maxshot = reSize * reSize;
        playerName = rePlayerName;
        hit = "X.";
        miss = "M.";
        empty = "--";
    }
};


// data structure to keep players' game data
//    - total shot counts
//    - total hit ship target counts
//    - total missed shots
//    - update shot status of the battleship grid
struct gamedata{

    struct ship{
        string name;
        string abbreviation;
        int size;
    };


    int userTotalShot, userHitNum, userMissNum, compTotalShot, compHitNum, compMissNum;


    // added by Karen on 20/11/2020 to show the game status (ShowGridWithComp)
    string userLsAttackStatus, compLsAttackStatus;

    //dynamic sized array for storing the ship and shot history for player and computer
    ship* shipArray;
    string* userGrid, *compGrid, *showedCompGrid;
    int* userShotHist, *compShotHist;

    // initialize the user grid value with empty constant
    void CreateArray(game g){
        shipArray = new ship[MAXSHIP];
        userShotHist = new int[g.maxshot];
        compShotHist = new int[g.maxshot];
        userGrid = new string[g.size * g.size];
        compGrid = new string[g.size * g.size];
        showedCompGrid = new string[g.size * g.size];
    }

    void InitGrid(game g){
        userTotalShot = userHitNum = userMissNum = compTotalShot = compHitNum = compMissNum = 0;

        //array to store the size and class of the ship.
        shipArray[4].name = "Patrol Boat";
        shipArray[4].size = 2;
        shipArray[4].abbreviation = "P.";

        shipArray[3].name = "Destroyer";
        shipArray[3].size = 3;
        shipArray[3].abbreviation = "D.";

        shipArray[2].name = "Submarine";
        shipArray[2].size = 3;
        shipArray[2].abbreviation = "S.";

        shipArray[1].name = "Battleship";
        shipArray[1].size = 4;
        shipArray[1].abbreviation = "B.";

        shipArray[0].name = "Carrier";
        shipArray[0].size = 5;
        shipArray[0].abbreviation = "C.";

        //put "--" into the grid and compGrid
        //init all the element of shotHist to -99 that means empty
        for (int i = 0; i < g.maxshot; i++) {
            userGrid[i] = compGrid[i] = showedCompGrid[i] = g.empty;
            userShotHist[i] = compShotHist[i] = -99;
        }

    }



    // added by Karen on 20/11/2020 to show the game status (ShowGridWithComp)
    void ShowGameStatus(game g){

        string compstatus = "", userstatus = "";

        if (compLsAttackStatus == g.hit)
            compstatus = "Hit";
        else if (compLsAttackStatus == g.miss)
            compstatus = "Miss";
        else
            compstatus = "---";


        compstatus = string(6- compstatus.length(), ' ') + compstatus;

        if (userLsAttackStatus == g.hit)
            userstatus = "Hit";
        else if (userLsAttackStatus == g.miss)
            userstatus = "Miss" ;
        else
            userstatus = "---";

        userstatus = string(7-userstatus.length(), ' ') + userstatus;

        cout << endl << endl;
        cout << "Game Status: " << endl;
        cout << "------------" << endl;
        cout << setw(28) << "Computer" << setw(16) << "Player" << endl;

        // this variable is not corret, please clarify the total target number.
        cout << "Total Target:" << setw(12) << ALLPOINT << setw(17) << ALLPOINT << endl;


        cout << "Target hit:" << setw(14) << compHitNum << setw(17) << userHitNum << endl;
        cout << "Target missed:" << setw(11) << compMissNum << setw(17) << userMissNum << endl;

        if((compstatus == "Miss") && (userstatus == "Miss"))
        {
            cout << "Last Attack:" << setw(14) << compstatus << setw(17) << userstatus << endl;
        }
        else
        {
            cout << "Last Attack:" << setw(14) << compstatus << setw(17) << userstatus << endl;
        }
    }

    //show the grid for both player and computer
    void ShowGridWithComp(game g, string* userGrid, string* compGrid){

        cout << "\nOcean Grid:";

        for (int i = 0; i < (g.size * 2) + g.size - 1; i++) {
          cout << " ";
        }
        cout << "\t\t     Tracking Grid:";

        cout << "\n" << "\t  ";

        //print header for user grid (00, 01, 02, ...)
        for (int k = 0; k < g.size; k++){
            if (k < 10)
                cout << " " << "0" << k;
            else
                cout << " " << k;
        }

        cout << "\t\t\t\t   ";

        //print header for computer grid (00, 01, 02, ...)
        for (int k = 0; k < g.size; k++){
            if (k < 10)
                cout << "0" << k << " ";
            else
                cout << k << " ";
        }
        cout << endl;

        for (int i = 0; i < g.size; i++) {
            cout << "\t";
            if (i < 10)
                cout << "0" << i;
            else
                cout << i;

            //print the user grid with ship's abbreviation
            for (int j = 0; j < g.size; j++) {
                cout << " " << userGrid[i * g.size + j];

                if (j == g.size - 1) {
                    cout << "\t\t\t\t";

                    if (i < 10)
                        cout << "0" << i;
                    else
                        cout << i;
                    //print the computer grid with no ship's abbreviation
                    for (int k = 0; k < g.size; k++)
                        cout << " " << compGrid[i * g.size + k];
                }
            }
            cout << endl;
        }

        ShowGameStatus(g);

    };

    void ShowGrid(game g, string* grid){
        //print header

        cout << endl << "\t   ";
        for (int k = 0; k < g.size; k++){
            if (k < 10)
                cout << "0" << k << " ";
            else
                cout << k << " ";
        }
        cout << endl;

        //print grid squares
        for (int i = 0; i < g.size; i++){
            cout << "\t";
            if (i < 10)
                cout << "0" << i;
            else
                cout << i;

            for (int j = 0; j < g.size ; j++)
                cout << " " << grid[i * g.size + j];

            cout << endl;
        }
    }


    // check if the ship placement already existed.
    bool IsDupShip(int xpos, int ypos, int shipSize,  string orientation, game g){
        if (orientation == "v") {
            if (ypos + shipSize - 1 <= g.size - 1){

                for (int i = 0; i < shipSize; i++) {
                    if (userGrid[(ypos + i) * g.size + xpos] != "--") {
                        cout << "\nThe ship coordination already existed, please enter again!" << endl;
                        return true;
                    }
                }
                return false;
            }else{
                cout << "\nit is not enough grid point to place. Please try again." << endl;
                return true;
            }
        }else{
            if (xpos + shipSize - 1 <= g.size - 1) {

                for (int i = 0; i < shipSize; i++) {
                    if (userGrid[ypos * g.size + xpos + i] != "--") {
                        cout << "\nThe ship coordination already existed, please enter again!" << endl;
                        return true;
                    }
                }
                return false;
            }else{
                cout << "\nit is not enough grid point to place. Please try again." << endl;
                return true;
            }
        }
    }


    //ask player the position they want the 5 ships place in horizontally or vertically.
    void PlaceShip(game g){
        int xpos = 0, ypos = 0, maxcoord = g.size -1;
        string orientation, orientationLine;
        string xypos, pos;

        cout << "\nYou have to place 5 ships (Patrol Boat, Destroyer, Submarine, Battleship and Carrie) on the grid\n";

        for (int i = 0; i < MAXSHIP; i++) {
            while (1) {
                cout << "\nPlease enter the ship (" << shipArray[i].name << ")'s coordination which is sized of " << shipArray[i].size << ", X & Y: " << endl;

                //get line input by player whatever they enter is work, BY Horace
                //no any enter, it means x = 0, y = 0;
                //if player enter 01 XXX, then x = 1, y = 0 and vice versa
                xypos = my_getline();
                istringstream xystring(xypos);

                for (int i = 0; i < 2; i++) {
                    xystring >> pos;
                    stringstream toInt(pos);

                    if (i == 0)
                        toInt >> xpos;
                    else
                        toInt >> ypos;
                }

                if (xpos < 0 || xpos > maxcoord || ypos < 0 || ypos > maxcoord)
                    cout << "\nThe X, Y you entered is out of range!" << endl;
                else{
                    do{
                        cout << "\nX = " << xpos << " Y = " << ypos << ", Please select the orientation (h - horizontal, v - vertical): " << endl;
                        orientationLine = my_getline();
                        istringstream getFirstWord(orientationLine);
                        getFirstWord >> orientation;

                    }while( !(orientation == "h" || orientation == "v") );

                    if (IsDupShip(xpos, ypos, shipArray[i].size, orientation, g) == false) {
                        if (orientation == "v") {
                            for (int j = 0; j < shipArray[i].size; j++)
                                userGrid[(ypos + j) * g.size + xpos] = shipArray[i].abbreviation;
                        }else{
                            for (int j = 0; j < shipArray[i].size; j++)
                                userGrid[ypos * g.size + xpos + j] = shipArray[i].abbreviation;
                        }
                        break;
                    }
                }
            }
            ShowGrid(g, userGrid);
        }
        cout << "\nYou have placed all ships on the grid and wait Computer place it as well.";
        cout << "\n\nNow, waiting for computer's turn.\n\n";
    }

    // For computer side, check if the ship placement already existed at the computer grid.
    bool IsDupShipForComp(int randPoint,int shipSize, int orientation, game g){
        if (orientation == 1) {
            if ( (randPoint / g.size) + shipSize - 1 <= g.size - 1) {
                for (int i = 0; i < shipSize; i++) {
                    if (compGrid[randPoint] != "--")
                        return true;

                    randPoint += g.size;
                }
                return false;
            }else
                return true;
        }else{
            if ( (randPoint % g.size) + shipSize - 1 <= g.size - 1) {
                for (int i = 0; i < shipSize; i++) {
                    if (compGrid[randPoint] != "--")
                        return true;

                    randPoint++;
                }
                return false;
            }else
                return true;
        }
    }

    // computer place 5 ships by itself
    void CompPlaceShip(game g){
        int numShip = 0, randGridPoint, orientation, shipSize, temp;

        while (numShip < MAXSHIP) {
            shipSize = shipArray[numShip].size;
            srand( (unsigned int)time(0) );
            temp = rand();
            srand(temp);

            //To get a random grid point an the orientation for computer to place the ship.
            //For orientation, 0 = horizontal, 1 = vertical.
            randGridPoint = (rand() % g.size) * g.size + (rand() % g.size);
            orientation = rand() % 2;

            // computer is going to place a ship on the grid with random point and orientation.
            // For each random point, it will try placing it in horizontally or vertically.
            for (int i = 0; i < 2; i++) {
                if (IsDupShipForComp(randGridPoint, shipSize, orientation, g) == false) {

                    if (orientation == 1) {
                        for (int i = 0; i < shipSize; i++)
                            compGrid[randGridPoint + i * g.size] = shipArray[numShip].abbreviation;
                    }else{
                        for (int i = 0; i < shipSize; i++)
                        compGrid[randGridPoint + i] = shipArray[numShip].abbreviation;
                    }
                    cout << numShip + 1 << "'s ship has been placed."<< endl;
                    numShip++;
                    break;
                }else
                    orientation = !orientation;
            }
        }
        cout << "\nComputer have placed all ship.\nGame starts now !\n";
    };

    //check if the x, y enterd by player hit before
    bool IsAttackBefore(int point, int* shotHist, int maxShot){
        for (int i = 0; i < maxShot; i++) {
            if (point == shotHist[i])
                return true;
        }
        return false;
    }

    //check if the player hit the target with the computer grid
    bool IsHit(int point, string* grid){
        if (grid[point] == "--" || grid[point] == "M." || grid[point] == "X.")
            return false;
        else
            return true;
    }

    void Attack(game g){
        // accept user x & y coordinate
        // update grid board according to x, y coordination
        // show message to user wheather it is hit or missed
        int xpos = 0, ypos = 0, maxcoord = g.size -1, randPoint, temp;
        //int rnd;
        string xypos, pos;

        while (1) {

            //ask player to enter the coordinates he want to attack
            //enter -1 backing to menu or -2 saving and exiting
            cout << "\nEnter -1 back to menu or -2 save and exit.\nPlease enter coordinates that you want to attack, X & Y: " << endl;

            //add by Horace, it same as the above.
            xypos = my_getline();
            istringstream xystring(xypos);

            for (int i = 0; i < 2; i++) {
                xystring >> pos;
                stringstream toInt(pos);

                if (i == 0)
                    toInt >> xpos;
                else
                    toInt >> ypos;
            }

            if (xpos == -1){
                break;
            }else if (xpos == -2){
                cout << "Remember using \"" << g.playerName << "\" to resume your game.\n";
                Save(g);
                break;
            }


            if (xpos < -2 || xpos > maxcoord || ypos < 0 || ypos > maxcoord)
                cout << "\nThe X, Y you entered is out of range!" << endl;
            else{
                if (IsAttackBefore(ypos * g.size + xpos, userShotHist, userTotalShot) == true)
                    cout << "\nThe coordinates of X = " << xpos << ", Y = " << ypos << " have been attacked before.\n";
                else{
                    //player's turn
                    userShotHist[userTotalShot] = ypos * g.size + xpos;
                    if (IsHit(ypos * g.size + xpos, compGrid) == true) {
                        userHitNum++;
                        // added by Karen on 20/11/2020 to keep last attack status
                        userLsAttackStatus = g.hit;
                        showedCompGrid[ypos * g.size + xpos] = g.hit;
                    }else{
                        userMissNum++;
                        // added by Karen on 20/11/2020 to keep last attack status
                        userLsAttackStatus = g.miss;
                        showedCompGrid[ypos * g.size + xpos] = g.miss;
                    }

                    //if player attack all point, then quit.
                    if (IsGameOver(userHitNum) == true && userTotalShot >= ALLPOINT) {
                        ShowGridWithComp(g, userGrid, showedCompGrid);
                        userTotalShot++;
                        cout << "\nYou won !!\n";
                        Save(g);
                        break;
                    }else{
                        //computer's turn
                        cout << "\nPlease give some time for this computer...";
                        do {
                            //computer select a random grid point and check if it attack before
                            srand( (unsigned int)time(0) );
                            temp = rand();
                            srand(temp);

                            //Horace random
                            randPoint = (rand() % g.size) * g.size + (rand() % g.size);

                            // changed the random generation to improve performance (by Karen on 20/11/2020)
                            //rnd = rand() % (g.size*g.size);

                            //randPoint = (rnd % g.size) * g.size + (rnd / g.size);

                        } while (IsAttackBefore(randPoint, compShotHist, compTotalShot) == true);

                        compShotHist[compTotalShot] = randPoint;
                        if (IsHit(randPoint, userGrid) == true) {
                            compHitNum++;
                            // added by Karen on 20/11/2020 to keep last attack status
                            compLsAttackStatus = g.hit;
                            userGrid[randPoint] = g.hit;
                        }else{
                            compMissNum++;
                            // added by Karen on 20/11/2020 to keep last attack status
                            compLsAttackStatus = g.miss;
                            userGrid[randPoint] = g.miss;
                        }

                        if (IsGameOver(compHitNum) == true && compTotalShot >= ALLPOINT) {
                            ShowGridWithComp(g, userGrid, showedCompGrid);
                            compTotalShot++;
                            cout << "\nYou lost.\n";
                            Save(g);
                            break;
                        }
                        cout << "\nComputer: ok, your turn !\n";
                    }
                    userTotalShot++;
                    compTotalShot++;
                    ShowGridWithComp(g, userGrid, showedCompGrid);
                }
            }
        }
    }

    //check the game is over
    bool IsGameOver(int hitNum){
        if (hitNum == ALLPOINT)
            return true;
        else
            return false;
    }


    //the function of save after the game is over or the player enter -2 to save and exit
    //using file i/o, creating a save, which is a .txt file, and use the player's name as the file name
    //write all the important game data to this .txt file and save it.
    void Save(game g){

        string saveName = g.playerName + ".txt";
        ofstream out;
        out.open(saveName.c_str());

        out << g.playerName << "\n" << g.size << "\n";

        for (int i = 0; i < g.maxshot - 1; i++) {
          out << userGrid[i] << " ";
        }
        out << userGrid[g.maxshot - 1] << "\n";

        for (int i = 0; i < g.maxshot - 1; i++) {
          out << compGrid[i] << " ";
        }
        out << compGrid[g.maxshot - 1] << "\n";

        for (int i = 0; i < g.maxshot - 1; i++) {
          out << showedCompGrid[i] << " ";
        }
        out << showedCompGrid[g.maxshot - 1] << "\n";

        for (int i = 0; i < g.maxshot - 1; i++) {
          out << userShotHist[i] << " ";
        }
        out << userShotHist[g.maxshot - 1] << "\n";

        for (int i = 0; i < g.maxshot - 1; i++) {
          out << compShotHist[i] << " ";
        }
        out << compShotHist[g.maxshot - 1] << "\n";

        out << userTotalShot << "\n" << userHitNum << "\n" << userMissNum << "\n" << compTotalShot << "\n" << compHitNum << "\n" << compMissNum << "\n" << userLsAttackStatus << "\n" << compLsAttackStatus;

        out.close();
    }

    //It is the function of the program flow for a new game
    //That create and init a grid array for player and compter
    //ask player for placing the 5 types ships
    //and the computer will place it ships automatically
    //Then, show the grid to player
    //Finally, prompt player to attack
    void CreateGameData(game g){
        CreateArray(g);
        InitGrid(g);
        ShowGrid(g, userGrid);
        PlaceShip(g);
        CompPlaceShip(g);
        ShowGridWithComp(g, userGrid, showedCompGrid);
        Attack(g);
    }

    //function of asking player to attack after resuming the game
    void resumeGameStat(game g){
        ShowGridWithComp(g, userGrid, showedCompGrid);
        Attack(g);
    }

    //show the grid and game status to player when they reume a game that is over.
    void resumeGameOver(game g){
        ShowGridWithComp(g, userGrid, showedCompGrid);
    }

    //function of resume game status
    //It is the last attack status for both player and computer
    void resumeAttackStatus(string userLs, string compLs){
        userLsAttackStatus = userLs;
        compLsAttackStatus = compLs;
    }

    //function of resume game status like the number of hit and miss.
    void resumeShotStatus(int uTotal, int uHit, int uMiss, int cTotal, int cHit, int cMiss){
        userTotalShot = uTotal;
        userHitNum = uHit;
        userMissNum = uMiss;
        compTotalShot = cTotal;
        compHitNum = cHit;
        compMissNum = cMiss;
    }

    //function of putting the shoting history from .txt to the array of shot history for player and Computer
    //It is for resume game
    void resumeShotHist(string userSH, string compSH, int size){
        int u = 0 , c = 0;
        string tempShot;
        userShotHist = new int[size * size];
        compShotHist = new int[size * size];

        istringstream userHist(userSH);
        istringstream compHist(compSH);

       while (userHist >> tempShot) {
           userShotHist[u] = stoi(tempShot);
           u++;
       }

       while (compHist >> tempShot) {
           compShotHist[c] = stoi(tempShot);
           c++;
       }
    }

    //function of putting all grid point from the .txt to the grid of player and computer
    //And these grid will show to player in each attack
    //It is for resume game
    void resumeGrid(string uGrid, string cGrid, string showedCGrid, int size){

        int u = 0, c = 0, s = 0;
        string tempPoint;
        userGrid = new string[size * size];
        compGrid = new string[size * size];
        showedCompGrid = new string[size * size];

        istringstream uG(uGrid);
        istringstream cG(cGrid);
        istringstream scG(showedCGrid);

        while (uG >> tempPoint) {
            userGrid[u] = tempPoint;
            u++;
        }

        while (cG >> tempPoint) {
            compGrid[c] = tempPoint;
            c++;
        }

        while (scG >> tempPoint) {
            showedCompGrid[s] = tempPoint;
            s++;
        }
    }

    //function of destroying the array of grid and shot history (game data)
    void DestroyGameData(){
      delete [] shipArray;
      delete [] userShotHist;
      delete [] compShotHist;
      delete [] userGrid;
      delete [] compGrid;
      delete [] showedCompGrid;
    }
};

void NewGame(){
    // start game and init the necessary parameters
    game mygame;
    mygame.startgame();
    gamedata playerdata;

    //start create the game data and playing the game
    playerdata.CreateGameData(mygame);
    //destroy the dynamic memory when the game is over
    playerdata.DestroyGameData();
}

//using File I/O library, get the important game data from the .txt file like game size, player name, the grid of player and computer
//Also, get the game status like the shoting history of player and computer.
void ResumeGameData(string saveName){
    string playerName, Size, userGrid, compGrid, showedCompGrid, userShotHist, compShotHist, userTotalShot, userHitNum, userMissNum, compTotalShot, compHitNum, compMissNum, userLsAttackStatus, compLsAttackStatus;
    int reSize, reUserTotalShot, reUserHitNum, reUserMissNum, reCompTotalShot, reCompHitNum, reCompMissNum;

    //create a game object
    game resume;

    ifstream fin;
    fin.open(saveName.c_str());

    //get each line in the .txt file
    getline(fin, playerName);
    getline(fin, Size);

    getline(fin, userGrid);
    getline(fin, compGrid);
    getline(fin, showedCompGrid);
    getline(fin, userShotHist);
    getline(fin, compShotHist);

    getline(fin, userTotalShot);
    getline(fin, userHitNum);
    getline(fin, userMissNum);
    getline(fin, compTotalShot);
    getline(fin, compHitNum);
    getline(fin, compMissNum);

    getline(fin, userLsAttackStatus);
    getline(fin, compLsAttackStatus);

    fin.close();

    //make the game data (string) to integer
    reSize = stoi(Size);
    reUserTotalShot = stoi(userTotalShot);
    reUserHitNum = stoi(userHitNum);
    reUserMissNum = stoi(userMissNum);
    reCompTotalShot = stoi(compTotalShot);
    reCompHitNum = stoi(compHitNum);
    reCompMissNum = stoi(compMissNum);

    //pass all the game data to gamedata object and ready for resume game.
    resume.ResumeData(reSize, playerName);

    gamedata resumePlayerData;

    resumePlayerData.resumeShotStatus(reUserTotalShot, reUserHitNum, reUserMissNum, reCompTotalShot, reCompHitNum, reCompMissNum);

    resumePlayerData.resumeAttackStatus(userLsAttackStatus, compLsAttackStatus);

    resumePlayerData.resumeShotHist(userShotHist, compShotHist, reSize);

    resumePlayerData.resumeGrid(userGrid, compGrid, showedCompGrid, reSize);


    //if the number of Hit (one of the gama data) of player or computer is 17
    //that mean the game is over.
    //and player cannot resume this save again to play
    //it will show the information to player and told them the result.
    //it also show the grid that last seen before.
    if (reUserHitNum == 17) {
      resumePlayerData.resumeGameOver(resume);
      cout << "\nThe game is over.\nYou won !!\nPress any key to exit...";
      getchar();
    }else if (reCompHitNum == 17){
      resumePlayerData.resumeGameOver(resume);
      cout << "\nThe game is over.\nYou lost.\nPress any key to exit...";
      getchar();
    }else{
        resumePlayerData.resumeGameStat(resume);
    }
}

//check the saved name exist in the folder
bool isExist(string saveName){
    ifstream fin;
    fin.open(saveName.c_str());

    if (fin.fail()){
        fin.close();
        return false;
    }else{
        fin.close();
        return true;
    }
}

//function of asking the saved name from player for resuming game
void ResumeGame(){
    cout << "Please enter your saving name(press -1 back to menu) " << setw(0) <<"> ";
    string saveName = my_getline();

    if (saveName == "-1") {

    }else{
        string passSaveName = saveName + ".txt";

        if (isExist(passSaveName) == false) {
            cout << "The saving called \"" + saveName + "\" does not exist." << endl;
            ResumeGame();
        }else{
            //start to resume
            ResumeGameData(passSaveName);
        }
    }
}

int main() {

    //program starts from menu and ask player choose number 1 to 4.
    //1: start a new game
    //2: resume the game save, but the player needs enter the saved name
    //3: print tutorial
    //4: quit program
    char gameStatus = MenuCmd();

    while (gameStatus == '1' || gameStatus ==  '2' || gameStatus == '3') {

        if (gameStatus == '1') {
            NewGame();
        }else if (gameStatus == '2'){
            ResumeGame();
        }else if (gameStatus == '3'){
            PrintTutorial();
        }

        gameStatus = MenuCmd();
    }

    return 0;
}
