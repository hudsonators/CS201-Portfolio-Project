#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"		//using Dr Lusth's header file for scanner functions
#include "scanner.c"		//using Dr Lusth's c file for scanner functions

/*
*	Hudson Nicholson
*	CS 201 - Dr Monica Anderson Herzog
*	The University of Alabama 
* 	
*	This project is for the spring 2019 CS 201 class at the University of Alabama.
* 	The program is a 'connect four' game where the player chooses the board size.
*	The player is also able to change how many players can play at once along with
*	some more options that can be explored under the settings menu. Along with that,
*	there is an option to play solo against the AI. 
*	
*	Scanner functions were provided by Dr Lusth of the UA CS department. 
*	scanner.c and scanner.h can be found at:  
*	troll.cs.ua.edu/ACP-C/scanner.h
*	troll.cs.ua.edu/ACP-C/scanner.c 
*/

void PrintBlankSpace(int);
void PrintBoard(char *, int, int);
void ResetBoard(char *, int, int);
int TakeTurnPlayer(char *, int, int, int, int, char *, int);
int TakeTurnAI(char *, int, int, int, int, char *, int, int);
int DFScheck(char *, int, int, int, char, int);
int WinCondition(char *, int, int, int, char, int, char *);
int SymbolToPlayerNum(char, char *);
void printRules();
void ReturnToMenuPrompt();
void choosePlayerToken(char *, int);
void clearWinLoss(int *, int *, int *);
int askNumInRow(int);
int askNumPlayers(int);
int askAIdiff(int);
int AI(char *, int, int, int, char *, int, int);

