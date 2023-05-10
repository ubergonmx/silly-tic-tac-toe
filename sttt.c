/*
Copyright (c) 2021, ubergonmx
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree. 
*/

#include <stdio.h>
#include <stdlib.h> /* I used system function to clear screen*/
#include <string.h> /* I used strcpy function to copy strings*/


/*declaring Constant variables*/
#define SIZE 5
#define PLAYER1 'X'
#define PLAYER2 'O'
#define BLANK ' '


/*----------------------------PROTOTYPES----------------------------*/

/*Color/Formatting functions*/
void colorBlue();
void colorCyan();
void colorGreen();
void colorPurple();
void colorRed();
void formatReset();
void colorWhite();
void colorYellow();
void inverse();
void underline();

/*Game functions*/
int gameCheck(char cBoard[][SIZE], char cPlayer);
void gameChooseAbility(char cBoard[][SIZE], int iNumOfAbilities, int iIsAbilityHidden);
void gameDraw();
void gameLogic(char cBoard[][SIZE], char cPlayer, char cPreviousPlayer, int iPlayer1Abilities[], int iPlayer2Abilities[], int iNumOfAbilities, int iIsAbilityHidden);
void gameStart();
void gameTurn(char cBoard[][SIZE], char cPlayer,int iPlayer1Abilities[], int iPlayer2Abilities[], int iNumOfAbilities, int iIsAbilityHidden);
void gameUpdate(char cBoard[][SIZE], char cPlayer);
void gameUpdateWithStatus(char cBoard[][SIZE], char cPlayer, char strGameStatus[]);
int gameUseAbility(char cBoard[][SIZE], char cPlayer, int *iTurns, int iAbilities[], int iOpponentAbilities[], int iNumOfAbilities, int iIsAbilityHidden, char strGameStatus[], int iAbility1);
void gameWinner(char cPlayer);
char getFromBoard(char cBoard[][SIZE], int iPlace);
int getHorizontalRow(char cBoard[][SIZE], char cPlayer, int iRequirement);
int getDiagonalRow(char cBoard[][SIZE], char cPlayer, int iRequirement);
int getVerticalRow(char cBoard[][SIZE], char cPlayer, int iRequirement);
void placeToBoard(char cBoard[][SIZE], int iPlace, char cInput);
void showBoard(char cBoard[][SIZE]);
void showAbilityUsed(int iAbility);
void showGameStatus(char cPlayer, char strGameStatus[]);
void showPlayerTurn(char cPlayer);

/*Abilities functions*/
void ability1(int **iTurns);
void ability2(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1);
void ability3(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1);
void ability4(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1);
void ability5(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1);
void ability6(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1);
void ability7(int iOpponentAbilities[], int iNumOfAbilities, int iIsAbilityHidden, char strGameStatus[], int iAbility1);
int ability8(char cPlayer, int* iAbility);

/*Intro or start functions*/
void showAbilities();
void showGameTitle();
void showHowToPlay();
void showMenu();

/*Miscellaneous functions*/
void clearScreen();
void getOpponent(char cPlayer, char *cOpponent);
void getOrdinalNumber(int iLoop, char strOrdinalNum[]);
void getAbilityName(int iLoop, char strAbilityName[]);
void listAbilities(int iShowNum);
int promptUser();
void showPlacementNumbers();


main(){
	showMenu();
}


/*----------------------------COLOR/FORMATTING FUNCTIONS----------------------------*/

/*These functions are for design purposes only

REFERENCE:
-https://www.theurbanpenguin.com/4184-2/
*/
void underline(){
	printf("\033[4m");
}
void inverse(){
	printf("\033[7m");
}

void colorRed () {
	printf("\033[1;31m");
}
void colorGreen(){
	printf("\033[1;32m");
}
void colorYellow(){
	printf("\033[1;33m");
}
void colorBlue(){
	printf("\033[1;34m");
}
void colorPurple(){
	printf("\033[1;35m");
}	
void colorWhite(){
	printf("\033[1;37m");
}
void colorCyan(){
	printf("\033[1;36m");
}

void formatReset() {
	printf("\033[0m");
}

/*----------------------------GAME FUNCTIONS----------------------------*/

/*Show board in a fashion way*/
void showBoard(char cBoard[][SIZE])
{
	int iRow, iCol, iNum;
	
	showGameTitle();
	colorYellow();
	printf("\n\t\t\t\t\b\b\b\b\b[GAME]");
	formatReset();
	printf("\n\t\t\t\b\b\b\b---------------------");
	for(iRow=0; iRow<5;iRow++)
	{		
		printf("\n\t\t\t\b\b\b\b|");
		/*The following for-loop prints 5 spaces in 1 row
			ex: (this is the output)
				O | X |  |  | O |
		*/
		for(iCol=0; iCol<5; iCol++)
		{
			/*Apply color formatting*/
			switch(cBoard[iRow][iCol])
			{
				case PLAYER1:
					colorCyan();
					break;
				case PLAYER2:
					colorPurple();
					break;
				default:
					colorWhite();
			}
			printf("%2c", cBoard[iRow][iCol]);	
			formatReset();
			printf(" |");
			
		}
		printf("\n\t\t\t\b\b\b\b---------------------");	
	}
	printf("\n\n");	
}

/*Return character (either X, O, or ' ') from board depending on the iPlace*/
char getFromBoard(char cBoard[][SIZE], int iPlace)
{
	char cPlaceValue;
	switch (iPlace){
		case 1:
			cPlaceValue=cBoard[0][0];
			break;
		case 2:
			cPlaceValue=cBoard[0][1];
			break;
		case 3:
			cPlaceValue=cBoard[0][2];
			break;
		case 4:
			cPlaceValue=cBoard[0][3];
			break;
		case 5:
			cPlaceValue=cBoard[0][4];
			break;
		case 6:
			cPlaceValue=cBoard[1][0];
			break;
		case 7:
			cPlaceValue=cBoard[1][1];
			break;
		case 8:
			cPlaceValue=cBoard[1][2];
			break;
		case 9:
			cPlaceValue=cBoard[1][3];
			break;
		case 10:
			cPlaceValue=cBoard[1][4];
			break;
		case 11:
			cPlaceValue=cBoard[2][0];
			break;
		case 12:
			cPlaceValue=cBoard[2][1];
			break;
		case 13:
			cPlaceValue=cBoard[2][2];
			break;
		case 14:
			cPlaceValue=cBoard[2][3];
			break;
		case 15:
			cPlaceValue=cBoard[2][4];
			break;
		case 16:
			cPlaceValue=cBoard[3][0];
			break;
		case 17:
			cPlaceValue=cBoard[3][1];
			break;
		case 18:
			cPlaceValue=cBoard[3][2];
			break;
		case 19:
			cPlaceValue=cBoard[3][3];
			break;
		case 20:
			cPlaceValue=cBoard[3][4];
			break;
		case 21:
			cPlaceValue=cBoard[4][0];
			break;
		case 22:
			cPlaceValue=cBoard[4][1];
			break;
		case 23:
			cPlaceValue=cBoard[4][2];
			break;
		case 24:
			cPlaceValue=cBoard[4][3];
			break;
		case 25:
			cPlaceValue=cBoard[4][4];
			break;
	}
	
	return cPlaceValue;
}

