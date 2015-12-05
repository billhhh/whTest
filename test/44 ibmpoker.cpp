/* 
* 
* Date:2015-10-05
* 
*Author: Mainframe Master
*
*	 this program has modified by Bill Wang
*/

#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h> 

FILE *inputFile; /* This data type describes the input data set*/

int debug = 0; /* This flag controls extra debug data printed to */

typedef struct cards { 
	char cardvalue;
	char cardsuit; 
}; /* This struct (data structure) describes a */

struct cards p1cards[5]; 
struct cards p2cards[5];

///Part2 Modify
struct cards p3cards[5];
int p3SortedValues[5];
int p3Score;
int count3=0;

int p1SortedValues[5]; 
int p2SortedValues[5]; 

int p1Score; 
int p2Score; 

int RoyalFlushesCnt=0;
int StraightFlushesCnt=0;
int FourKindsCnt=0;
int FullHousesCnt=0;
int FlushesCnt=0;
int SWHtraightCnt=0;
int ThreeKindsCnt=0;
int TwoPairsCnt=0;
int OnePairsCnt=0;
int HighCardsCnt=0;

enum {TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK,
	QUEEN, KING, ACE}; 

enum {HIGHCARD=0, ONEPAIR, TWOPAIR, THREEKIND, STRAIGHT, FLUSH,
	FULLHOUSE, FOURKIND};

