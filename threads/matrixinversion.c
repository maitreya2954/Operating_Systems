#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
int n;
int det;
int matrix[100][100];
int altrmatrix[100][100];

struct matrixdata
{
	int row;
	int column;
	int size;
};

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

void * cofactor(void * a)
{
	printf(" |__Cofactor invoked...\n");
	struct matrixdata *data=a;
	int new_matrix[data->size-1][data->size-1];
	int count1=0,count2=0;
	for (int p = 0; p < data->size; ++p)
	{
		if(p!=data->row)
		{
			count2=0;
			for (int q = 0; q < data->size; ++q)
			{
				if(q!=data->column)
				{
					//printf("p-%d q-%d c1-%d c2-%d\n ", p,q,count1,count2);	
					new_matrix[count1][count2]=matrix[p][q];
					count2++;
				}
			}
			count1++;
		}
	}
	altrmatrix[data->row][data->column]=pow(-1,data->row+data->column)*determinant(n-1, new_matrix);
	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	srand((unsigned)time(0));
	printf("Enter the size of matrix: ");
	scanf("%d",&n);
	pthread_t tid[n][n];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j]=(rand()%10)+1;
		}
	}

	printf("\n\n%s\n", argv[0]);
	for (int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			struct matrixdata *data=(struct matrixdata *)malloc((sizeof(struct matrixdata)));
			data->row=i;
			data->column=j;
			data->size=n;
			pthread_create(&tid[i][j], &attr, cofactor, data);
			pthread_join(tid[i][j],NULL);
		}             
	}
	int new_matrix[n][n];
	printf("Matrix:\n");
	for (int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			printf("%d ", matrix[i][j]);
			new_matrix[i][j]=matrix[i][j];
		}
		printf("\n");
	}
	
	printf("\n\ndet=%d\nAdjoint Matrix: \n", determinant(n, new_matrix));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j]=altrmatrix[j][i];
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
	printf("\n");
	return 0;
}