/*Place the character(either X, O, or ' ') on the board*/
void placeToBoard(char cBoard[][SIZE], int iPlace, char cInput)
{
	switch (iPlace){
		case 1:
			cBoard[0][0]=cInput;
			break;
		case 2:
			cBoard[0][1]=cInput;
			break;
		case 3:
			cBoard[0][2]=cInput;
			break;
		case 4:
			cBoard[0][3]=cInput;
			break;
		case 5:
			cBoard[0][4]=cInput;
			break;
		case 6:
			cBoard[1][0]=cInput;
			break;
		case 7:
			cBoard[1][1]=cInput;
			break;
		case 8:
			cBoard[1][2]=cInput;
			break;
		case 9:
			cBoard[1][3]=cInput;
			break;
		case 10:
			cBoard[1][4]=cInput;
			break;
		case 11:
			cBoard[2][0]=cInput;
			break;
		case 12:
			cBoard[2][1]=cInput;
			break;
		case 13:
			cBoard[2][2]=cInput;
			break;
		case 14:
			cBoard[2][3]=cInput;
			break;
		case 15:
			cBoard[2][4]=cInput;
			break;
		case 16:
			cBoard[3][0]=cInput;
			break;
		case 17:
			cBoard[3][1]=cInput;
			break;
		case 18:
			cBoard[3][2]=cInput;
			break;
		case 19:
			cBoard[3][3]=cInput;
			break;
		case 20:
			cBoard[3][4]=cInput;
			break;
		case 21:
			cBoard[4][0]=cInput;
			break;
		case 22:
			cBoard[4][1]=cInput;
			break;
		case 23:
			cBoard[4][2]=cInput;
			break;
		case 24:
			cBoard[4][3]=cInput;
			break;
		case 25:
			cBoard[4][4]=cInput;
			break;
	}
	
	
}
/*This function determines whether the game will continue or stop
 return 0 = Game continues
 return 1 = Player has won
 return 2 = Game draw
*/
int gameCheck(char cBoard[][SIZE],char cPlayer)
{
	int iSpaces, iOccupied=0;
	for(iSpaces=0; iSpaces<=25; iSpaces++)
	{
		/*Count spaces that are occupied*/
		if(getFromBoard(cBoard, iSpaces)==PLAYER1 || getFromBoard(cBoard, iSpaces)==PLAYER2)
			iOccupied++;
				
	}
	/*Player has won if a row, a column, or a diagonal line has 5 spaces occupied by the player*/
	if(getHorizontalRow(cBoard, cPlayer, 5) == 5 || getVerticalRow(cBoard, cPlayer, 5) == 5 || getDiagonalRow(cBoard, cPlayer, 5) == 5)
	{
		return 1;
	}
	/*Game draw if all spaces are occupied and the player hasn't occupied 5 spaces*/
	else if(iOccupied==25)
	{
		return 2;
	}
	/*Game continues if the conditions above are not true*/
	return 0;
}

int getHorizontalRow(char cBoard[][SIZE], char cPlayer, int iRequirement){
	int iOccupied, iLoop1, iLoop2;
	
	/*Get the number of occupied spaces by the player on each horizontal row*/
	for(iOccupied=0,iLoop1=0; iLoop1<5; iLoop1++)
	{
		/*If the number of occupied spaces is less than the requirement, reset iOccupied to 0 and check again*/
		if(iOccupied<iRequirement){
			iOccupied=0;
			for(iLoop2=0; iLoop2<5; iLoop2++){
				if(cBoard[iLoop1][iLoop2]==cPlayer)
					iOccupied++;
			}
		}
	}
	return iOccupied;
}

int getVerticalRow(char cBoard[][SIZE], char cPlayer, int iRequirement){
	int iOccupied, iLoop1, iLoop2;
	
	/*Get the number of occupied spaces by the player on each vertical row*/
	for(iOccupied=0,iLoop1=0; iLoop1<5; iLoop1++)
	{
		/*If the number of occupied spaces is less than the requirement, reset iOccupied to 0 and check again*/
		if(iOccupied<iRequirement){
			iOccupied=0;
			for(iLoop2=0; iLoop2<5; iLoop2++){
				if(cBoard[iLoop2][iLoop1]==cPlayer)
					iOccupied++;
			}
		}
	}
	return iOccupied;
}

int getDiagonalRow(char cBoard[][SIZE], char cPlayer, int iRequirement){
	int iOccupied, iLoop1, iLoop2;
	
	/*Get the number of occupied spaces by the player on the first diagonal row (\) */
	for(iOccupied=0,iLoop1=0; iLoop1<5; iLoop1++){
		if(cBoard[iLoop1][iLoop1]==cPlayer)
			iOccupied++;
	}
	/*If the number of occupied spaces is less than the requirement, reset iOccupied to 0
	and then get the number of occupied spaces by the player on the second diagonal row (/) */
	if(iOccupied<iRequirement){
		for(iOccupied=0,iLoop1=0, iLoop2=4; iLoop1<5, iLoop2>=0; iLoop1++, iLoop2--)
		{
			if(cBoard[iLoop1][iLoop2]==cPlayer)
				iOccupied++;
		}
	}
	return iOccupied;
}

/*Show winner depending on the cPlayer*/
void gameWinner(char cPlayer){
	if(cPlayer==PLAYER1){
		colorCyan();
		printf("\t\t   PLAYER 1 IS THE WINNER!");
	}
	else{
		colorPurple();
		printf("\t\t   PLAYER 2 IS THE WINNER!");
	}
	formatReset();
}
/*Show draw message*/
void gameDraw(){
	colorWhite();
	printf("\t\t\t\t\b\b\b\bDRAW!");
	formatReset();
}
/*This function determines whether to pass the turn to the next player or stop the game and show results*/
void gameLogic(char cBoard[][SIZE], char cPlayer, char cPreviousPlayer, int iPlayer1Abilities[], int iPlayer2Abilities[], int iNumOfAbilities, int iIsAbilityHidden)
{
	/*gameCheck return values: 0 (game continues), 1 (winner), 2(draw)*/
	int iGameStop = gameCheck(cBoard, cPreviousPlayer);
	
	/*Check if the game continues, !iGameStop also means iGameStop==0*/
	if(!iGameStop)
	{
		/* Pass the turn to the next player */
		gameTurn(cBoard, cPlayer, iPlayer1Abilities, iPlayer2Abilities, iNumOfAbilities, iIsAbilityHidden);
	}
	else
	{
		showBoard(cBoard);
		
		/*1 = winner, 2 = draw */
		if(iGameStop==1)
			gameWinner(cPreviousPlayer);
		else if(iGameStop==2)
			gameDraw();

		/* Ask players if they want to restart/play again*/
		printf("\n\t\t\t\b\b\bTHANKS FOR PLAYING!");
		printf("\n\n\t\t   [1] Restart\n\t\t   [2] Return to main menu\n\n");
		
		if(promptUser()==1)
			gameStart();
		else
			showMenu();
	}
}
/*Visually updates the screen*/
void gameUpdate(char cBoard[][SIZE], char cPlayer)
{
	/*This will clear the screen, show the title and the board*/
	showBoard(cBoard);	
	/*Show whose turn it is*/
	showPlayerTurn(cPlayer);
}
/*Visually updates the screen with custom message/game status*/
void gameUpdateWithStatus(char cBoard[][SIZE], char cNextPlayer, char strGameStatus[])
{
	/*This will clear the screen, show the title and the board*/
	showBoard(cBoard);
	/*If the strGameStatus contains 1 on the first index, proceed to show the message*/
	if(strGameStatus[0]=='1')
		showGameStatus(cNextPlayer, strGameStatus);
	/*Show whose turn it is*/
	showPlayerTurn(cNextPlayer);
}

