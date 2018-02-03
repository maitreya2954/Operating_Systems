#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
/*int n = 27; 
int magicSquare[n][n];

memset(magicSquare, 0, sizeof(magicSquare));

int i = n/2;
int j = n-1;

for (int num=1; num <= n*n; )
{
    if (i==-1 && j==n)
    {
        j = n-2;
        i = 0;
    }
    else
    {
        if (j == n)
            j = 0;
        if (i < 0)
            i=n-1;
    }
    if (magicSquare[i][j]) 
    {
        j -= 2;
        i++;
        continue;
    }
    else
        magicSquare[i][j] = num++;

    j++; i--; 
}

printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",
        n, n*(n*n+1)/2);
for(i=0; i<n; i++)
{
    for(j=0; j<n; j++)
        printf("%3d ", magicSquare[i][j]);
    printf("\n");
}*/
    pid_t pid = vfork();
    if (pid==0)
    {
        int n;
        printf("Child...\nEnter the size of the matrix: ");
        scanf("%d",&n);
        int magicSquare[n][n];
        memset(magicSquare, 0, sizeof(magicSquare));
        int i = n/2;
        int j = n-1;
        for (int num=1; num <= n*n; )
        {
            if (i==-1 && j==n)
            {
                j = n-2;
                i = 0;
            }
            else
            {
                if (j == n)
                    j = 0;
                if (i < 0)
                    i=n-1;
            }
            if (magicSquare[i][j]) 
            {
                j -= 2;
                i++;
                continue;
            }
            else
                magicSquare[i][j] = num++;

            j++; i--; 
        }
        FILE *fp;
        fp=fopen("temp.dat","w");
        fprintf(fp, "%d ", n);
        for(int k=0; k<n; k++)
        {
            for(int l=0; l<n; l++)
                fprintf(fp, "%d ", magicSquare[k][l]);
        }
        fclose(fp);
        exit(0);
    }
    else if(pid>0)
    {
        FILE *fp;
        fp=fopen("temp.dat","r");
        int n;
        fscanf(fp, "%d", &n);
        int magicSquare[n][n];
        printf("Parent...\n");
        printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",
        n, n*(n*n+1)/2);
        
        for(int k=0; k<n; k++)
            for(int l=0; l<n; l++)
                fscanf(fp, "%d" , &magicSquare[k][l]);
        for(int k=0; k<n; k++)
        {
            for(int l=0; l<n; l++)
                printf("%3d ", magicSquare[k][l]);
            printf("\n");
        }
        exit(0);
    }

return 0;
}