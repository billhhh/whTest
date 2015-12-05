#include <stdio.h>
#include <math.h>

int main()
{
	int count1=14,count2=16;

	int totalnum = count1+count2;				  
	printf("Summary:\n");
	printf("Total games: %d\n",totalnum);
	int t1=(int)(count1*100.0/totalnum+0.5);
	printf("Player 1 total wins: %d Percentage %d%%\n",count1,t1);
	int t2=(int)(count2*100.0/totalnum+0.5);
	printf("Player 2 total wins: %d Percentage %d%%",count2,t2);

	return 0;
}
