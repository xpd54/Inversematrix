// All rights for edit is reserve to Ravi Prakash y10uc256 LNMIIT
// Tested on gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5) 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct fractionNumber
{
	int num,den;
};
typedef struct fractionNumber fractionNumber;
void print(fractionNumber input)
{
	if(input.den !=1)
	{
		printf("%d/%d ",input.num,input.den);
	}
	else
		printf("%d ",input.num);
	return;
}
int gcd(int a,int b)
{
	if(b==0)
		return a;
	else
	return gcd(b , a % b);
}

int lcm(int a,int b)
{
	return (a * b) / gcd(a,b);
}

fractionNumber add(fractionNumber a,fractionNumber b)
{
	int den=lcm(a.den,b.den);
	int aNum=(den / a.den) * a.num;
	int bNum=(den / b.den) * b.num;
	fractionNumber temp;
	temp.num=aNum + bNum;
	temp.den=den;
	int gcdOfNumAndDen = gcd(temp.num,temp.den);
	temp.num = temp.num / gcdOfNumAndDen;
	temp.den = temp.den / gcdOfNumAndDen;
	return temp;
}

fractionNumber sub(fractionNumber a,fractionNumber b)
{
	int den=lcm(a.den,b.den);
	int aNum=(den / a.den) * a.num;
	int bNum=(den / b.den) * b.num;
	fractionNumber temp;
	temp.num=aNum - bNum;
	temp.den=den;
	int gcdOfNumAndDen = gcd(temp.num,temp.den);
	temp.num = temp.num / gcdOfNumAndDen;
	temp.den = temp.den / gcdOfNumAndDen;
	return temp;
}

fractionNumber mul(fractionNumber a,fractionNumber b)
{
	fractionNumber temp;
	int num=a.num*b.num;
	int den=a.den*b.den;
	int gcdOfNumbers = gcd(num,den);
	temp.num = num / gcdOfNumbers;
	temp.den = den / gcdOfNumbers;
	if(temp.den < 0)
	{
		temp.num = temp.num*(-1);
		temp.den = temp.den*(-1);
	}
	return temp;
}

fractionNumber dev(fractionNumber a,fractionNumber b)
{
	fractionNumber temp;
	temp.num = b.den;
	temp.den = b.num;
	return mul(a,temp);
}

fractionNumber determinant(int n,fractionNumber mat[n][n])
{
	int i,j,i_count,j_count,count=0;
	fractionNumber array[n-1][n-1],det;
	det.num=0;
	det.den=1;
	if(n==1)
		return mat[0][0];
	if(n==2)
		return sub(mul(mat[0][0],mat[1][1]),mul(mat[0][1],mat[1][0]));
	for(count=0;count<n;count++)
	{
		i_count=0;
		for(i=1;i<n;i++)
		{
			j_count=0;
			for(j=0;j<n;j++)
			{
				if(j == count)
					continue;
				//array[i_count][j_count].num = mat[i][j].num;
				//array[i_count][j_count].den = mat[i][j].den;
				array[i_count][j_count] = mat[i][j];
				j_count++;
			}
			i_count++;
		}
		fractionNumber temp = determinant(n-1,array);
		temp.num = pow(-1,count) * temp.num;
		det = add(det,mul(mat[0][count],temp));
	}
	return det;
}

void adjoint(int n,fractionNumber mat[n][n])
{
	int i,j,i_count,j_count,countOfRow,countOfColumn;
	fractionNumber array[n-1][n-1],output[n][n];
/*######################## Making co-factors of matrix ################*/
	for(countOfRow=0;countOfRow<n;countOfRow++)
	{
		for(countOfColumn=0;countOfColumn<n;countOfColumn++)
		{
			i_count=0;
			for(i=0;i<n;i++)
			{
				j_count=0;
				if(i==countOfRow)
					continue;
				for(j=0;j<n;j++)
				{
					if(j==countOfColumn)
						continue;
					//array[i_count][j_count].num = mat[i][j].num;
					//array[i_count][j_count].den = mat[i][j].den;
					array[i_count][j_count]=mat[i][j];
					j_count++;
				}
				i_count++;
			}
			/*deciding sign of co factors */
			fractionNumber temp = determinant(n-1,array);
			output[countOfRow][countOfColumn].num = pow(-1,countOfRow+countOfColumn)*temp.num;
			output[countOfRow][countOfColumn].den = temp.den;
		}
	}
	int l,k;
	for(l=0;l<n;l++)
	{
		for(k=0;k<n;k++)
			mat[l][k]=output[l][k];
	}
}

void transpose(int n,fractionNumber mat[n][n])
{	
	int i,j;
	fractionNumber temp;
	fractionNumber output[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			output[j][i] = mat[i][j];
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		mat[i][j]=output[i][j];
	}
}

void inverseOfMatrix(int n,fractionNumber det,fractionNumber mat[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	mat[i][j] = dev(mat[i][j],det);
}
