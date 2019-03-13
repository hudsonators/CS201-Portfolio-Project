#include <stdlib.h>
#include <stdio.h>

void PrintBlankSpace();
void PrintBoard(char *, int, int);
void ResetBoard(char *, int, int);
int checkFour();
int TakeTurnPlayer(char *, int, int, int);

/*

A 3,4, and 5 player mode can be made asily by making the modulo used with TakeTurnPlayer a variable of the number of users

the TakeTurnPlayer function must then simply add more if else statements using the playerTurn variables

*/

int main(int argc, char *argv[]){
	int rows = 6;
	int cols = 7;
	
	PrintBlankSpace();
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
	int win = 0;							//win = 1 if player 1 is winner win = 2 if player 2 is winner
	int userWantsToPlay = 1;				//this variable keeps the most outter while loop going as long as the user wants to continue playing
	int inputTemp = -1;
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
				while(turnsTaken < rows*cols || win != 0 ){
					//this is where the game is played against computer
					turnsTaken++;
				}
				break;
			case 2:
				while(turnsTaken < rows*cols || win != 0 ){
					win = TakeTurnPlayer(board, rows, cols, turnsTaken%2);
					turnsTaken++;
				} 
				//put endgame output here like a win or tie and the final board
				break;
			case 3:
				//print the stats for each 
				break;
			case 4:
				break;
			case 5:
				break;
			case 8:
				//add print statement for the rules
				break;
			case 9:
				printf("See you next time! \n");
				userWantsToPlay = 0;
				break;
		}
	}
}

int TakeTurnPlayer(char board[], int rows, int cols, int playerNum){
	int input = -1;
	PrintBlankSpace();
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
				return 0;
			} else if (playerNum == 1){
				board[i] = 'X';
				return 0;
			} //to add more players just add more else if statements with different 
		}
		
	}
}

void PrintBlankSpace(){
	/*	
	* This function prints many lines of blank space
	* This is to be used for formatting purposes of the output
	*/
	int j;
	for(j = 0; j<40; j++){
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

int checkFour(){
	//using the position of the inserted piece, do 
}