/*This function is responsible for the abilities
	returns iSkipTurn wherein the values are:
	0 = use normal turn
	1 = skip the normal turn
*/
int gameUseAbility(char cBoard[][SIZE], char cPlayer, int *iTurns, int iAbilities[], int iOpponentAbilities[], int iNumOfAbilities, int iIsAbilityHidden, char strGameStatus[], int iAbility1)
{
	int iAbility, iSkipTurn=0, iLoop, iNewLine, iCounter, iIsAbilityUsed;
	char strAbility[15] = "";
	
	/*Display available abilities in a fashion way*/
	printf("\n [AVAILABLE ABILITIES]");
	if(iIsAbilityHidden)
		printf(" - Ability names hidden!");
	printf("\n\t");
	for(iLoop=0, iNewLine=1; iLoop < iNumOfAbilities; iLoop++){
		if(iAbilities[iLoop] !=0){
			
			/*If iIsAbilityHidden is 1, it will show "???"*/
			if(iIsAbilityHidden)
				strcpy(strAbility, "???");
			else
				getAbilityName(iAbilities[iLoop]-1, strAbility);
			
			colorGreen();
			printf("%d", iLoop+1);
			formatReset();
			
			printf("-%s\t", strAbility);
			
			/*Enter new line after the 4th ability shown*/
			if(iNewLine % 4 == 0)
				printf("\n\t");
			iNewLine++;
		}
	}
	printf("0-normal turn ");
	
	/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
		-Input within 0 to number of abilities
		-Input matches ability that exist
	*/
	do{
		iIsAbilityUsed=0;
		
		colorWhite();
		printf("\n > Use an ability? ", iNumOfAbilities);
		scanf("%d", &iAbility);	
		
		colorRed();
		if(iAbility <0 || iAbility > iNumOfAbilities)
			printf(" Enter number from the choices only.\n");
		else{
			/*This condition is for the array, we want to avoid -1 index*/
			if(iAbility!=0){
				if(iAbilities[iAbility-1] == 0){
					printf(" Ability is used/removed. Select another ability or use normal turn.\n");
					iIsAbilityUsed=1;
				}		
			}
		}
		formatReset();
	} while(iAbility <0 || iAbility > iNumOfAbilities || iIsAbilityUsed);

	/* If the player inputted 0 or inputted Counter ability, this whole if-statement will be skipped */
	if(iAbility != 0 && iAbilities[iAbility-1] != 8)
	{
		iCounter=0;
		/* Check for opponent's Counter ability */
		for(iLoop=0; iLoop < iNumOfAbilities; iLoop++)
			if(iOpponentAbilities[iLoop]==8)
				/*iCounter will be assigned to 0 if the oppponent doesnt want to counter ability, otherwise assigned to 1*/
				iCounter=ability8(cPlayer, &iOpponentAbilities[iLoop]);

		/*If the ability is not countered, use the ability and skip turn. Otherwise, do not skip turn*/
		if(!iCounter){
			/*iAbility1 is passed to determine if the screen will keep printing or will clear screen once gameUpdate is called
			if iAbility1 is 1, allow to print game messages
			else copy the message so that it will be shown on the next gameUpdate
			*/
			switch(iAbilities[iAbility-1]){
				case 1:
					ability1(&iTurns);
					break;
				case 2:
					ability2(cBoard, cPlayer, strGameStatus, iAbility1);
					break;
				case 3:
					ability3(cBoard, cPlayer, strGameStatus, iAbility1);
					break;
				case 4:
					ability4(cBoard, cPlayer, strGameStatus, iAbility1);
					break;
				case 5:
					ability5(cBoard, cPlayer, strGameStatus, iAbility1);
					break;
				case 6:
					ability6(cBoard, cPlayer, strGameStatus, iAbility1);
					break;
				case 7:
					ability7(iOpponentAbilities, iNumOfAbilities, iIsAbilityHidden, strGameStatus, iAbility1);
					break;
			}
			iSkipTurn=1;
		}
		/* Assign 0 to that ability after it is used or countered*/
		iAbilities[iAbility-1]=0;
	}
	return iSkipTurn;
}
void gameTurn(char cBoard[][SIZE], char cPlayer,int iPlayer1Abilities[], int iPlayer2Abilities[], int iNumOfAbilities, int iIsAbilityHidden){
	
	int iPlace, iLoop, iAvailableAbilities, iTurns = 0, iSkipTurn, iAbility1, iGameStop=0;
	char cNextPlayer, strGameStatus[100]="";
	
	/*DO-WHILE loop until the iTurns is 0*/
	do
	{
		iAbility1=0; /*The purpose of this flag is just for the messages on abilities (printf) - we want the messages to be shown properly*/
		iSkipTurn=0;
		iAvailableAbilities = 0;
				
		/*Make iAbility1 true (or value to 1) if iTurns is equal to 2 - which means ability1 (AnotherTwo/Take 2 turns) is used*/
		if(iTurns !=0){		
			if(iTurns == 2)
				iAbility1=1;
			iTurns--;
		}
		/*
		The purpose of this iGameStop is for the ability1 (AnotherTwo/Take 2 turns).
		Once the Player has occupied 5 spaces in a row even if the player has 1 more turn, 
		end the do-while loop by assigning 0 to iTurns
		*/
		if(!iGameStop){
			/*Check whose turn is it*/
			if(cPlayer == PLAYER1)
			{								
				/*Count PLAYER 1's abilities that have not been used*/
				for(iLoop=0; iLoop<iNumOfAbilities; iLoop++){	
					if(iPlayer1Abilities[iLoop] != 0)
						iAvailableAbilities++;
				}
				/*Check if PLAYER 1 has abilities left*/
				if(iAvailableAbilities!=0)
					iSkipTurn=gameUseAbility(cBoard, PLAYER1, &iTurns, iPlayer1Abilities, iPlayer2Abilities, iNumOfAbilities, iIsAbilityHidden, strGameStatus, iAbility1);
				
				
				/*Assign the next player which is PLAYER2*/
				cNextPlayer=PLAYER2;
			}
			else{
				/*Count PLAYER 2's abilities that have not been used*/
				for(iLoop=0; iLoop<iNumOfAbilities; iLoop++){	
					if(iPlayer2Abilities[iLoop] != 0)
						iAvailableAbilities++;
				}
				/*Check if PLAYER 2 has abilities left*/
				if(iAvailableAbilities!=0)
					iSkipTurn=gameUseAbility(cBoard, PLAYER2, &iTurns, iPlayer2Abilities, iPlayer1Abilities, iNumOfAbilities, iIsAbilityHidden, strGameStatus, iAbility1);
			
				/*Assign the next player which is PLAYER1*/
				cNextPlayer=PLAYER1;
			}
			
			if(!iSkipTurn){
				do{
					printf("\n [NORMAL TURN]");
					colorWhite();
					printf("\n > Where do you want to place? [1-25]: ");
					scanf("%d", &iPlace);	
					
					colorRed();
					if(iPlace <1 || iPlace > 25)
						printf(" Enter number from 1 to 25 only.\n");
					else if(getFromBoard(cBoard, iPlace) != BLANK)
						printf(" Place is already occupied, enter other number from 1 to 25.\n");
					formatReset();		
				} while(iPlace <1 || iPlace >25 || getFromBoard(cBoard, iPlace) != BLANK);
				
				placeToBoard(cBoard, iPlace, cPlayer);
				
				/*This part updates the board visually*/
				gameUpdate(cBoard, cPlayer);
			}
			
			/*Set the flag iGameStop with gameCheck*/
			iGameStop=gameCheck(cBoard, cPlayer);
		} 
		else
			iTurns = 0;
		
	} while(iTurns > 0 );
	
	/*This part does the following if the game hasn't ended yet
		1. Updates the board visually 
		2. Show Game Status (Ability errors,etc)
		3. Show the NEXT PLAYER
	*/
	if(!iGameStop)
		gameUpdateWithStatus(cBoard, cNextPlayer, strGameStatus);
	
	/*This stops the turn of the current player and passes the turn to the next player*/
	gameLogic(cBoard, cNextPlayer, cPlayer, iPlayer1Abilities, iPlayer2Abilities, iNumOfAbilities, iIsAbilityHidden);
	
}
/*Show on the screen which ability is used*/
void showAbilityUsed(int iAbility){
	char strAbility[15]="";
	getAbilityName(iAbility, strAbility);
	colorGreen();
	printf("\n [ABILITY USED: %s] ", strAbility);	
	formatReset();
}
void showGameStatus(char cPlayer, char strGameStatus[]){
	/*
		The purpose of this function is to show the abilities messages 
		after the turn of the player ends (which will clear the screen)

		cPlayer has the next player, so print out the previous player
	*/
	if(cPlayer==PLAYER1){
		printf(" [PLAYER 2]");
	}
	else{
		printf(" [PLAYER 1]");
	}
	/*Convert '1' to a space*/
	strGameStatus[0] = ' ';
	colorBlue();
	printf("%s\n\n", strGameStatus);
	formatReset();
	/* Reset Game Status */
	strcpy(strGameStatus, "");
}
/*Show on the screen whose turn it is*/
void showPlayerTurn(char cPlayer){
	if(cPlayer==PLAYER1)
	{
		colorCyan();
		inverse();
		printf(" Player 1's turn (X)");
		formatReset();
	}
	else{		
		colorPurple();
		inverse();
		printf(" Player 2's turn (O)");
		formatReset();
		
	}
}
void gameChooseAbility(char cBoard[][SIZE], int iNumOfAbilities, int iIsAbilityHidden)
{
	int iPlayer1Abilities[iNumOfAbilities],iPlayer2Abilities[iNumOfAbilities], iLoop, iLoop2, iError;
	char sError1[40]="Please select from 1 to 8 only.";
	char sError2[40]="Please select another unique ability.";
	char sErrorMsg[40] = "";
	char strAbility[15] = "";
	
	/* Player 1 (X) will now select his/her own abilities depending on the number of abilities*/
	for(iLoop=0; iLoop<iNumOfAbilities; iLoop++)
	{
		/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
			-Input number within 1 to number of abilities
		*/
		do {
			showGameTitle();
			listAbilities(1);
	
	        if(iIsAbilityHidden)
	        {
	        	inverse();
	        	printf("\n NOTE: PLAYER 2 MUST LOOK AWAY FROM THE SCREEN.");
	        	formatReset();
	    	}

			colorCyan();
			printf("\n PLAYER 1 (X) IS CHOOSING\n");
			
			/*Print error message if there's an error */
			if(iError){	
				colorRed();
				printf(" %s\n", sErrorMsg);
				/*Reset error message*/
				iError=0;
				strcpy(sErrorMsg, "");
			}
			
			colorWhite();
			/*strAbility is just for game text - determines which position to be stored in the abilities array*/
			getOrdinalNumber(iLoop, strAbility);
			printf(" (%d/%d) Select %s [1-8]: ", iLoop+1, iNumOfAbilities, strAbility);
			scanf("%d", &iPlayer1Abilities[iLoop]);
			
			/*Copy error message so that it will show when it loops again*/
			if(iPlayer1Abilities[iLoop]<=0 || iPlayer1Abilities[iLoop]>8){
				iError=1;
				strcpy(sErrorMsg, sError1);
			}
			for(iLoop2=0; iLoop2<iLoop; iLoop2++){
				if(iPlayer1Abilities[iLoop] == iPlayer1Abilities[iLoop2]){
					iError=1;
					strcpy(sErrorMsg, sError2);	
					iLoop--; /*subtract iLoop to avoid duplication of abilities*/
				}
			}

			formatReset();
		}while(iPlayer1Abilities[iLoop] <= 0 || iPlayer1Abilities[iLoop] > 8);
	}
	
	/* Player 2 (Y) will now select his/her own abilities depending on the number of abilities */
	for(iLoop=0; iLoop<iNumOfAbilities; iLoop++)
	{
		/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
			-Input number within 1 to number of abilities
		*/
		do {
			showGameTitle();
			listAbilities(1);
			
			if(iIsAbilityHidden)
	        {
	        	inverse();
	        	printf("\nNOTE: PLAYER 1 MUST LOOK AWAY FROM THE SCREEN.");
	        	formatReset();
	    	}		

			colorPurple();
			printf("\n Player 2 (O) IS CHOOSING\n");
			/*Print error message if there's an error */
			if(iError){	
				colorRed();
				printf(" %s\n", sErrorMsg);	
				/*Reset error message*/
				iError=0;
				strcpy(sErrorMsg, "");
			}
			
			colorWhite();
			/*strAbility is just for game text - determines which position to be stored in the abilities array*/
			getOrdinalNumber(iLoop, strAbility);
			printf(" (%d/%d) Select %s [1-8]: ", iLoop+1, iNumOfAbilities, strAbility);
			scanf("%d", &iPlayer2Abilities[iLoop]);
			
			strcpy(sErrorMsg, "");
			/*Copy error message and make iError to 1 (which means TRUE) so that it will show when it loops again*/
			if(iPlayer2Abilities[iLoop]<=0 || iPlayer2Abilities[iLoop]>8){
				iError=1;
				strcpy(sErrorMsg, sError1);
			}
			for(iLoop2=0; iLoop2<iLoop; iLoop2++){
				if(iPlayer2Abilities[iLoop] == iPlayer2Abilities[iLoop2]){
					iError=1;
					strcpy(sErrorMsg, sError2);	
					iLoop--; /*subtract iLoop to avoid duplication of abilities*/
				}
			}
			formatReset();
		}while(iPlayer2Abilities[iLoop] <= 0 || iPlayer2Abilities[iLoop] > 8);
	}
	
	gameUpdate(cBoard, PLAYER1);
	gameLogic(cBoard, PLAYER1, 0, iPlayer1Abilities,  iPlayer2Abilities, iNumOfAbilities, iIsAbilityHidden);
}
void gameStart()
{
	/*THIS IS THE BOARD - When gameStart() is called, a new board will be created and be passed.*/
	char cBoard[SIZE][SIZE] = {
		{BLANK, BLANK, BLANK, BLANK, BLANK},
		{BLANK, BLANK, BLANK, BLANK, BLANK},
		{BLANK, BLANK, BLANK, BLANK, BLANK},
		{BLANK, BLANK, BLANK, BLANK, BLANK},
		{BLANK, BLANK, BLANK, BLANK, BLANK}
	}, cChoice;
	int iNumOfAbilities;
	
	showGameTitle();
	
	printf("\t\t\t\b\b[GAME SETTINGS]\n");

	/*Ask the players how many abilities they want*/
	do {
		printf("\n\t\t\b\b\b\b\bHow many abilities do you want? [0-8]: ");
		scanf("%d", &iNumOfAbilities);
		if(iNumOfAbilities < 0 || iNumOfAbilities > 8){
			colorRed();
			printf("\t\t\b\b\b\b\bPlease enter number from 1 to 8 only.");
			formatReset();
		}
	} while (iNumOfAbilities < 0 || iNumOfAbilities > 8);
	
	/*If the input is not 0, ask players if they like the abilities' names to be hidden*/
	if(iNumOfAbilities!=0){
		do {
			printf("\n\t\t\b\b\b\b\bWould you like the abilities' names to be hidden during the game? [y/n]: ");
			cChoice = getche();
			if(cChoice != 'Y' && cChoice != 'N'&&  cChoice != 'y' &&  cChoice != 'n'){
				colorRed();
				printf("\n\t\t\b\b\b\b\bPlease choose Y or N only.");
				formatReset();
			}
		} while ( cChoice != 'Y' && cChoice != 'N' &&  cChoice != 'y' && cChoice != 'n');
		
		/* 1=TRUE and 0=FALSE, so if the player chose y/Y, it will pass true on iIsAbilityHidden */
		if(cChoice == 'y' || cChoice == 'Y')
			gameChooseAbility(cBoard, iNumOfAbilities, 1);
		else
			gameChooseAbility(cBoard, iNumOfAbilities, 0);
	}
	else{
		gameUpdate(cBoard, PLAYER1);
		gameLogic(cBoard, PLAYER1, 0, 0, 0, 0, 0);
	}
}
/*----------------------------ABILITIES FUNCTIONS----------------------------*/
void ability1(int **iTurns){
	/* Add 2 turns: for each turn, a player can use an ability or use normal turn */	
	**iTurns+=2;
	showAbilityUsed(0);
	printf("Added 2 turns for the player.\n");
}
void ability2(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1){
	int iReplace, iHasOpponentSymbol = 0, iLoop;
	char cOpponent;
	
	/* Get the player's opponent */
	getOpponent(cPlayer, &cOpponent);
	
	/* Check each space if it has opponent's symbol */
	for(iLoop = 0; iLoop <= 25; iLoop++)
	{
		if(getFromBoard(cBoard, iLoop) == cOpponent)
			iHasOpponentSymbol = 1;
	}
	
	showAbilityUsed(1);
	/*If the opponent has symbol on the board, proceed to use the ability; else print an error message*/
	if(iHasOpponentSymbol){
		/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
			-Input space within 1-25
			-Input space has opponent's symbol
		*/
		do{
			colorGreen();
			printf("\n > Choose a place to replace opponent's symbol [1-25]: ");
			scanf("%d", &iReplace);	
			
			colorRed();
			if(iReplace <1 || iReplace > 25)
				printf(" Enter number from 1 to 25 only.\n");
			else if(getFromBoard(cBoard, iReplace) != cOpponent)
				printf(" Place is not occupied by opponent, enter other number from 1 to 25.\n");
			formatReset();
		}while (iReplace <1 || iReplace >25 || getFromBoard(cBoard, iReplace) != cOpponent);
		
		/*Replace the symbol*/
		placeToBoard(cBoard, iReplace, cPlayer);
		
		/*Update the board visually*/
		gameUpdate(cBoard, cPlayer);
		
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1){
			showAbilityUsed(1);
			printf(" Replaced opponent's symbol.\n");
		}
		else
			strcpy(strGameStatus, "1Replaced opponent's symbol.");
	}
	else {
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1)
			printf("There is no opponent's symbol to replace, hence this ability has no effect.\n");
		else
			strcpy(strGameStatus, "1There is no opponent's symbol to replace, hence ReSymbol has no effect.");
	}
}
void ability3(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1){
	/* Replace all four corners and the middle space with BLANK */
	placeToBoard(cBoard, 1, BLANK);
	placeToBoard(cBoard, 5, BLANK);
	placeToBoard(cBoard, 21, BLANK);
	placeToBoard(cBoard, 25, BLANK);
	placeToBoard(cBoard, 13, BLANK);
	
	/*Update the board visually*/
	gameUpdate(cBoard, cPlayer);
	
	/*If the player has an extra turn, proceed to normally print message; else copy the message*/
	if(iAbility1){
		showAbilityUsed(2);
		printf("Cleared all corners and middle space.\n");
	}
	else
		strcpy(strGameStatus, "1Cleared all corners and middle space.");
}
void ability4(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1){
	
	/*iOccupied is for checking of 2 occupied spaces or more by player */
	int iSelectedRow, iSelectedType, iHorizontal=0, iVertical=0, iDiagonal=0, iOccupied, iLoop, iLoop2; /*iPlace, iPlaceLimit=2;*/
	char cOpponent;
	
	/*If there's atleast 1 row that has 2 places occupied by the player, set the respective flag to true*/
	if(getHorizontalRow(cBoard,cPlayer,2)>=2)
		iHorizontal=1;
	if(getVerticalRow(cBoard,cPlayer,2)>=2)
		iVertical=1;
	if(getDiagonalRow(cBoard,cPlayer,2)>=2)
		iDiagonal=1;
		
	showAbilityUsed(3);
	/*If there's atleast 1 row that has 2 places occupied by the player, proceed to use the ability; else print an error message*/
	if(iHorizontal || iVertical || iDiagonal){
		
		getOpponent(cPlayer, &cOpponent);
		
		/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
			-Input within given choices
		*/
		do{
			colorWhite();
			printf("\n > Select type of row [");
			if(iHorizontal){
				colorGreen();
				printf("1");
				colorWhite();
				printf("-horizontal ");
			}
			if(iVertical){
				colorGreen();
				printf("2");
				colorWhite();
				printf("-vertical ");
			}
			if(iDiagonal){
				colorGreen();
				printf("3");
				colorWhite();
				printf("-diagonal ");
			}
			printf("]: ");
			scanf("%d", &iSelectedType);
						
			colorRed();
			if(iSelectedType <1 || iSelectedType > 3 || (iSelectedType==1 && !iHorizontal) || (iSelectedType==2 && !iVertical) || (iSelectedType==3 && !iDiagonal))
				printf(" Enter number from choices only.\n");
			formatReset();
		}while (iSelectedType <1 || iSelectedType > 3 || (iSelectedType==1 && !iHorizontal) || (iSelectedType==2 && !iVertical) || (iSelectedType==3 && !iDiagonal));
	
		switch (iSelectedType){
			case 1:
				/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
					-Input within 1-5
					-Input has atleast 2 spaces the player occupies on that horizontal row
				*/
				do{
					colorWhite();
					printf("\n > Select row to clear opponent's symbols. [1-5]: ");
					scanf("%d", &iSelectedRow);
					
					/*Check if the selected horizontal row has 2 spaces the player occupies*/
					for(iLoop=0, iOccupied=0; iLoop<5; iLoop++)
					{
						if(cBoard[iSelectedRow-1][iLoop]==cPlayer)
							iOccupied++;
					}
					
					colorRed();
					if(iSelectedRow <1 || iSelectedRow > 5)
						printf(" Enter number from 1 to 5 only.\n");
					else if(iOccupied<2)
						printf(" Enter a row number with 2 spaces you occupy.\n");
					formatReset();
				}while (iSelectedRow <1 || iSelectedRow > 5 || iOccupied<2);
				
				/*Clear opponents symbol on selected horizontal row*/
				for(iLoop=0; iLoop<5; iLoop++)
				{
					if(cBoard[iSelectedRow-1][iLoop]==cOpponent)
						cBoard[iSelectedRow-1][iLoop]=BLANK;
				}
				break;
			case 2:
				/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
					-Input within 1-5
					-Input has atleast 2 spaces the player occupies on that vertical row
				*/
				do{
					colorWhite();
					printf("\n > Select row to clear opponent's symbols. [1-5]: ");
					scanf("%d", &iSelectedRow);
					
					/*Check if the selected vertical row has 2 spaces the player occupies*/
					for(iLoop=0, iOccupied=0; iLoop<5; iLoop++)
					{
						if(cBoard[iLoop][iSelectedRow-1]==cPlayer)
							iOccupied++;
					}
					
					colorRed();
					if(iSelectedRow <1 || iSelectedRow > 5)
						printf(" Enter number from 1 to 5 only.\n");
					else if(iOccupied<2)
						printf(" Enter a row number with 2 spaces you occupy.\n");
					formatReset();
				}while (iSelectedRow <1 || iSelectedRow > 5 || iOccupied<2);
				
				/*Clear opponents symbol on selected vertical row*/
				for(iLoop=0; iLoop<5; iLoop++)
				{
					if(cBoard[iLoop][iSelectedRow-1]==cOpponent)
						cBoard[iLoop][iSelectedRow-1]=BLANK;
				}
				break;
				
			case 3:
				/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
					-Input either 1 or 2
					-Input has atleast 2 spaces the player occupies on that diagonal row
				*/
				do{
					colorWhite();
					printf("\n > Select row to clear opponent's symbols. [1-2]: ");
					scanf("%d", &iSelectedRow);
					
					/*Check if the selected diagonal row has 2 spaces the player occupies*/
					switch(iSelectedRow){
						case 1: /*Count how many spaces occupied by the player on diagonal row (descending)*/
							for(iOccupied=0,iLoop=0; iLoop<5; iLoop++){
								if(cBoard[iLoop][iLoop]==cPlayer)
									iOccupied++;
							}
							break;
						case 2: /*Count how many spaces occupied by the player on diagonal row (ascending)*/
							for(iOccupied=0,iLoop=0, iLoop2=4; iLoop<5, iLoop2>=0; iLoop++, iLoop2--)
							{
								if(cBoard[iLoop][iLoop2]==cPlayer)
									iOccupied++;
							}
							break;
					}
						
					colorRed();					
					if(iSelectedRow <1 || iSelectedRow > 2)
						printf(" Enter number either 1 or 2 only.\n");
					else if(iOccupied<2)
						printf(" Enter a row number with 2 spaces you occupy.\n");
					formatReset();
				} while (iSelectedRow <1 || iSelectedRow > 2 || iOccupied<2);
				
				/*Clear opponents symbol on selected diagonal row*/
				switch(iSelectedRow){
					case 1:
						for(iOccupied=0,iLoop=0; iLoop<5; iLoop++){
							if(cBoard[iLoop][iLoop]==cOpponent)
								cBoard[iLoop][iLoop]=BLANK;
						}
						break;
					case 2:
						for(iOccupied=0,iLoop=0, iLoop2=4; iLoop<5, iLoop2>=0; iLoop++, iLoop2--)
						{
							if(cBoard[iLoop][iLoop2]==cOpponent)
								cBoard[iLoop][iLoop2]=BLANK;
						}
						break;
				}
				break;
		}
		
		
		/*This part updates the board visually*/
		gameUpdate(cBoard, cPlayer);
		
		if(iAbility1){
			showAbilityUsed(3);
			printf("Cleared opponent's symbol\n");
		}
		else
			strcpy(strGameStatus, "1Cleared opponent's symbol");
	}
	else{
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1)
			printf("You don't have a row with 2 spaces occupied, hence this ability will have no effect.\n");
		else
			strcpy(strGameStatus, "1You don't have a row with 2 spaces occupied, hence Free Row will have no effect.");
	}
}