int main()
{ 
	printf("Hu Wang's Poker Program\n");
	printf("\n");

	int count1=0,count2=0;

	int isFlush(struct cards[]);
	int isStraight(int values[]); 
	int getValue(char val); 
	char getPrint(int val); 
	void countCards(int values[], int sortedValues[], int frequency[]); 
	int scoreHand(struct cards[],int sortedValues[]); 
	int chooseWinner(int values0[],int score0, int values1[], int score1);

	int i;
	char c; 

	//inputFile = fopen("DD:INPUT", "r"); 
	inputFile = fopen("pokerinput.txt", "r");
	if (inputFile == NULL)
	{ 
		printf("open error: %d/%s\n", errno, strerror(errno));
		exit(98); 
	} 

	while (fscanf(inputFile,
		"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",				///Part2 Modify
		&p1cards[0],&p1cards[1],&p1cards[2],&p1cards[3],&p1cards[4], 
		&p2cards[0],&p2cards[1],&p2cards[2],&p2cards[3],&p2cards[4],
		&p3cards[0],&p3cards[1],&p3cards[2],&p3cards[3],&p3cards[4]
	) != EOF) { /* The while statement reads a record and stores*/

		if (debug) 
		{ /* If the debug flag is enabled (that is, not */
			printf("Player 1: %.2s %.2s %.2s %.2s %.2s : ",
				&p1cards[0],&p1cards[1],&p1cards[2],&p1cards[3],&p1cards[4]);
		}/* End of "if (debug)"*/
		p1Score = scoreHand(&p1cards[0],&p1SortedValues[0]); 

		if (debug) { /* Do the same thing for player 2 now */
			printf("Player 2: %.2s %.2s %.2s %.2s %.2s : ",
				&p2cards[0],&p2cards[1],&p2cards[2],&p2cards[3],&p2cards[4]);
		}/* End of "if (debug)"*/
		p2Score = scoreHand(&p2cards[0],&p2SortedValues[0]); 

		p3Score = scoreHand(&p3cards[0],&p3SortedValues[0]);	///Part2 Modify

		if (debug) 
		{ /* If we're in debugging mode, display the scores */
			printf("%d:%d; ",p1Score,p2Score); 
		}

		if (chooseWinner(&p1SortedValues[0],p1Score, ///Part2 Modify
			&p2SortedValues[0],p2Score) == 1) 
		{/* If player 1 is the winner, display an*/
			//printf("Player 1 wins!\n");
			//count1++;

			if(chooseWinner(&p1SortedValues[0],p1Score, ///Part2 Modify
				&p3SortedValues[0],p3Score) == 1)
			{
				//p1 win
				count1++;
			}

			else
			{
				count3++;
			}
		}
		else
		{
			//printf("Player 2 wins!\n");
			//count2++;

			if(chooseWinner(&p2SortedValues[0],p2Score, ///Part2 Modify
				&p3SortedValues[0],p3Score) == 1)
			{
				//p2 win
				count2++;
			}

			else
			{
				count3++;
			}
		}

		memset(p1SortedValues, 0, sizeof(p1SortedValues)); 
		memset(p2SortedValues, 0, sizeof(p2SortedValues));
		memset(p3SortedValues, 0, sizeof(p3SortedValues)); ///Part2 Modify

		/* Suck up anything left at the end of the current record and */
		/* discard*/
		do
		{ 
			c = fgetc(inputFile); 
		} while ( c != '\n'); 
	} /* End of loop that processes each record */

	/////Output Report

	int totalnum = count1+count2+count3;	 ///Part2 Modify			
	printf("Summary:\n");
	printf("Total games: %d\n",totalnum);
	int t1=(int)((double)count1*100/totalnum+0.5);
	printf("Player 1 total wins: %d Percentage %d%%\n",count1,t1);
	int t2=(int)((double)count2*100/totalnum+0.5);
	printf("Player 2 total wins: %d Percentage %d%%\n",count2,t2); ///Part2 Modify
	int t3=(int)(count3*100.0/totalnum+0.5);
	printf("Player 3 total wins: %d Percentage %d%%\n\n",count3,t3);  ///Part2 Modify

	int totalhands = RoyalFlushesCnt+StraightFlushesCnt+FourKindsCnt+FullHousesCnt+
		FlushesCnt+SWHtraightCnt+ThreeKindsCnt+TwoPairsCnt+OnePairsCnt+HighCardsCnt;
	printf("Hand Occurrences:\n");
	printf("Total Hands Analyzed: %d\n",(count1+count2+count3)*3); ///Part2 Modify
	printf("Royal Flushes: %d (%d%%)\n",RoyalFlushesCnt,(int)(RoyalFlushesCnt*100.0/totalhands+0.5));
	printf("Straight Flushes: %d (%d%%)\n",StraightFlushesCnt,(int)(StraightFlushesCnt*100.0/totalhands+0.5));
	printf("Four of a Kinds: %d (%d%%)\n",FourKindsCnt,(int)(FourKindsCnt*100.0/totalhands+0.5));
	printf("Full Houses: %d (%d%%)\n",FullHousesCnt,(int)(FullHousesCnt*100.0/totalhands+0.5));
	printf("Flushes: %d (%d%%)\n",FlushesCnt,(int)(FlushesCnt*100.0/totalhands+0.5));
	printf("Straights: %d (%d%%)\n",SWHtraightCnt,(int)(SWHtraightCnt*100.0/totalhands+0.5));
	printf("Three of a Kinds: %d (%d%%)\n",ThreeKindsCnt,(int)(ThreeKindsCnt*100.0/totalhands+0.5));
	printf("Two Pairs: %d (%d%%)\n",TwoPairsCnt,(int)(TwoPairsCnt*100.0/totalhands+0.5));
	printf("One Pairs: %d (%d%%)\n",OnePairsCnt,(int)(OnePairsCnt*100.0/totalhands+0.5));
	printf("High Cards: %d (%d%%)\n",HighCardsCnt,(int)(HighCardsCnt*100.0/totalhands+0.5));

	/********************************************************************/
	/* Close input file */
	/********************************************************************/
	fclose(inputFile);
	/********************************************************************/
	/* Return from the program*/
	/********************************************************************/
	return 0; 
} 

int isFlush(struct cards hand[])
{ 
	if (hand[0].cardsuit==hand[1].cardsuit &
		hand[0].cardsuit==hand[2].cardsuit &
		hand[0].cardsuit==hand[3].cardsuit &
		hand[0].cardsuit==hand[4].cardsuit) 
		return 1; 
	return 0; 
} 
		
