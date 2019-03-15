#include <stdlib.h>
#include <stdio.h>

void PrintBlankSpace(int);
void PrintBoard(char *, int, int);
void ResetBoard(char *, int, int);
int TakeTurnPlayer(char *, int, int, int, int, char *);
int TakeTurnComputer(char *, int, int, int, int, char *);
int DFScheck(char *, int, int, int, char, int);
int WinCondition(char *, int, int, int, char, int, char *);
int SymbolToPlayerNum(char, char *);
void printRules();
void ReturnToMenuPrompt();
void choosePlayerToken(char *, int);
void clearWinLoss(int *, int *, int *);
int askNumInRow(int);
int askNumPlayers(int);
int AI(char *, int, int, int, char *);

/*

A 3,4, and 5 player mode can be made asily by making the modulo used with TakeTurnPlayer a variable of the number of users

the TakeTurnPlayer function must then simply add more if else statements using the playerTurn variables


-possibly add a 'settings' option where one could change their piece character or the number of pieces in a row needed to win

*/

int main(int argc, char *argv[]){
	int rows;
	int cols;
	
	PrintBlankSpace(40);
	printf("Welcome to the Connect X game! It is like Connect Four BUT EXTREME!!! \n");
	printf("what size board would you like to play with?\n");
	printf("We suggest not going over a 10x10 size board, as it may appear incorrectly based on your window size. ");
	printf("\n");
	printf("rows: ");
	scanf("%d", &rows);
	printf("coloumns: ");
	scanf("%d", &cols);
	printf("\n");
	
	if(0){
		//add error handling here for bad input sizes
	}
	
	char board[rows * cols];
	ResetBoard(board, rows, cols);
	int turnsTaken = 0;						
	int win = -1;							//win = 1 if player 1 is winner win = 2 if player 2 is winner
	int userWantsToPlay = 1;				//this variable keeps the most outter while loop going as long as the user wants to continue playing
	int inputTemp = -1;
	int userInSettings = 0;
	int inputTemp2 = -1;
	int winPerPlayer[11];					//index 11 for all of these will be the AI's index
	int lossPerPlayer[11];
	int tiesPerPlayer[11];
	char symbolForPlayer[11];
	int i;
	for(i=0; i<11; i++){
		winPerPlayer[i] = 0;
		lossPerPlayer[i] = 0;
		tiesPerPlayer[i] = 0;
		if(i == 0){
			symbolForPlayer[i] = 'O';
		} else if(i == 1){
			symbolForPlayer[i] = 'X';
		} else if(i == 10){
			symbolForPlayer[i] = 'C';		//C for computer
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
		printf("MAIN MENU \n");
		printf("--------------------- \n");
		printf("'1' - PLAY AGAINST COMPUTER \n");
		printf("'2' - PLAY LOCAL MULTIPLAYER \n");
		printf("'3' - STATS \n");
		printf("'4' - SETTINGS \n");
		printf("'8' - RULES \n");
		printf("'9' - EXIT GAME \n \n");
		printf("Enter your choice: ");
		scanf("%d", &inputTemp);
		switch(inputTemp){
			case 1:
				PrintBlankSpace(40);
				win = -1;
				int challenger = -1;
				printf("Which player would like to challenge the computer? \nPlayer Number: ");
				scanf("%d", &challenger);
				printf("\n");
				while(turnsTaken < rows*cols && win == -1 ){
					if(turnsTaken % 2 == 0){
						win = TakeTurnPlayer(board, rows, cols, challenger-1, numInRow, symbolForPlayer);
					} else {
						win = TakeTurnPlayer(board, rows, cols, 10, numInRow, symbolForPlayer);
					}
					turnsTaken++;
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				PrintBlankSpace(1);
				if(win == 10){						//computer wins
					printf("WINNER is the COMPUTER \n");
					winPerPlayer[10]++;
					lossPerPlayer[challenger-1]++;
				} else if (win >= 0) {				//challenger wins
					printf("WINNER is the Player %d \n", win+1);
					winPerPlayer[challenger-1]++;
					lossPerPlayer[10]++;
				} else if (win == -1){
					tiesPerPlayer[10]++;
					tiesPerPlayer[challenger-1]++;
				}
				
				ReturnToMenuPrompt();
				ResetBoard(board, rows, cols);
				turnsTaken = 0;				
				PrintBlankSpace(40);
				//clean up the output a little more here and maybe show stats 
				//change this show either the computer has its own special character and index for stats or its stats are kept elsewhere
				break;
			case 2:
				win = -1;
				while(turnsTaken < rows*cols && win == -1 ){
					win = TakeTurnPlayer(board, rows, cols, turnsTaken%numPlayers, numInRow, symbolForPlayer);
					turnsTaken++;
					//ADD TIE EVENT AND STAT TRACKING HERE
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				PrintBlankSpace(1);
				printf("WINNER is Player ");
				printf("%d", win+1);
				PrintBlankSpace(2);
				int b;
				if(win == -1){
					for(b = 0; b < numPlayers; b++){
						tiesPerPlayer[b]++;
					}
				} else {
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
				printf("Computer AI with symbol %c : (%d WINS / %d LOSSES / %d TIES / %d GAMES PLAYED / %.2f WINNING %%)", symbolForPlayer[10], winPerPlayer[10], lossPerPlayer[10], tiesPerPlayer[10], tempInt, temp*100.0);
				printf("\n");
				ReturnToMenuPrompt();
				break;
			case 4:
				userInSettings = 1;
				while (userInSettings == 1){
					PrintBlankSpace(40);
					printf("Settings Menu \n");
					printf("Here are your options \n");
					printf("--------------------- \n");
					printf("'1' - Number of tokens in a row to win \n");
					printf("'2' - Number of players \n");
					printf("'3' - Choose player tokens \n");
					printf("'4' - Clear win / loss record \n");
					printf("'8' -  \n");
					printf("'9' - MAIN MENU \n \n");
					printf("Enter your choice: ");
					scanf("%d", &inputTemp2);
					switch(inputTemp2){
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
						case 9:
							userInSettings = 0;
							break;
					}
				}
				break;
			case 5:
				break;
			case 8:
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
}

int AI(char board[], int rows, int cols, int winNum, char key[]){
	int i;
	i = rand()%cols;
	if(board[i] == '-'){
		return i;
	} else {
		return AI(board, rows, cols, winNum, key);
	}
}

int askNumInRow(int numInRow){
	int input;
	PrintBlankSpace(40);
	printf("WARNING: If you make this value too large relative to your board size,  \n");
	printf("every game will result in a tie. \n \n");
	printf("Currently a player must have %d tokens in a row to win \n", numInRow);
	printf("How many tokens would you like this value to be? (between 3 and 10) \n");
	scanf("%d", &input);
	printf("\n");
	if(input < 3 || input > 10 ){
		printf("Sorry, but that number is not between 3 and 10  \n");
		return numInRow;
	}
	printf("One must now have %d tokens in a row to win \n", input);
	ReturnToMenuPrompt();
	return input;
}

int askNumPlayers(int numPlayers){
	int input;
	PrintBlankSpace(40);
	printf("Currently you have %d players active \n", numPlayers);
	printf("How many players would you like to have in your game total? (between 2 and 10) \n");
	scanf("%d", &input);
	printf("\n");
	if(input < 2 || input > 10 ){
		printf("Sorry, but that number is not between 2 and 10  \n");
		return numPlayers;
	}
	printf("The game will now be played with %d players \n", input);
	ReturnToMenuPrompt();
	return input;
}

void choosePlayerToken(char key[], int numPlayers){
	int input;
	char inputChar;
	PrintBlankSpace(40);
	printf("Which player's token would you like to change? \n");
	printf("Currently you can change players 1 - %d \n", numPlayers);
	scanf("%d", &input);
	printf("\n");
	if(input-1 < 0 || input-1 >= numPlayers ){
		printf("Sorry, but that number is not between 1 - %d  \n", numPlayers);
		return;
	}
	printf("WARNING: You cannot be the same character as another player or the computer 'C' \n\n");
	printf("What single character would player %d like to be represented by? \n", input);
	scanf(" %c", &inputChar);
	printf("\n");
	int i;
	for(i = 0; i < 11; i++){
		if(key[i] == inputChar || inputChar == '-'){
			printf("Sorry, but that character is unavailable at the moment. Next time choose a \n");
			printf("character that is not a number value or in use by another player \n");
			ReturnToMenuPrompt();
			return;
		}
	}
	
	//add handling here to make sure that it is not the same piece as another player!!!
	//IF THIS IS NOT DONE, THE GAME WILL NOT PROCESS THE WIN CONDITION CORRECTLY
	printf("Player %d now is represented by token ' %c ' \n", input, inputChar);
	printf("\n");
	key[input-1] = inputChar;
	ReturnToMenuPrompt();
}

void clearWinLoss(int win[], int loss[], int tie[]){
	PrintBlankSpace(40);
	int i;
	for(i=0; i<11; i++){
		win[i] = 0;
		loss[i] = 0;
		tie[i] = 0;
	}
	printf("The record was cleared \n");
	ReturnToMenuPrompt();
}

int SymbolToPlayerNum(char symbol, char key[]){
	int i;
	for(i = 0; i < 11; i++){
		if(symbol == key[i]){
			return i;
		}
	}
}

int DFScheck(char board[], int index, int cols, int rows, char symbol, int direction){
	/*
	*	This is a single direction DFS that returns how many of the symbol are in a row. 
	*	The direction is chosen by the direction variable with the key shown below.
	*	0 = left ; 1 = right ; 2 = down ; 3 = NW ; 4 = SE ; 5 = NE ; 6 = SW
	*/
	printf("FLAG: DFS CHECK    ");
	printf("%c     ", symbol);
	printf("%d     %d", direction, index);
	printf("\n");
	int nextIndex = -1;
	//These are the ending conditions for each of the directions given the graph format used for this project
	
	if (direction == 6){
		if(index + cols - 1 > rows*cols && index%cols == 0){	//Have to check for hitting bottom of graph and left side		
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols-1; 
	}
	if (direction == 5){
		if(index - cols + 1 < 0 && (index+1)%cols == 0){		//Have to check for hitting top of graph and right side
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index-cols+1;
	}
	if (direction == 4){
		if(index + cols + 1 > rows*cols && (index+1)%cols == 0){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols+1;
	}
	if (direction == 3){
		if(index - cols - 1 < 0 && index%cols == 0){				
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
		return 1 + DFScheck(board, nextIndex, cols, rows, symbol, direction);	//piece to the SW matches then the reccursion continues
	} else{
		return 0;								//piece to the SW does not match then recurrsion ends
	}
}

int WinCondition(char board[], int rows, int cols, int indexToCheck, char symbol, int winNum, char key[]){
	/*
	* This function looks at the recently inserted piece then analyzes
	* the other spots to the left and right of it to determine if there
	* was a horizontal win condition. If the win condition is met, then
	* the function returns a 1. This is essentially a DFS of the graph
	*/
	
	//winNum is the number of pieces needed to be in a row for a winning condition
	int totalHoriz, totalVert, totalNWtoSE, totalNEtoSW, totalDiag;
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

int TakeTurnPlayer(char board[], int rows, int cols, int playerNum, int winNum, char key[]){
	int input = -1;
	int hold = 0;
	int hold2 = 0;
	PrintBlankSpace(40);
	PrintBoard(board, rows, cols);
	if(playerNum == 10){
		hold = 1;
		input = AI(board, rows, cols, winNum, key);
		//make the above statement a function that determines the next best move
	} 


	while (hold == 0){
		printf("Player 1: Choose what column to place your token. \n");
		printf("Column: ");
		scanf("%d", &input);
		if(input >= 0 && input < cols){
			hold = 1;
		} else {
			printf("Please input a value between 0 and %d \n", cols-1);
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
	/*	
	* This function prints the board passed to the function
	*/
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
	/*	
	* This function sets the board passed to the function to be completely empty
	*/
	board[rows * cols];
	int i;
	int temp;
	for(i = 0; i < rows * cols; i++){
		if(i % cols == 0){
			board[i] = '-';
		} else {
			board[i] = '-';
		}
	}
}

void printRules(){
	int temp = 0;
	printf("THE RULES ARE SIMPLE \n");
	printf("--------------------- \n");
	printf("When enetering a game, you choose which column that you want the token to be placed in. \n");
	printf("The token will slide down to the lowest open position in the column. The next player will \n");
	printf("then take their turn. This continues until the board is full or one player gets the correct \n");
	printf("number of tokens in a row. That row can be either horizontal, veritcal, or diagonal. The \n");
	printf("number of tokens needed in a row to win can be changed under the setting's main menu option. \n");
	printf("HAVE FUN PLAYING!!! \n");
}

void ReturnToMenuPrompt(){
	int inputTemp = -1;
	
	printf("\n\nType '1' to return to previous menu \n\n");
	inputTemp = -1;
	while(inputTemp != 1){
		scanf("%d", &inputTemp);
	}
}