void ability5(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1){
	int iPlace=0, iPlaceLimit=3;
	
	do{
		/*Check if the PLAYER has won (when the opponent accidentally/purposely completed 5 spaces for the player) */
		if(!gameCheck(cBoard, cPlayer)){
			showAbilityUsed(4);
			colorGreen();
			printf(" - (%d placement/s left)\n", iPlaceLimit);
			/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
				-Input space within 1-25
				-Input space isn't occupied
			*/
			do{
				
				colorWhite();
				
				/*Ask opponent*/
				printf(" Where does ");
				if(cPlayer==PLAYER1){
					colorPurple();
					printf("PLAYER 2 (O)");
				}
				else{
					colorCyan();
					printf("PLAYER 1 (X)");
				}
				colorWhite();
				printf(" want to place? [1-25]: ");
				scanf("%d", &iPlace);	
				
				colorRed();
				if(iPlace <1 || iPlace > 25)
					printf(" Enter number from 1 to 25 only.\n");
				else if(getFromBoard(cBoard, iPlace) != BLANK)
					printf(" Place is already occupied, enter other number from 1 to 25.\n");
				formatReset();
			}while (iPlace <1 || iPlace >25 || getFromBoard(cBoard, iPlace) != BLANK);
			
			iPlaceLimit--;
			
			/* Places the symbol on the board but visually not updated yet */
			placeToBoard(cBoard, iPlace, cPlayer);
			
			/* This part updates the board visually */
			gameUpdate(cBoard, cPlayer);
		}
		else /*If player has won, end this whole ability function by assigning 0 to iPlaceLimit */
			iPlaceLimit=0;	
	} while(iPlaceLimit > 0);
	
}
void ability6(char cBoard[][SIZE], char cPlayer, char strGameStatus[], int iAbility1){
	int iSpaces, iRemove, iCount, iPlayer1Occupied=0, iPlayer2Occupied=0;
	char cOpponent;
	
	/*Count players occupied spaces*/
	for(iSpaces=0; iSpaces<=25; iSpaces++)
	{
		if(getFromBoard(cBoard, iSpaces)==PLAYER1)
			iPlayer1Occupied++;
		
		if(getFromBoard(cBoard, iSpaces)==PLAYER2)
			iPlayer2Occupied++;
		
	}
	
	getOpponent(cPlayer, &cOpponent);
	
	/*Calculate if the opponent has more spaces*/
	if(cPlayer==PLAYER1) 
		iCount= iPlayer2Occupied-iPlayer1Occupied;
	else
		iCount=	iPlayer1Occupied-iPlayer2Occupied;
	
	/*If the opponent has more spaces, proceed to use the ability; else print an error message*/
	if(iCount > 0)
	{
		do{			
			showAbilityUsed(5);
			colorGreen();
			printf(" - (%d left)", iCount);
			/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
				-Input space within 1-25
				-Input space has opponent's symbol
			*/
			do{
				colorGreen();
				printf("\n > Where do you want to remove? [1-25]: ");
				scanf("%d", &iRemove);	
				
				colorRed();
				if(iRemove <1 || iRemove > 25)
					printf(" Enter number from 1 to 25 only.\n");
				else if(getFromBoard(cBoard, iRemove) != cOpponent)
					printf(" Enter a number that the opponent occupies.\n");
				formatReset();		
			} while(iRemove <1 || iRemove >25 || getFromBoard(cBoard, iRemove) != cOpponent);
			
			iCount--;
			
			/*Replaces the opponent's symbol with blank*/
			placeToBoard(cBoard, iRemove, BLANK);
			
			/* This part updates the board visually */
			gameUpdate(cBoard, cPlayer);
			
		} while(iCount>0);
	}
	else{	
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1){
			showAbilityUsed(5);		
			printf("The opponent doesn't have more spaces occupied, hence this ability will have no effect.\n");
		}
		else
			strcpy(strGameStatus, "1The opponent doesn't have more spaces occupied, hence Aequalis will have no effect.");
	}
}
void ability7(int iOpponentAbilities[], int iNumOfAbilities, int iIsAbilityHidden, char strGameStatus[], int iAbility1){
	int iAbility, iLoop, iAvailableAbilities=0;
	char strAbility[15] = "";
	
	/*Count opponent's available abilities*/
	for(iLoop=0; iLoop<iNumOfAbilities; iLoop++)	
		if(iOpponentAbilities[iLoop] != 0)
			iAvailableAbilities++;
			
	showAbilityUsed(6);
	/*If the opponent has an available ability or more, proceed to use this ability; else print an error message*/
	if(iAvailableAbilities!=0){
		/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
			-Input within 1 to no. of abilities
			-Input ability that exist from opponent
		*/
		do{
			colorWhite();
			printf("\n Enter which ability to remove from opponent [");
			
			/*Show opponent's available abilities*/
			for(iLoop=0; iLoop < iNumOfAbilities; iLoop++){
				if(iOpponentAbilities[iLoop] !=0){
					if(iIsAbilityHidden)
						strcpy(strAbility, "???");
					else
						getAbilityName(iOpponentAbilities[iLoop]-1, strAbility);
					colorGreen();
					printf("%d", iLoop+1);
					formatReset();
					
					printf("-%s; ", strAbility);
				}
			}
			printf("]: ");
			scanf("%d", &iAbility);	
			
			colorRed();
			if(iAbility <1 || iAbility > iNumOfAbilities)
				printf(" Enter number from the choices only.\n");
			else
				if(iAbility!=0)
					if(iOpponentAbilities[iAbility-1] == 0)
						printf(" Ability doesn't exist, select another ability.\n");
			
			formatReset();		
		} while(iAbility <1|| iAbility >iNumOfAbilities || iOpponentAbilities[iAbility-1] == 0);
		
		iOpponentAbilities[iAbility-1] =0;
		
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1)
			printf(" Removed an ability from opponent.\n");
		else
			strcpy(strGameStatus, "1Removed an ability from opponent.");
	}
	else{
		/*If the player has an extra turn, proceed to normally print message; else copy the message*/
		if(iAbility1)
			printf("The opponent has no abilities left, hence this ability will have no effect.");
		else
			strcpy(strGameStatus, "1The opponent has no abilities left, hence Vanish will have no effect.");
	}
}
int ability8(char cPlayer, int* iAbility){
	int cChoice;
	
	/*DO-WHILE loop until the player enters a correct letter that satisfies the condition:
		-Input is Y/y or N/n
	*/
	do {

		printf("\n\tWould ");
		if(cPlayer==PLAYER1){
			colorPurple();
			printf("PLAYER 2");
			formatReset();
		}
		else{
			colorCyan();
			printf("PLAYER 1");
			formatReset();
		}
		printf(" like to counter the ability? [y/n]: ");
		
		cChoice = getche();
		if(cChoice != 'Y' && cChoice != 'N' &&  cChoice != 'y' &&  cChoice != 'n'){
			colorRed();
			printf("\n\tPlease choose Y or N only.");
			formatReset();
		}
	} while ( cChoice != 'Y' && cChoice != 'N' &&  cChoice != 'y' && cChoice != 'n');
	
	/*
		1 means TRUE and 0 means FALSE, 
		so if the opponent chose y/Y, it will return TRUE 
		which will skip the switch statement on gameUseAbility
	*/
	if(cChoice == 'y' || cChoice == 'Y'){
		if(cPlayer==PLAYER1){
			colorPurple();
			printf("\n\tPLAYER 2 has countered ");
			colorCyan();
			printf("PLAYER 1's ");
			printf("ability.\n");
			formatReset();
		}
		else{
			colorCyan();
			printf("\n\tPLAYER 1 has countered ");
			colorPurple();
			printf("PLAYER 2's ");
			printf("ability.\n");
			formatReset();
		}
		/*Counter ability of the opponent is used so assign 0*/
		*iAbility=0;
		return 1;
	}
	else{
		printf("\n");
		return 0;
	}
}