int isStraight(int values[])
{ 
	int i;
	int cardCount;/* How many consecutive neighboring */
	/* entries in the values array have been*/
	/* found with a value of 1. If we get up*/
	/* to five, then we know the hand is a*/
	/* straight.*/

	if (values[ACE]==1) /* Account for the A-2-3-4-5 straight */
		cardCount = 1;
	else
		cardCount = 0;

	for (i=0;i<=ACE;i++)
	{ 
		if (values[i]==1) 
		{ 
			cardCount++; 
			if (cardCount == 5)
				return 1;
		}
		else 
			cardCount = 0;/* Back to zero cards in a row*/ 
	}
	return 0;
}

int getValue(char val) 
{

	if (val=='A')
		return ACE;
	if (val=='K')
		return KING; 
	if (val=='Q')
		return QUEEN;
	if (val=='J')
		return JACK; 
	if (val=='T')
		return TEN;
	if (val=='9')
		return NINE; 
	if (val=='8')
		return EIGHT;
	if (val=='7')
		return SEVEN;
	if (val=='6')
		return SIX;
	if (val=='5') 
		return FIVE;
	if (val=='4') 
		return FOUR;
	if (val=='3') 
		return THREE; 
	if (val=='2') 
		return TWO; 
	return 0; 
} 

char getPrint(int val)
{ 

	if (val==ACE) 
		return 'A'; 
	if (val==KING)
		return 'K'; 
	if (val==QUEEN) 
		return 'Q'; 
	if (val==JACK)
		return 'J'; 
	if (val==TEN) 
		return 'T'; 
	if (val==NINE)
		return '9'; 
	if (val==EIGHT) 
		return '8'; 
	if (val==SEVEN) 
		return '7'; 
	if (val==SIX) 
		return '6'; 
	if (val==FIVE)
		return '5'; 
	if (val==FOUR)
		return '4'; 
	if (val==THREE) 
		return '3'; 
	if (val==TWO) 
		return '2'; 
	return 'X'; 
} 

//output sortedValues[] and frequency[]
void countCards(int values[], int sortedValues[], int frequency[])
{ 

	int i,j;

	j = 0;
	for (i=ACE;i>=TWO;i--)
	{ 
		if (values[i]==4) 
		{ 
			/* Player got a 4 of a kind */
			frequency[j] = 4; 
			sortedValues[j] = i;
			j++;
		} 
	} 

	for (i=ACE;i>=TWO;i--)
	{ 
		if (values[i]==3) 
		{ 
			/* Player got a 3 of a kind */
			frequency[j] = 3; 
			sortedValues[j] = i;
			j++;
		} 
	} 
	for (i=ACE;i>=TWO;i--)
	{ 
		if (values[i]==2) 
		{ 
			frequency[j] = 2; 
			sortedValues[j] = i;
			j++;
		} 
	} 
	for (i=ACE;i>=TWO;i--)
	{ 
		if (values[i]==1) 
		{ 
			frequency[j] = 1; 
			sortedValues[j] = i;
			j++;
		} 
	} 
	return; 
} 

