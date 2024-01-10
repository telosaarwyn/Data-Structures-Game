/*
	CCDSTRU MACHINE PROJECT
	TERM 2, AY 2022 - 2023
	NAMES:
		CATANGAY, Cassandra Jayne		S13
		CHUA, Judy						S13
		TELOSA, Arwyn Gabrielle			S12
*/

#include <stdio.h>
#include <stdlib.h>

int GameOver (int over, int turn, 
			  int sum1, int sum2)
{		
	/*	
		Turn is true 
		-----where Player 1 is turn=true
		THEORY: Turn that is true is player 1
		
		TEST CASE 1:
		if (3,3) = 8 --> Player 1 || Turn will be false
		   (2,3) = 9 --> Player 2 || Turn will be true
		   (3,1) = 5 --> Player 1 || Turn will be false
		   (1,1) = 4 --> Player 2 || Turn will be true
		   (2,2) = 2 --> Player 1 || Over will be true
					>>Over is biconditional kung (in my definition)
						isa sa mga players nakareach na ng 3 moves
						and if yung sum is less than or equal to 15,
						automatic nang mag-oover yung game 
		   		sum1 = 8+5+2 = 15
				All values in sum1 (8,5,2) are elements of W
				|(8,5,2)| = 3
				Satisfies 3rd if ng GameOver
				  SO A WINS ---> Player 1 Wins [*]
		
		TEST CASE 2:
		if (3,3) = 8 --> Player 1 || Turn will be false
		   (2,3) = 9 --> Player 2 || Turn will be true
		   (3,1) = 5 --> Player 1 || Turn will be false
		   (1,1) = 4 --> Player 2 || Turn will be true
		   (2,3) = 2 --> Player 1 || INVALID COORDINATES
		   							 Turn will be false
		   (3,2) = 2 --> Player 2 || Over will be true
		   			Player 2 reached 3 moves then check sum
		   			sum1 = 9+4+2 = 15
					All values in sum1 (9,4,2) are elements of W
					|(9,4,2)| = 3
					Satisfies 4th if ng GameOver
					  SO B WINS ---> Player 2 Wins [*]
					  
			REMEMBER: Turn == false -> Player 2 
			
		TEST CASE 3:
		if (2,2) = 1 --> Player 1 || Turn will be false*
		   (3,3) = 1 --> Player 2 || INVALID VALUE
		   							 Turn will be true
		   (2,3) = 8 --> Player 1 || Turn will be false*
		   (1,1) = 6 --> Player 2 || Turn will be true
		   (1,3) = 6 --> Player 1 || INVALID VALUE
		   							 Turn will be false
		   (2,3) = 7 --> Player 2 || INVALID COORDINATES
		   							 Turn will be true
		   (3,2) = 2 --> Player 1 || Over will be true*
		   			Player 1 reached 3 moves then check sum
		   			sum1 = 1+8+2 = 11
					All values in sum1 (1,8,2) are elements of W
					|(1,8,2)| = 3
					Satisfies 1th if ng GameOver
					  SO B WINS ---> Player 2 Wins [*]
				REASON: control na ni Player 2 yung board
						kasi wala nang magagawa si player 1
						kung naka 3 moves na siya, pero si
						player 2, kaya niya pang taasan si
						player 1
				IN THIS CASE: May 2 moves pa si Player 2
							  where yung first value niya is 6
							  {-, -, 3, 4, 5, -, 7, -, 9}
							  Pwede siya mag 3 and 4
							  HONESTLY---I think pataasan sila
							  ng sum or unang maka-15
				WHAT IF 
					-4 pinili ni Player 1 instead of 2?
					Player 1 reached 3 moves then check sum
		   			sum1 = 1+8+5 = 14
					All values in sum1 (1,8,5) are elements of W
					|(1,8,5)| = 3
					Satisfies 1th if ng GameOver
					  SO B WINS ---> Player 2 Wins [*]
					>>Kaya I think PATAASAN or unang maka-15
					   {-, 2, 3, 4, -, -, 7, -, 9}
					(bulok Player 2 is pinili niya pa 2 and 3
					pero hindi na rin naman siya makakapili
					kasi deafult winner na siya)
					
		TEST CASE 4:
		if (2,2) = 1 --> Player 1 || Turn will be false*
		   (3,3) = 1 --> Player 2 || INVALID VALUE
		   							 Turn will be true
		   (2,3) = 8 --> Player 1 || Turn will be false*
		   (1,1) = 6 --> Player 2 || Turn will be true
		   (1,3) = 6 --> Player 1 || INVALID VALUE
		   							 Turn will be false
		   (2,1) = 7 --> Player 2 || Turn will be true
		   (3,2) = 9 --> Player 1 || Turn will be false*
		      **REMEMBER:
		   			Player 1 may have reached 3 moves BUT check sum
		   			sum1 = 1+8+9 = 18
					All values in sum1 (1,8,9) are elements of W
					|(1,8,9)| = 3
					Invalid sum so OVER == false 
					kasi sum is not either less than 15 or equal to 15
				IN THIS CASE:
				   May pag-asa pa kasi si Player 2 para makapag-15
				   If Player 2 inputs 2, then player 2 wins automatically
		   (1,2) = 3 --> Player 2 || Turn will be true (sum is 16)
		   (1,3) = 4 --> Player 1 || Turn will be false
	*/
	
	if (over)
	{
		printf("\n************************************************************\n\n\t\t");
		if (turn && sum1 < 15)
			printf("Player 2 WINS >:-]\n");
		else if (turn == 0 && sum2 < 15)
			printf("Player 1 WINS >:-]\n");
		else if (turn && sum1 == 15)
			printf("Player 1 WINS >:-]\n");
		else if (turn == 0 && sum2 == 15)
			printf("Player 2 WINS >:-]\n");
		printf("\n************************************************************\n");
				
		return -1;
	}
	else
	{
		if (turn) 		//player 1 is true
			return 0; 
		else 			//player 2 is false
			return 1; 
	}
}