/*----------------------------INTRO OR START FUNCTIONS----------------------------*/
/*Clear screen and show title*/
void showGameTitle()
{
	clearScreen();
	colorYellow();
	printf("\t\tCreated by Aaron Palpallatoc\n");
	printf(" ___ _ _ _         _____ _       _____           _____ \n");
	printf("/ __(_) | |_  _ __|_   _(_)__ __|_   _|_ _ __ __|_   _|__  ___ \n");
	printf("\\__ \\ | | | || |___|| | | / _|___|| |/ _` / _|___|| |/ _ \\/ -_)\n");
	printf("|___/_|_|_|\\_, |    |_| |_\\__|    |_|\\__,_\\__|    |_|\\___/\\___|\n");
	printf("           |__/ \n");
	formatReset();
}

/*Show game title, list abilities, and prompt user*/
void showAbilities(){
	int iChoice;
	
	showGameTitle();
	listAbilities(0);
	printf("\n\n\t\t[1] Show how to play \n\t\t[2] Return to main menu\n\n");
	
	if(promptUser()==1)
		showHowToPlay();
	else
		showMenu();
}
/*List abilities*/
void listAbilities(int iShowNum){
	int iLoop;
	char strAbility[15] ="";
	char sDescription[8][420] = {
		"Player gets two turns after using their normal turn to use this ability.",
		"Player chooses a space occupied by an opponent, and then replaces the opponent's symbol with their own.",
		"Removes all symbols from the four corners and center of the grid.",
		"Player chooses a row with 2 spaces they occupy, and then all the symbols of the opponent within the same\n\t\trow are removed. (Horizontal: 1 is first row, etc.; Vertical: 1 is first column, etc.; Diagonal: 1 is\n\t\tdescending line or row, etc.)",
		"Lets the opponent choose 3 unoccupied spaces for the player.",
		"If the opponent occupies more spaces than the player, the player can select spaces occupied by the\n\t\topponent and make them unoccupied until they both have equal number of spaces.",
		"Player chooses and removes an unused ability from the opponent's abilities.",
		"When an opponent plays an ability, the player with the counter ability will be asked by the computer if\n\t\tthey would like to counter it, and if they agree, the opponent will not be able to use the ability,\n\t\tcan no longer use that ability, and will instead take a normal turn. This ability can only be used\n\t\tduring the opponent's turn. (Counter does nothing when selected after being asked 'Use an ability?')"
	};
	
	printf("\n LIST OF ABILITIES: ");
	underline();
	printf("(All the abilities are only used ONCE. If used wrongly, it will END your turn!)\n");
	formatReset();
	
	for (iLoop=0; iLoop<8; iLoop++){
		getAbilityName(iLoop, strAbility);
		printf(" %d. ",iLoop+1);
		colorGreen();
		printf("%s",strAbility);
		formatReset();
		printf(" - %s\n", sDescription[iLoop]);	
	}
	
}