int main(int argc, char *argv[]){
	int rows;	//number of rows chosen by user
	int cols;	//number of cols chosen by user
	
	//Enter screen is printed and the user is asked how many rows and columns they want
	//Thank you to http://patorjk.com/software/taag/ for the ascii to font generator!!!
	PrintBlankSpace(40);
	printf("  ______   ______   .__   __. .__   __.  _______   ______ .___________.              ___   ___ \n");
	printf(" /      | /  __  \\  |  \\ |  | |  \\ |  | |   ____| /      ||           |              \\  \\ /  / \n");
	printf("|  ,----'|  |  |  | |   \\|  | |   \\|  | |  |__   |  ,----'`---|  |----`    ______     \\  V  /  \n");
	printf("|  |     |  |  |  | |  . `  | |  . `  | |   __|  |  |         |  |        |______|     >   <   \n");
	printf("|  `----.|  `--'  | |  |\\   | |  |\\   | |  |____ |  `----.    |  |                    /  .  \\  \n");
	printf(" \\______| \\______/  |__| \\__| |__| \\__| |_______| \\______|    |__|                   /__/ \\__\\ \n");
	printf("\n");
	printf("Welcome to the Connect X game! It is like Connect Four BUT EXTREME!!! \n\n");
	printf("We suggest not going over a 20x20 size board, as it may appear incorrectly based on your window size. \n\n");
	printf("What size board would you like to play with?\n\n");
	while(1){
		printf("\n");
		printf("rows: ");
		rows = readInt(stdin);
		printf("coloumns: ");
		cols = readInt(stdin);
		printf("\n");
	
		if(rows>3 && cols>3){
			break;
		} else{
			PrintBlankSpace(30);
			printf("Please input a value for rows and cols that are both greater than or equal to 4. \n");
		}
	}
	/*
	*	The board is created using a 1D array that holds every index. This was done
	*	at first when I did not believe you could pass a 2D array to a function without
	*	knowing the size of the dimensions. Not wanting to use a global variable to do 
	*	that, I decided using a single array was best to represent the graph. Later on,
	*	I learned that one can create an array of pointers and pass that to a function 
	*	which is essentially a 2D array. At that time I had already worked out all the
	*	algebra for using the 1D array as a graph, so it was not benefitial for myself 
	*	to change the code from 1D to 2D at that point. If I were to re-do the code for 
	*	this project, that would be the main decision I would change. At this point however
	*	it would only help the readability of my code and does not affect the performance
	* 	a measureable amount. However, to aid anyone who would like to expand on my code I will 
	*	show how this 1D array functions as a graph.
	*
	*	The array is size N*M (N rows and M cols). We can use a 5x5 graph to show how 
	*	the indexes would be represented on the graph below. Each number is the index
	*	on the 1D array of the 5x5 graph.
	*
	*	0  1  2  3  4
	*	5  6  7  8  9
	*	10 11 12 13 14
	*	15 16 17 18 19
	*	20 21 22 23 24
	*
	*	Now we can look at the operations to determine the bounds as well as how to increment
	*	up, down, right, left, or diagonally on this 1D array graph. The number of rows
	*	and columns will be represented as 'rows' and 'cols' variables in this pseudo code
	* 	shown below.
	*
	*	Incrementing								Example using index = 12 from graph above
	*	-------------								-----------------------------------------
	*	right:      index = index + 1;				newIndex = 12 + 1 = 13
	*	left:       index = index - 1;				newIndex = 12 - 1 = 11
	*	up:         index = index - cols;			newIndex = 12 - 5 = 7
	*	down:       index = index + cols;			newIndex = 12 + 5 = 17
	*	diagonalNW: index = index - cols - 1;		newIndex = 12 - 5 - 1 = 6
	*	diagonalSW: index = index + cols - 1;		newIndex = 12 + 5 - 1 = 16
	*	diagonalNE: index = index - cols + 1;		newIndex = 12 - 5 + 1 = 8
	*	diagonalSE: index = index + cols + 1;		newIndex = 12 + 5 + 1 = 18
	*
	*	Bounds										Example of reaching bound from graph above
	*	-------------								------------------------------------------
	*	right edge:		(index+1)%cols == 0			index = 14     (14 + 1) % 5 == 0  
	*	left edge:		index%cols == 0				index = 10		10 % 5 == 0
	*	top edge:		index - cols < 0			index = 2		2 - 5 < 0
	*	bottom edge:	index + cols >= rows*cols	index = 22		22 + 5 > 5*5
	*
	*	With these operations available, one should be able to do nearly every function that a 
	*	2D array can do in very similar run times.
	*	
	*/
	char *board = NULL;
	board = (char *)malloc(rows * cols * sizeof(char));
	ResetBoard(board, rows, cols);
	
	int turnsTaken = 0;						
	int win = -1;							//win = 1 if player 1 is winner win = 2 if player 2 is winner
	int userWantsToPlay = 1;				//this variable keeps the most outter while loop going as long as the user wants to continue playing
	int inputTemp = -1;
	int userInSettings = 0;
	int inputTemp2 = -1;
	int winPerPlayer[12];					//next 3 functions are score keeping
	int lossPerPlayer[12];					//index 10 for all of these will be the AI's index
	int tiesPerPlayer[12];					
	char symbolForPlayer[12];				//array to hold and access the tokens for each player
	int aiDiff = 10; 						//start AI at hard difficulty
	int i;
	for(i=0; i<12; i++){
		winPerPlayer[i] = 0;
		lossPerPlayer[i] = 0;
		tiesPerPlayer[i] = 0;
		if(i == 0){
			symbolForPlayer[i] = 'O';		//sets tokens to specific starting values
		} else if(i == 1){
			symbolForPlayer[i] = 'X';
		} else if(i == 10){
			symbolForPlayer[i] = 'C';		//C for computer
		} else if(i == 11){
			symbolForPlayer[i] = 'E';		//E for computer easy
		} else if(i == 2){
			symbolForPlayer[i] = '3';
		} else if(i == 3){
			symbolForPlayer[i] = '4';
		} else if(i == 4){
			symbolForPlayer[i] = '5';
		} else if(i == 5){
			symbolForPlayer[i] = '6';
		} else if(i == 6){
			symbolForPlayer[i] = '7';
		} else if(i == 7){
			symbolForPlayer[i] = '8';
		} else if(i == 8){
			symbolForPlayer[i] = '9';
		} else if(i == 9){
			symbolForPlayer[i] = '0';
		} else {
			symbolForPlayer[i] = '?';
		} 
	}
	int numInRow = 4; 						//number of pieces in a row in order for win condition
	int numPlayers = 2;						//number of players playing the game
	while(userWantsToPlay == 1){
		PrintBlankSpace(40);
		printf("         MAIN MENU \n");
		printf("--------------------------- \n");
		printf(" 1 - PLAY AGAINST COMPUTER \n");
		printf(" 2 - PLAY LOCAL MULTIPLAYER \n");
		printf(" 3 - STATS \n");
		printf(" 4 - SETTINGS \n");
		printf(" 5 - RULES \n");
		printf(" 9 - EXIT GAME \n \n");
		printf("Enter your choice: ");
		inputTemp = readInt(stdin);
		switch(inputTemp){
			//refer to the above print statements to learn what each case does
			case 1:
				win = -1;
				int challenger = -1;
				PrintBlankSpace(40);
				printf("Which player would like to challenge the computer? \nPlayer Number: ");
				while(1){				
					challenger = readInt(stdin);
					printf("\n");
					if(challenger<=numPlayers && challenger>0){ //checks to make sure the player challenging the computer is an active player
						break;
					} else {
						PrintBlankSpace(40);
						printf("Please input a player number that is currently active. \nPlayer Number: ");
					}
				}
				while(turnsTaken < rows*cols && win == -1 ){
					//this is where the entire match takes place
					if(turnsTaken % 2 == 0){
						win = TakeTurnPlayer(board, rows, cols, aiDiff, numInRow, symbolForPlayer, challenger-1);
					} else {
						win = TakeTurnPlayer(board, rows, cols, challenger-1, numInRow, symbolForPlayer, 0);
					}
					turnsTaken++; 
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				PrintBlankSpace(1);
				//the stats are then recorded
				//could have made this a function to clean the code up, but this is only done twice so I did not
				if(win == aiDiff){						//computer wins
					printf("WINNER is the COMPUTER \n");
					winPerPlayer[aiDiff]++;
					lossPerPlayer[challenger-1]++;
				} else if (win >= 0) {				//challenger wins
					printf("WINNER is the Player %d \n", win+1);
					winPerPlayer[challenger-1]++;
					lossPerPlayer[aiDiff]++;
				} else if (win == -1){
					printf("The match is a TIE \n");
					tiesPerPlayer[aiDiff]++;
					tiesPerPlayer[challenger-1]++;
				}
				ReturnToMenuPrompt();
				ResetBoard(board, rows, cols);
				turnsTaken = 0;				
				PrintBlankSpace(40);
				break;
			case 2:
				win = -1;
				while(turnsTaken < rows*cols && win == -1 ){
					//this is where the entire match takes place
					win = TakeTurnPlayer(board, rows, cols, turnsTaken%numPlayers, numInRow, symbolForPlayer, 0);
					turnsTaken++;
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				PrintBlankSpace(1);
				int b;
				//the stats are then recorded
				if(win == -1){
					printf("The match is a TIE \n");
					for(b = 0; b < numPlayers; b++){
						tiesPerPlayer[b]++;
					}
				} else {
					printf("WINNER is Player ");
					printf("%d", win+1);
					for(b = 0; b < numPlayers; b++){
						if(win == b){
							winPerPlayer[b]++;
						} else {
							lossPerPlayer[b]++;
						}
					}
				}	
				ReturnToMenuPrompt();
				ResetBoard(board, rows, cols);
				turnsTaken = 0;				
				PrintBlankSpace(40);
				//clean up the output a little more here and maybe show stats 
				break;
			case 3:
				PrintBlankSpace(40);
				printf("WINS/LOSSES/TIES/GP/WIN%% \n");
				int k = 0;
				float temp = 0;
				int tempInt = 0;
				for(k=0; k<numPlayers; k++){
					tempInt = winPerPlayer[k] + lossPerPlayer[k] + tiesPerPlayer[k];
					temp = (float)winPerPlayer[k]/tempInt;
					printf("Player %d with symbol %c : (%d WINS / %d LOSSES / %d TIES / %d GAMES PLAYED / %.2f WINNING %%)", k+1, symbolForPlayer[k], winPerPlayer[k], lossPerPlayer[k], tiesPerPlayer[k], tempInt, temp*100.0);
					printf("\n");
				}
				tempInt = winPerPlayer[10] + lossPerPlayer[10] + tiesPerPlayer[10];
				temp = (float)winPerPlayer[10]/tempInt;
				printf("Computer AI (hard) with symbol %c : (%d WINS / %d LOSSES / %d TIES / %d GAMES PLAYED / %.2f WINNING %%)", symbolForPlayer[10], winPerPlayer[10], lossPerPlayer[10], tiesPerPlayer[10], tempInt, temp*100.0);
				printf("\n");
				tempInt = winPerPlayer[11] + lossPerPlayer[11] + tiesPerPlayer[11];
				temp = (float)winPerPlayer[11]/tempInt;
				printf("Computer AI (easy) with symbol %c : (%d WINS / %d LOSSES / %d TIES / %d GAMES PLAYED / %.2f WINNING %%)", symbolForPlayer[11], winPerPlayer[11], lossPerPlayer[11], tiesPerPlayer[11], tempInt, temp*100.0);
				printf("\n");
				ReturnToMenuPrompt();
				break;
			case 4:
				userInSettings = 1;
				while (userInSettings == 1){
					PrintBlankSpace(40);
					printf("              SETTINGS \n");
					printf("------------------------------------- \n");
					printf(" 1 - Number of tokens in a row to win \n");
					printf(" 2 - Number of players \n");
					printf(" 3 - Choose player tokens \n");
					printf(" 4 - Clear win / loss record \n");
					printf(" 5 - Change AI difficulty \n");
					printf(" 9 - Return to MAIN MENU \n \n");
					printf("Enter your choice: ");
					inputTemp2 = readInt(stdin);
					switch(inputTemp2){
						//refer to settings options in print statements above for what each case # does
						case 1:
							numInRow = askNumInRow(numInRow);
							break;
						case 2:
							numPlayers = askNumPlayers(numPlayers);
							break;
						case 3:
							choosePlayerToken(symbolForPlayer, numPlayers);
							break;
						case 4:
							clearWinLoss(winPerPlayer, lossPerPlayer, tiesPerPlayer);
							break;
						case 5:
							aiDiff = askAIdiff(aiDiff);
							break;
						case 9:
							userInSettings = 0;
							break;
					}
				}
				break;
			case 5:
				PrintBlankSpace(40);
				printRules();
				ReturnToMenuPrompt();
				PrintBlankSpace(40);
				break;
			case 9:
				printf("See you next time! \n");
				userWantsToPlay = 0;
				break;
		}
	}
	free(board);
	return 0;
}

int AI(char board[], int rows, int cols, int winNum, char key[], int playerNum, int aiDiff){
		
	/*	
	*	The AI is simple but effective. It follows the three rules below.
	*	It checks rule 1, 2, then 3.
	*	The function returns the column in which the piece should be placed.
	*	
	*	1)if there is a move to win, make that move
	*	2)if there is a move the other player can win on, make that move
	*	3)otherwise, randomize it
	*
	*	ALSO, if aiDiff is equal to 11, then the ai is in easy mode
	*	Easy mode is just random inserts
	*/
	
	if(aiDiff == 11){
		//easy mode!!!!
		int i;
		while(1){
			i = rand()%cols;
			if(board[i] == '-'){
				return i;
			}
		}
	}
	
	//this is an array to tell whther each column is full or not
	int *arr = NULL;
	arr = (int *)malloc(cols* sizeof(int));
	
	int i;
	for(i = 0; i<cols; i++){
		if(board[i] == '-'){
			arr[i] = 1;
		} else {
			arr[i] = 0;
		}
	}
	int win = -1;
	int j;
	for(j= 0; j<cols; j++){
		if(arr[j] == 1){
			for(i = (rows*cols - (cols - j)); i >= j; i = (i-cols)){
				/*
				* This for loop starts at the bottom row of the column the user selected
				* the loop keeps going up the column until it finds an open spot
				*/
				if(board[i] == '-'){
					board[i] = key[10];		
					win = WinCondition(board, rows, cols, i, key[10], winNum, key);
					if(win > -1){
						board[i] = '-';
						return j;
					} else 
						board[i] = '-';
					break;
				}
			}
		}
	}
	win = -1;
	for(j= 0; j<cols; j++){
		if(arr[j] == 1){
			for(i = rows*cols - (cols-j); i >= j; i = i-cols){
				/*
				* This for loop starts at the bottom row of the column the user selected
				* the loop keeps going up the column until it finds an open spot
				*/
				
				if(board[i] == '-'){
					board[i] = key[playerNum];	
					win = WinCondition(board, rows, cols, i, key[playerNum], winNum, key); 
					if(win > -1){
						board[i] = '-';
						return j;
					} else 
						board[i] = '-';
					break;
				}
			}
		}
	}
	int k;
	while(1){
		k = rand()%cols;
		if(board[k] == '-'){
			return k;
		} 
	}
	free(arr);
}

int askNumInRow(int numInRow){
	int input;
	PrintBlankSpace(40);
	printf("WARNING: If you make this value too large relative to your board size,  \n");
	printf("every game will result in a tie. \n \n");
	printf("Currently a player must have %d tokens in a row to win \n\n", numInRow);
	printf("How many tokens would you like this value to be? (between 3 and 10) \n\n");
	input = readInt(stdin);
	printf("\n");
	if(input < 3 || input > 10 ){
		printf("Sorry, but that number is not between 3 and 10  \n\n");
		ReturnToMenuPrompt();
		return numInRow;
	}
	printf("One must now have %d tokens in a row to win \n", input);
	ReturnToMenuPrompt();
	return input;
}

int askNumPlayers(int numPlayers){
	//this prompts the user to choose how many players will be active
	int input;
	PrintBlankSpace(40);
	printf("Currently you have %d players active \n\n", numPlayers);
	printf("Note: You can always change this number later, and players you remove retain their stats \n\n");
	printf("How many players would you like to have in your game total? (between 2 and 10) \n\n");
	input = readInt(stdin);
	printf("\n");
	if(input < 2 || input > 10 ){
		printf("Sorry, but that number is not between 2 and 10  \n\n");
		ReturnToMenuPrompt();
		return numPlayers;
	}
	printf("The game will now be played with %d players \n", input);
	ReturnToMenuPrompt();
	return input;
}

void choosePlayerToken(char key[], int numPlayers){
	/*
	*	This prompts the user to change the token for a specific player. The user
	*	must input the player who wants their token to change. The user must then
	*	choose which character they want to use now.
	*/
	int input;
	char inputChar;
	PrintBlankSpace(40);
	printf("Which player's token would you like to change? \n");
	printf("Currently you can change players 1 - %d \n", numPlayers);
	input = readInt(stdin);
	printf("\n");
	if(input-1 < 0 || input-1 >= numPlayers ){	//error handling input value
		printf("Sorry, but that number is not between 1 - %d  \n", numPlayers);
		ReturnToMenuPrompt();
		return;
	}
	printf("WARNING: You cannot be the same character as another player or the AIs 'C' and 'E' \n\n");
	printf("What single character would player %d like to be represented by? \n", input);
	inputChar = readChar(stdin);
	printf("\n");
	int i;
	for(i = 0; i < 12; i++){		//error handling so no players have the same characters
		if(key[i] == inputChar || inputChar == '-' ){
			printf("Sorry, but that character is unavailable at the moment. Next time choose a \n");
			printf("character that is not a number value or in use by another player or AI ('C' and 'H') \n");
			ReturnToMenuPrompt();
			return;
		}
	}
	printf("Player %d now is represented by token ' %c ' \n", input, inputChar);
	printf("\n");
	key[input-1] = inputChar;
	ReturnToMenuPrompt();
}

void clearWinLoss(int win[], int loss[], int tie[]){
	//clears the board used for the game
	PrintBlankSpace(40);
	int i;
	for(i=0; i<12; i++){
		win[i] = 0;
		loss[i] = 0;
		tie[i] = 0;
	}
	printf("The record was cleared \n\n");
	printf("We won't tell anyone about all the losses you had... :) \n");
	ReturnToMenuPrompt();
}

int SymbolToPlayerNum(char symbol, char key[]){
	//this is just handy for finding the Player's Number given the symbol and the key[]
	int i;
	for(i = 0; i < 12; i++){
		if(symbol == key[i]){
			return i;
		}
	}
	printf("Error: symbol not found in SymbolToPlayerNum\n");
	return -1;
}

int DFScheck(char board[], int index, int cols, int rows, char symbol, int direction){
	/*
	*	This is a single direction DFS that returns how many of the input symbol are in a 
	*	specific direction. 
	*	The direction is chosen by the direction variable with the key shown below.
	*	0 = left ; 1 = right ; 2 = down ; 3 = NW ; 4 = SE ; 5 = NE ; 6 = SW
	*/
	
	int nextIndex = -1;
	//These are the ending conditions for each of the directions given the graph format used for this project

	if (direction == 6){
		if(index + cols - 1 >= rows*cols || index%cols == 0){ //this if statement checks for the bounds of each search	
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols-1; 							//this statement sets the next index to be the next token in the direction used
	}
	if (direction == 5){
		if(index - cols + 1 < 0 || (index+1)%cols == 0){	
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index-cols+1;
	}
	if (direction == 4){
		if( index + cols + 1 >= (rows*cols) || (index+1)%cols == 0){
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols+1;
	}
	if (direction == 3){
		if(index - cols - 1 < 0 || index%cols == 0){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index-cols-1;
	}
	if (direction == 2){
		if(index + cols >= rows*cols){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols;
	}
	if (direction == 1){
		if((index+1)%cols == 0){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index + 1;
	}
	if (direction == 0){
		if(index%cols == 0){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index - 1;
	}
	if(board[index] == symbol){
		return 1 + DFScheck(board, nextIndex, cols, rows, symbol, direction);	//if the piece is not on the edge and matches, then reccur
	} else{
		return 0;								
	}
}

int WinCondition(char board[], int rows, int cols, int indexToCheck, char symbol, int winNum, char key[]){
	/*
	* This function looks at the recently inserted piece then analyzes
	* the other spots to the left and right of it to determine if there
	* was a horizontal win condition. If the win condition is met, then
	* the function returns a 1. This is also done for the other three 
	* winning directions, vertical, diagonal NW to SE, and diagonal 
	* NE to SW. This calls the DFScheck function in order to get these values.
	*/
	
	//winNum is the number of pieces needed to be in a row for a winning condition
	int totalHoriz, totalVert, totalNWtoSE, totalNEtoSW;
	totalHoriz = DFScheck(board, indexToCheck, cols, rows, symbol, 0) + DFScheck(board, indexToCheck, cols, rows, symbol, 1) - 1;
	//one must be subracted due to checking both the left and right while both will return at least 1 for the base case
	totalVert = DFScheck(board, indexToCheck, cols, rows, symbol, 2);		//we only need to check the down direction here because there will never be an upwards piece 
	totalNWtoSE = DFScheck(board, indexToCheck, cols, rows, symbol, 3) + DFScheck(board, indexToCheck, cols, rows, symbol, 4) - 1;
	totalNEtoSW = DFScheck(board, indexToCheck, cols, rows, symbol, 5) + DFScheck(board, indexToCheck, cols, rows, symbol, 6) - 1;
	if(totalVert >= winNum || totalHoriz >=winNum || totalNWtoSE >=winNum || totalNEtoSW >=winNum){
		return SymbolToPlayerNum(symbol, key);		//returns the player who won's playerNum
	}
	
	return -1;
}

int TakeTurnPlayer(char board[], int rows, int cols, int playerNum, int winNum, char key[], int auxillaryPlayerNum){
	/*
	*	This function determines whether the player is a computer or human player by the playerNum
	*	variable. It then prompts the user for input or calls the AI function for input. The piece 
	*	for that column selected is then placed and dropped to the lowest open spot. The spot the
	*	token was dropped into is then put through the WinCondition function to see if the user placing
	* 	the piece has won the game.
	*/
	//auxillaryPlayerNum is the playerNum of the computer's opponent when this
	//if the computer is playing the player num is equal to 10 if hard mode AI and 11 if easy mode
	int input = -1;
	PrintBlankSpace(40);
	PrintBoard(board, rows, cols);
	if(playerNum == 10){		//This executes when the computer is playing hard mode
		input = AI(board, rows, cols, winNum, key, auxillaryPlayerNum, playerNum);
	} else if (playerNum == 11){		//This executes when the computer is playing easy mode
		input = AI(board, rows, cols, winNum, key, auxillaryPlayerNum, playerNum);
	} else {
		while (1){
			printf("Player %d: Choose what column to place your token. \n", playerNum+1);
			printf("Column: ");
			input = readInt(stdin);
		
			if(input >= 0 && input < cols && board[input] == '-'){
				break;
			} else {
				printf("Please input a column between 0 and %d that is not full \n", cols-1);
			}
		}
	}
	int i;
	for(i = rows*cols - (cols-input); i >= input; i = i-cols){
		/*
		* This for loop starts at the bottom row of the column the user selected
		* the loop keeps going up the column until it finds an open spot
		*/
		if(board[i] == '-'){
			board[i] = key[playerNum];
			return WinCondition(board, rows, cols, i, key[playerNum], winNum, key); 
		}
	}
	return -1;
}

void PrintBlankSpace(int num){
	/*	
	* This function prints 'num' lines of blank space
	* This is to be used for formatting purposes of the output
	*/
	int j;
	for(j = 0; j<num; j++){
		printf("\n");		
	}
}

void PrintBoard(char board[], int rows, int cols){
	//This function prints the board passed to the function
	int i;
	for(i = 0; i < rows*cols; i++){
		if(i%cols == 0 && i!=0){
			printf("|\n");
		}
		printf("|");
		printf(" %c ", board[i]);
	}
	printf("|\n");
	for(i = 0; i<cols; i++){
		printf("|");
		if(i<10){
			printf(" %d ", i);
		} else if(i<100){
			printf(" %d", i);
		} else 
			printf("%d", i);
	}
	printf("|\n");
}

void ResetBoard(char board[], int rows, int cols){
	//This function resets the board passed to the function
	int i;
	for(i = 0; i < rows * cols; i++){
		if(i % cols == 0){
			board[i] = '-';
		} else {
			board[i] = '-';
		}
	}
}

void printRules(){
	//This simply prints the rules
	printf("THE RULES ARE SIMPLE \n");
	printf("--------------------- \n");
	printf("When enetering a game, you choose which column that you want the token to be placed in. \n");
	printf("The token will slide down to the lowest open position in the column. The next player will \n");
	printf("then take their turn. This continues until the board is full or one player gets the correct \n");
	printf("number of tokens in a row. That row can be  horizontal, veritcal, or diagonal. Check out the \n");
	printf("settings option to see what all you, the user, can change to have some extra fun!!!. \n");
	printf("Most importantly: ");
	printf("HAVE FUN PLAYING!!! \n");
}

int askAIdiff(int aiDiff){
	//prompts the user for what the AIdiff they want
	int input;
	PrintBlankSpace(40);
	if(aiDiff == 10){
		printf("Currently you are playing on HARD difficulty \n\n");
	} else if (aiDiff == 11){
		printf("Currently you are playing on EASY difficulty \n\n");
	} else 
		return 10;
	
	printf("What difficulty would you like to play on? \n");
	printf("------------------------------------------ \n");
	printf(" 1 - HARD \n");
	printf(" 2 - EASY \n");
	input = readInt(stdin);
	printf("\n");
	if(input < 1 || input > 2 ){
		printf("Sorry, but that number is not 1 or 2  \n\n");
		ReturnToMenuPrompt();
		return aiDiff;
	}
	if(input == 1){
		printf("The difficulty is now HARD \n\n");
		ReturnToMenuPrompt();
		return 10;
	} else if (input == 2){
		printf("The difficulty is now EASY \n\n");
		ReturnToMenuPrompt();
		return 11;
	}
	return 10;
}

void ReturnToMenuPrompt(){
	//This is a simple function used a lot to prompt the user before returning them to a previous menu
	int inputTemp = -1;
	while(inputTemp != 1){
		printf("\n\nType '1' to return to previous menu \n\n");
		inputTemp = readInt(stdin);
	}
}
