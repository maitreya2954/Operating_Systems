#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

//Order of the matrix
int n;

//Original Matrix
int Matrix[10][10];

int AdjointMatrix[10][10];

//Structure to define each element in the matrix
struct MatElem
{
	int row;
	int column;
	int size;
};


//Determinant Function
int determinant(int n, int matrix[][n])
{

	if (n == 2)
		return ((matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]));

	else
	{
		int temp_matrix[n-1][n-1];
		int det = 0;
		
		for (int i = 0; i < n; ++i)
		{
			int count1 = 0,count2;
			
			for (int p = 1; p < n; ++p)
			{
				count2=0;
				for (int q = 0; q < n; ++q)
				{
					if(q != i)
					{
							
						temp_matrix[count1][count2] = matrix[p][q];
						count2++;
					}
				}
					count1++;
			}
			
			det = det + (matrix[0][i]*(pow(-1,i)*determinant(n-1, temp_matrix)));
		}

		return (det);
	}
}

//Cofactor Function
void *Adjoint(void * a)
{
	struct MatElem *X = a;
	//X is each element

	int temp_matrix[X -> size-1][X -> size-1];
	//temp_matrix contains all the elements other than the element row and element column

	int count1 = 0,count2;
	

	for (int p = 0; p < X -> size; ++p)
	{
		if(p != X -> row)
		{
			count2 = 0;
			for (int q = 0; q < X -> size; ++q)
			{
				if(q != X -> column)
				{
					temp_matrix[count1][count2] = Matrix[p][q];
					count2++;
				}
			}
			count1++;
		}
	}
	AdjointMatrix[X -> column][X -> row] = pow(-1,X -> row + X -> column)*determinant(n-1, temp_matrix);

	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	srand((unsigned)time(0));
	printf("\nEnter the size of matrix: ");
	scanf("%d",&n);
	
	//Create n square threads as there are n square elements in the matrix
	pthread_t tid[n][n];
	
	// for (int i = 0; i < n; ++i)
	// 	for (int j = 0; j < n; ++j)
	// 	{
	// 		printf("Enter (%d , %d) element: ", i, j);
	// 		scanf("%d", &Matrix[i][j]);
	// 	}

	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			Matrix[i][j] = rand()%5 + 1;

	printf("\nThe matrix you entered is :\n");
	int new_Matrix[n][n];

	for (int i = 0; i < n; ++i)
	{
		printf("\t\t\t\t");
		
		for (int j = 0; j < n; ++j)
			{
				printf("%d   ",Matrix[i][j]);
				new_Matrix[i][j] = Matrix[i][j];
			}
		printf("\n");
	}
	
	for (int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			struct MatElem *X = (struct MatElem *)malloc((sizeof(struct MatElem)));
			X->row = i;
			X->column = j;
			X->size = n;
			pthread_create(&tid[i][j], NULL, Adjoint, X);
			pthread_join(tid[i][j],NULL);
		}
	
	int det = determinant(n, new_Matrix);
	printf("\nDeterminant = %d\n", det);
		
	printf("\nThe AdjointMatrix is :\n");
	for (int i = 0; i < n; ++i)
	{	
		printf("\t\t\t\t");
		for(int j = 0; j < n; ++j)
			printf("%d   ", AdjointMatrix[i][j]);
		
		printf("\n");
	}
	printf("\n");

	if(det == 0)
		printf("Inversion Doesn't exist\n");
	else
	{
		printf("\nThe InvertedMatrix is :\n");
		for (int i = 0; i < n; ++i)
		{	
			printf("\t\t\t\t");
			for(int j = 0; j < n; ++j)
				printf("%.2f   ", (AdjointMatrix[i][j]*1.0)/det);
			
			printf("\n");
		}
		printf("\n");
	}

	return 0;
}