/*Show game title and prompt user*/
void showMenu(){
	showGameTitle();
	printf("\n\n\t\t\t\b\b[1] Start game\n\t\t\t\b\b[2] How to play\n\n");
	
	if(promptUser()==1)
		gameStart();
	else 
		showHowToPlay();
}
/*Clear screen, show the placement numbers and instructions, and prompt user*/
void showHowToPlay(){
	
	clearScreen();
	showPlacementNumbers();
	colorYellow();
	printf("\n\n\t\tWelcome to SILLY TIC-TAC-TOE!");
	formatReset();
	printf("\nThe game proceeds similarly to normal tic-tac-toe, where each player (starting with ");
	colorCyan();
	printf("Player 1 - X");
	formatReset();
	printf("),");
	printf("\ntakes turns selecting an unoccupied space, except there are 25 spaces, and a player needs to occupy");
	colorYellow();
	printf("\nfive (5) spaces ");
	formatReset();
	printf("in a horizontal, vertical or diagonal row to win. Instead of taking their usual turn,");
	printf("\nthey may use one of their chosen ");
	colorGreen();
	printf("abilities");
	formatReset();
	printf(". Once a player uses an ability, that player cannot use that");
	printf("\nability again. If you see this ");
	colorBlue();
	printf("color");
	formatReset();
	printf(", it is either a normal or an error message after an ability is used.");
	printf("\n\nAs you can see the board above, the numbers represent the location on where the X or O will be placed.");
	printf("\nFor example, Player 1 inputted 20, the X will be placed on the 4th row 5th column.");
	
	printf("\n\n\t\t[1] Show types of abilities\n\t\t[2] Return to main menu\n\n");
	
	if(promptUser()==1)
		showAbilities();
	else
		showMenu();
}