int NextPlayerMove (int smallPeg, int bigPeg[], 
					 int pos[], 
					 int nRow, int nCol, 
					 int free[][3], 
					 int okay, int next, 
					 int *pCount)
{	
	int i, j;
	int nFound = 0;
	
	for (j = 0; j < 9 && !nFound; j++)
		if (bigPeg[j] == smallPeg)
			nFound = 1;
	
	if (free[nRow][nCol] == 0 && nFound)
	{
		pos[*pCount] = smallPeg;  //lagay value for player
		free[nRow][nCol] = smallPeg; // occupied
		okay = 1;
		(*pCount)++;
		bigPeg[j-1] = 0; //peg used
		//put bigPeg here kasi nagiging 
		//invalid kapag space occupied yung nakalagay
	}
	
	else if (!nFound)
		printf("VALUE TAKEN. SORRY, NEXT PLAYER MOVE >:[\n");
	else
		printf("SPACE OCCUPIED. SORRY, NEXT PLAYER MOVE >:[\n");
		
	if (okay && nRow == 0)
		next = 1;
	
	else if (okay && nRow == 1)
		next = 1;


	else if (okay && nRow == 2)
		next = 1;
	
	if (okay && next && nCol == 0)
	{
		next = 0;
		okay = 0;			
	}
	
	else if (okay && next && nCol == 1)
	{
		next = 0;
		okay = 0;			
	}
	
	else if (okay && next && nCol == 2)
	{
		next = 0;
		okay = 0;		
	}
	
	return nFound;
}