// calc score
int scoreHand(struct cards hand[], int sortedValues[])
{ 
	int handVal = 0;/* Return value - score for the hand*/
	int i;
	int values[15] = { 0 }; 

	int frequency[5] = { 0 }; /* Frequency array - how many times */
	/* each entry in the sortedValues array */
	/* appears in the hand. */

	for (i=0;i<=sizeof(hand);i++) /* For each card in the hand, tick*/
		/* up the entry in the values array that*/
			/* corresponds to the matching card rank. */
	{ 
		values[getValue(hand[i].cardvalue)]++;
	} 

	countCards(&values[0],&sortedValues[0],&frequency[0]); 

	//judge situation one by one
	if (isStraight(&values[0])) 
	{ 
		handVal += STRAIGHT;
		if (isFlush(&hand[0]))
		{ 
			//FlushesCnt++;
			handVal += FLUSH; 
			if (debug)
				printf("Straight Flush, high card %c",
				getPrint(sortedValues[0]));
			////////!!!could be royal flush here
			if (1 == values[14])
			{
				RoyalFlushesCnt++;
			}
			else
			{
				StraightFlushesCnt++;
			}
		} 
		else
		{
			SWHtraightCnt++;
			if (debug)
				printf("Straight, high card %c",getPrint(sortedValues[0])); 
		}
	} 
	else if (isFlush(&hand[0])) 
	{ 
		//normal flush
		FlushesCnt++;
		handVal += FLUSH; 
		if (debug)
			printf("Flush, high card %c",getPrint(sortedValues[0]));
	} 

	if (frequency[0]==4)
	{ 
		FourKindsCnt++;
		handVal += FOURKIND;
		if (debug)
			printf("Four of a kind %c",getPrint(sortedValues[0]));
	} 
	else if (frequency[0]==3) 
	{ 
		if (frequency[1]==2)
		{ 
			FullHousesCnt++;
			handVal += FULLHOUSE; 
			if (debug)
				printf("Full house %cs and %cs",getPrint(sortedValues[0]),
				getPrint(sortedValues[1]));
		} 
		else
		{ 
			ThreeKindsCnt++;
			handVal += THREEKIND; 
			if (debug)
				printf("Three of a kind %cs with a %c and a %c",
				getPrint(sortedValues[0]),getPrint(sortedValues[1]), 
				getPrint(sortedValues[2]));
		} 
	} 
	else if (frequency[0]==2) 
	{ 
		if (frequency[1]==2)
		{ 
			TwoPairsCnt++;
			handVal += TWOPAIR; 
			if (debug)
				printf("Two pair %cs and %cs with a %c",
				getPrint(sortedValues[0]),getPrint(sortedValues[1]), 
				getPrint(sortedValues[2]));
		} 
		else
		{ 
			OnePairsCnt++;
			handVal += ONEPAIR; 
			if (debug)
				printf("One pair %cs with a %c and a %c and a %c",
				getPrint(sortedValues[0]),getPrint(sortedValues[1]), 
				getPrint(sortedValues[2]),getPrint(sortedValues[3]));
		} 
	} 

	//high cards
	if (handVal == 0) 
	{ 
		HighCardsCnt++;
		if (debug)
			printf("High Card %c %c %c %c %c",getPrint(sortedValues[0]),
			getPrint(sortedValues[1]),getPrint(sortedValues[2]), 
			getPrint(sortedValues[3]),getPrint(sortedValues[4]));
	} 

	if (debug)
		printf("\n"); 
	/* Return the value (score) of the hand */
	return handVal; 

} 

/********************************************************************/
/**/
/* Subroutine chooseWinner determines which of two input players is */
/* the winner for a hand. */
/**/
/* If score0 differs from score1 that means the players had */
/* different hands (for example, a full house and a three of a*/
/* kind). If score0 is the same as score1 then the players had the*/
/* same hand (two straights, for example) and the ranks of the cards*/
/* must be analyzed.*/
/**/
/* If the first value/score pair is the winner, then the subroutine */
/* returns 1. */
/* If the second value/score pair is the winner, then the subroutine*/
/* returns 0. */
/**/
/********************************************************************/
int chooseWinner(int values0[],int score0,int values1[],int score1) 
{ 
	int i;

	if (score0 > score1) /* The first player had a better hand */
		return 1;
	else if (score1 > score0) /* The second player had a better*/
		/* hand */
		return 0;
	else /* The players had the same hand. Compare */
		/* values of the cards to determine */
		/* winner.*/
	{
		for (i=0;i<5;i++)
		{
			if (values0[i]>values1[i]) 
				return 1; 
			else if (values1[i]>values0[i])
				return 0; 
		}
	}
}