/* ----------------------------MISCELLANEOUS FUNCTIONS----------------------------*/

/*Get the opponent of the given player*/
void getOpponent(char cPlayer, char *cOpponent){
	if(cPlayer==PLAYER1)
		*cOpponent=PLAYER2;
	else
		*cOpponent=PLAYER1;
}

/*Copy string depending on the iLoop (used on gameChooseAbility only)*/
void getOrdinalNumber(int iLoop, char strOrdinalNum[]){
	switch(iLoop){
		case 0:
			strcpy(strOrdinalNum,"first ability");
			break;
		case 1:
			strcpy(strOrdinalNum,"second ability");
			break;
		case 2:
			strcpy(strOrdinalNum,"third ability");
			break;
		case 3:
			strcpy(strOrdinalNum,"fourth ability");
			break;
		case 4:
			strcpy(strOrdinalNum,"fifth ability");
			break;
		case 5:
			strcpy(strOrdinalNum,"sixth ability");
			break;
		case 6:
			strcpy(strOrdinalNum,"seventh ability");
		
		case 7:
			strcpy(strOrdinalNum,"eight ability");
			break;
	}
	
}

/*Copy ability name depending on the iLoop*/
void getAbilityName(int iLoop, char strAbilityName[]){
	switch(iLoop){
		case 0:
			strcpy(strAbilityName,"AnotherTwo");
			break;
		case 1:
			strcpy(strAbilityName,"ReSymbol");
			break;
		case 2:
			strcpy(strAbilityName,"DI5APPEAR");
			break;
		case 3:
			strcpy(strAbilityName,"Free row");
			break;
		case 4:
			strcpy(strAbilityName,"Unlucky3");
			break;
		case 5:
			strcpy(strAbilityName,"Aequalis");
			break;
		case 6:
			strcpy(strAbilityName,"Vanish");
			break;
		case 7:
			strcpy(strAbilityName,"Counter");
			break;
	}
	
}

