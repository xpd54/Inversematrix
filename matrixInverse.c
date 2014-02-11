// All rights for edit is reserve to Ravi Prakash y10uc256 LNMIIT
//Tested on gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5) 
#include"fractionNumberFunction.h"
int main()
{

/*##################### input taking ####################*/
/* 1.Try to avoid more space between two input in same row.
   2.Row should be end with ";" like for 3 x 3 matrix
   		1 2 3;
   		4 5 6;
   		7 8 9;
   3.matrix should be squre matrix so just put one number
   to denote the matrix size like 4 means 4 x 4.
*/


	int N,M,countM=0,countN=0,column,i,j,minusFlag=0;
	printf("Enter your marix size \n");
	scanf("%d",&N);
	column=4*((3*N+N-1)+5);
	char userInput[N][column];
	fractionNumber input[N][N];
	int count=N;
	while(count--)
	{
		scanf("%[^;]%*s",userInput[countM]);
		countM++;
	}
	count = N;
	/*uncomment to see user input in string formate*/
	/*while(count--)
	{
		printf("%s",userInput[countN]);
		countN++;
	}
	printf("\n");*/
	countN=0;
	countM=0;
	for(i=0;i<N;i++)
	{
		countN=0;
		int j=0,flag=0,flagSpace=0;
		char tempInput;
		input[countM][countN].num=0;
		input[countM][countN].den=0;
		while(1)
		{
			tempInput=userInput[i][j];
			if(tempInput == '-')
			{
				minusFlag=1;
			}
			if(tempInput>='0' && tempInput<='9')
			{
				flagSpace = 0;
				if(flag==0)
				{
					input[countM][countN].num=input[countM][countN].num*10+(tempInput-'0');
				}
				else
					input[countM][countN].den=input[countM][countN].den*10+(tempInput-'0');
			}
			if(tempInput == '/')
				flag=1;
			if(tempInput == ' ')
			{
				if(flag == 0 && flagSpace==0)
				{
					input[countM][countN].den=1;
				}
				if(flagSpace == 0)
				{	
					if(minusFlag==1)
					{
						input[countM][countN].num = -input[countM][countN].num;
						minusFlag=0;
					}
					countN++;
					input[countM][countN].num=0;
					input[countM][countN].den=0;
					flagSpace=1;
					flag=0;
				}
			}
			if((int)strlen(userInput[i])==j+1)
			{
				if(minusFlag==1)
				{
					input[countM][countN].num = -input[countM][countN].num;
					minusFlag=0;
				}
				if(flag!=1)
				input[countM][countN].den=1;
				countM++;
				break;
			}
			j++;
		}
	}
	
/*######### End of taking Input ############*/
	
/*########################### printing the user input ###############
  1.It will print the value in whole number not in fraction part
  2.If denominater in 1 it won't print denominater
*/
/*############## uncomment to see input in calculating array #############*/
	/*for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			print(input[i][j]);
		}
		printf("\n");
	}*/
	fractionNumber determinantOfMatrix;
/*############ Take determinant Of Matrix#######*/
	determinantOfMatrix=determinant(N,input);
	if(determinantOfMatrix.num == 0)
	{
		printf("Determinant Of Matrix is ZERO inverse not possible\n");
		return 0;
	}
	printf("\n");
/*############ convert matrix in adjoint form ############*/
	adjoint(N,input);
/*############  take transpose of matrix ################*/
	transpose(N,input);
/*############  Calculate inverse of matrix ##############*/
	inverseOfMatrix(N,determinantOfMatrix,input);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			print(input[i][j]);
		}
		printf("\n");
	}

}
