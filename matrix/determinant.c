#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

int determinant(int n, int matrix[][n])
{
	if (n==2)
	{
		//printf("det return: %d\n", (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]));
		return ((matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]));
	}
	else
	{
		int new_matrix[n-1][n-1];
		int det=0;
		for (int i = 0; i < n; ++i)
		{
			int count1=0,count2=0;
			for (int p = 1; p < n; ++p)
			{
				count2=0;
				for (int q = 0; q < n; ++q)
				{
					if(q!=i)
					{
						//printf("p-%d q-%d c1-%d c2-%d\n ", p,q,count1,count2);	
						new_matrix[count1][count2]=matrix[p][q];
						count2++;
					}
				}
					count1++;
			}
			
			det=det+(matrix[0][i]*(pow(-1,i)*determinant(n-1, new_matrix)));
		}
		//printf("det: %d\n", det);
		return (det);
	}
}

int cofactor(int i, int j, int n, int matrix[][n])
{
	int new_matrix[n-1][n-1];
	int count1=0,count2=0;
	for (int p = 0; p < n; ++p)
	{
		if(p!=i)
		{
			count2=0;
			for (int q = 0; q < n; ++q)
			{
				if(q!=j)
				{
					//printf("p-%d q-%d c1-%d c2-%d\n ", p,q,count1,count2);	
					new_matrix[count1][count2]=matrix[p][q];
					count2++;
				}

			}
			count1++;
		}
	}
	/*printf("new_matrix\n\n");
	for (int p = 0; p < n-1; ++p)
	{
		for (int q = 0; q < n-1; ++q)
		{
			printf("%d ", new_matrix[p][q]);
		}
		printf("\n");
	}*/
	return (pow(-1,i+j)*determinant(n-1, new_matrix));
}

int main(int argc, char const *argv[])
{
	int n,det=0;
	printf("Enter the size of the square matrix: ");
	scanf("%d",&n);
	int matrix[n][n],new_matrix[n][n];
	printf("Enter the values in matrix: ");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d",&matrix[i][j]);
		}
	}

	pid_t pid=vfork();

	if(pid<0)
	{
		printf("***********Fork Failed***********\n");
		exit(0);
	}
	else if(pid==0)
	{
		
		for (int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				new_matrix[i][j]=cofactor(i,j,n,matrix);
			}
		}

		printf("Matrix:\n");
		for (int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}

		printf("Cofactor Matrix:\n");
		for (int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				printf("%d ", new_matrix[i][j]);
			}
			printf("\n");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("\n\ndet=%d\nAdjoint Matrix: \n", determinant(n, matrix));
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				matrix[i][j]=new_matrix[j][i];
			}
		}		
		for (int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
		exit(0);
	}
	return 0;
}