/*Asks user to choose between 1 and 2 only and return the choice*/
int promptUser(){
	int iChoice;
	
	/*DO-WHILE loop until the player enters a correct number that satisfies the condition:
		-Input is 1 or 2	
	*/
	do{
		printf("\t\t\t\b\b\bChoose [1 or 2]: ");
		scanf("%d", &iChoice);
		if(iChoice < 1 || iChoice > 2){
			colorRed();
			printf("\t\t\a Please choose properly.\n");
			formatReset();
		}

	}while(iChoice < 1 || iChoice > 2);
	
	return iChoice;
}

/*Removes all elements showed on screen*/
void clearScreen(){
	system("CLS");
}

/*Show board with designated number on each space*/
void showPlacementNumbers(){
	int iRow, iCol, iNum;
	
	printf("\t\t\t\b\b\b[NUMBER PLACEMENTS]");
	printf("\n\t\t\t\b\b\b\b---------------------");
	for(iRow=0; iRow<5;iRow++)
	{		
		printf("\n\t\t\t\b\b\b\b|");
		for(iCol=0; iCol<5; iCol++)
		{
			if(iRow == 0)
				printf("%2d |" , iCol+1);
			if(iRow == 1)
			{
				if(iCol>=0 && iCol<4)
				printf("%2d |" , iCol+6);
				else
					printf("% 2d|" , iCol+6);
			}
			if(iRow == 2)
			{
				printf("% 2d|" , iCol+11);
			}
			if(iRow == 3)
			{
				printf("% 2d|" , iCol+16);
			}
			if(iRow == 4)
			{
				printf("% 2d|" , iCol+21);
			}
		}
		printf("\n\t\t\t\b\b\b\b---------------------");
	}
}
