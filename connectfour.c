#include <stdlib.h>
#include <stdio.h>

void PrintBlankSpace(int);
void PrintBoard(char *, int, int);
void ResetBoard(char *, int, int);
int TakeTurnPlayer(char *, int, int, int);
int TakeTurnComputer(char *, int, int, int);
int DFScheck(char *, int, int, int, char, int);
int WinCondition(char *, int, int, int, char, int);
int winConditionVert(char *, int, int, int);
int winConditionDiag(char *, int, int, int);
char PlayerNumToSymbol(int);
int SymbolToPlayerNum(char);
void printRules();
void ReturnToMenuPrompt();



/*

A 3,4, and 5 player mode can be made asily by making the modulo used with TakeTurnPlayer a variable of the number of users

the TakeTurnPlayer function must then simply add more if else statements using the playerTurn variables


-possibly add a 'settings' option where one could change their piece character or the number of pieces in a row needed to win

*/

int main(int argc, char *argv[]){
	int rows;
	int cols;
	
	PrintBlankSpace(40);
	printf("Welcome to the Connect Four game, what size board would you like to play with?\n");
	printf("We suggest not going over a 10x10 size board, as it will not appear correctly ");
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
	int inputTemp2 = -1;
	int users = 2;
	int winPerPlayer[10];
	while(userWantsToPlay == 1){
		printf("Here are your options \n");
		printf("--------------------- \n");
		printf("'1' - play against computer \n");
		printf("'2' - play local multiplayer \n");
		printf("'3' - show me the stats \n");
		printf("'8' - show the rules \n");
		printf("'9' - exit game \n");
		scanf("%d", &inputTemp);
		switch(inputTemp){
			case 1:
				win = -1;
				while(turnsTaken < rows*cols && win == -1 ){
					if(turnsTaken % 2 == 0){
						win = TakeTurnPlayer(board, rows, cols, turnsTaken%2);
					} else {
						win = TakeTurnComputer(board, rows, cols, turnsTaken%2);
					}
					turnsTaken++;
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				printf("WINNER is Player ");
				printf("%c", PlayerNumToSymbol(win));
				printf("\n");
				winPerPlayer[win]++;
				ReturnToMenuPrompt();
				ResetBoard(board, rows, cols);
				turnsTaken = 0;				
				PrintBlankSpace(40);
				//clean up the output a little more here and maybe show stats 
				break;
			case 2:
				win = -1;
				while(turnsTaken < rows*cols && win == -1 ){
					win = TakeTurnPlayer(board, rows, cols, turnsTaken%2);
					turnsTaken++;
				} 
				PrintBlankSpace(40);
				PrintBoard(board, rows, cols);
				printf("WINNER is Player ");
				printf("%c", PlayerNumToSymbol(win));
				printf("\n");
				winPerPlayer[win]++;
				ReturnToMenuPrompt();
				ResetBoard(board, rows, cols);
				turnsTaken = 0;				
				PrintBlankSpace(40);
				//clean up the output a little more here and maybe show stats 
				break;
			case 3:
				//print the stats for each 
				break;
			case 4:
				break;
			case 5:
				break;
			case 8:
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

int SymbolToPlayerNum(char symbol){
	if(symbol == 'O'){
		return 0;
	} else if(symbol == 'X'){
		return 1;
	}
}

char PlayerNumToSymbol(int playerNum){
	if(playerNum == 0){
		return 'O';
	} else if(playerNum == 1){
		return 'X';
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
		if(index + cols - 1 > rows*cols){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols-1; 
	}
	if (direction == 5){
		if(index - cols + 1 < 0){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index-cols+1;
	}
	if (direction == 4){
		if(index + cols + 1 > rows*cols){				
			if(board[index] == symbol){
				return 1;							
			} else {
				return 0;							
			}
		}
		nextIndex = index+cols+1;
	}
	if (direction == 3){
		if(index - cols - 1 < 0){				
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

int WinCondition(char board[], int rows, int cols, int indexToCheck, char symbol, int winNum){
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
		return SymbolToPlayerNum(symbol);		//returns the player who won's playerNum
	}
	
	return -1;
}

int TakeTurnPlayer(char board[], int rows, int cols, int playerNum){
	int input = -1;
	PrintBlankSpace(40);
	PrintBoard(board, rows, cols);
	printf("Player 1: Choose what column to place your piece. \n");
	printf("Column: ");
	scanf("%d", &input);
	int i;
	for(i = rows*cols - (cols-input); i >= input; i = i-cols){
		/*
		* This for loop starts at the bottom row of the column the user selected
		* the loop keeps going up the column until it finds an open spot
		*/
		if(board[i] == '-'){
			if(playerNum == 0){
				board[i] = 'O';
				return WinCondition(board, rows, cols, i, 'O', 4);
			} else if (playerNum == 1){
				board[i] = 'X';
				return WinCondition(board, rows, cols, i, 'X', 4);
			} //to add more players just add more else if statements with different 
		}
	}
}

int TakeTurnComputer(char board[], int rows, int cols, int playerNum){
	int input = -1;
	PrintBlankSpace(40);
	//PrintBoard(board, rows, cols);
	//printf("COMPU \n");
	//printf("Column: ");
	//scanf("%d", &input);
	int i;
	input = rand() % cols;
	for(i = rows*cols - (cols-input); i >= input; i = i-cols){
		/*
		* This for loop starts at the bottom row of the column the user selected
		* the loop keeps going up the column until it finds an open spot
		*/
		if(board[i] == '-'){
			if(playerNum == 0){
				board[i] = 'O';
				return WinCondition(board, rows, cols, i, 'O', 4);
			} else if (playerNum == 1){
				board[i] = 'X';
				return WinCondition(board, rows, cols, i, 'X', 4);
			} //to add more players just add more else if statements with different 
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
	printf("THESE THE DAMN RULES \n");
}

void ReturnToMenuPrompt(){
	int inputTemp = -1;
	printf("Type '1' to return to main menu \n");
	inputTemp = -1;
	while(inputTemp != 1){
		scanf("%d", &inputTemp);
	}
}