void getInput (int *smallPeg, int *nRow, int *nCol)
{
	do
	{
		printf("INPUT ROW: ");
		scanf("%d", nRow);
		
		printf("INPUT COLUMN: ");
		scanf("%d", nCol);	
		
		//check if correct coordinates
		if ((*nRow < 1 || *nRow > 3) || (*nCol < 1 || *nCol > 3))
			printf("INVALID INPUT. KEEP IN MIND THIS IS A 3 BY 3 GRID\n\n");
	} while ((*nRow < 1 || *nRow > 3) || (*nCol < 1 || *nCol > 3));
	
	(*nRow)--; //deretso index na kagad kapag pinass
	(*nCol)--;
	
	do
	{
		printf("VALUE in POSITION: ");
		scanf("%d", smallPeg);
		//check if valid value
		if (*smallPeg < 1 || *smallPeg > 9)
			printf("INVALID INPUT. PLEASE INPUT VALUES 1 to 9.\n\n");	
	} while (*smallPeg < 1 || *smallPeg > 9);	
}
int main()
{
	int p1[9]; //grid
	int p2[9]; //grid
	int free[3][3]; //0 if free, 1 if occupied
	int bigPeg[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; //check if hindi na-uulit yung values 1-9
	int smallPeg; //input user value
	int okay, next, turn, over; //system initialization
	int nRow, nCol, nCount; //coordinates tas nCount for checking if 6 na yung moves
	int i, j, k; // i and j for loops, k for checking if valid smallPeg
	int W[9]; //Opposite of bigPeg
	int nVal; //count of W (must be 6)
	int p1Count, p2Count;
	int sum1, sum2;
	int newSum1, newSum2;
	
	okay = 0; //false
	next = 0; //false
	turn = 1; //true
	over = 0; //false since F <-> F V F == T
	nVal = 0; //counts valid inputs
	p1Count = 0;
	p2Count = 0;
	nCount = 0;
	sum1 = 0;
	sum2 = 0;
	newSum1 = 0;
	newSum2 = 0;
	
	for (i = 0; i < 3; i++)	
		for (j = 0; j < 3; j++)
			free[i][j] = 0;
	
	printf("WELCOME to CCDSTRU's GAME MACHINE PROJECT!\n");
	printf("[S12] Arwyn Gabrielle Telosa\n");
	printf("[S13] Cassandra Jayne Catangay\n");
	printf("[S13] Judy Chua\n");
	printf("\n*************************GAME START*************************\n");
	do
	{
		k = 0;
		
		if (nCount % 2 == 0) //Player 1
		{
			printf("\nPLAYER 1's TURN:\n");
			getInput(&smallPeg, &nRow, &nCol);
			k = NextPlayerMove(smallPeg, bigPeg, p1, nRow, nCol, free, okay, next, &p1Count);
			
			if (k) //This means smallPeg is a valid value
			{
				sum1 += p1[p1Count - 1]; //get sum of player 1
				W[nVal] = smallPeg; //W[] is basically the opposite of Peg
				//In specs, much complicated and unefficient since there are multiple values that are repeating
				//Addition to that, w will always be an element of W since smallPeg here is w
				nVal++;
			}
		}	
			
		else //if (nCount % 2 == 1)
		{
			printf("\nPLAYER 2's TURN:\n");
			getInput(&smallPeg, &nRow, &nCol);
			k = NextPlayerMove(smallPeg, bigPeg, p2, nRow, nCol, free, okay, next, &p2Count);
			
			if (k) //This means smallPeg is a valid value
			{
				sum2 += p2[p2Count - 1]; //get sum of player 2
				W[nVal] = smallPeg; //W[] is basically the opposite of Peg
				//In specs, much complicated and unefficient since there are multiple values that are repeating
				//Addition to that, w will always be an element of W since smallPeg here is w
				nVal++;
			}
		}
		nCount++;
		
		if ((p1Count == 3 && sum1 <= 15) || (p2Count == 3 && sum2 <= 15))
		{
			over = 1;
			newSum1 = sum1;
			newSum2 = sum2;
		}
		else if (p1Count > 3)
		{
			k = 0;
			
			for (i = 2; i < p1Count + 1 && !k; i++)
			{
				newSum1 = sum1 - p1[p1Count - i];
				
				if (newSum1 < 15)
				{
					over = 1;
					k = 1;
				}
			}
		}
		else if (p2Count > 3)
		{
			k = 0;
			
			for (i = 2; i < p2Count + 1; i++)
			{
				newSum2 = sum2 - p2[p2Count - i];
				
				if (newSum2 < 15)
				{
					over = 1;
					k = 1;
				}				
			}
		}
		
		turn = GameOver(over, turn, newSum1, newSum2); //return !turn
	} while (turn != -1);
	
	printf("\nCREATED BY: \n");
	printf("[S12] Arwyn Gabrielle Telosa\n");
	printf("[S13] Cassandra Jayne Catangay\n");
	printf("[S13] Judy Chua\n\n");
	printf("TO EXIT THE GAME, ");
	system("pause");
	return 0;
}
