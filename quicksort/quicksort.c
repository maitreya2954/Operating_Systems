#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Driver program to test above functions
int main()
    {
        pid_t pid=vfork();
        if(pid==0)
        {
            int arr[] = {10, 7, 8, 9, 1, 5};
            int n = sizeof(arr)/sizeof(arr[0]);
            quickSort(arr, 0, n-1);
            FILE *fp=fopen("temp.dat","w");
            for (int i = 0; i < n; ++i)
            {
                fprintf(fp, "%d ", arr[i]);
            }
        }
        else if(pid>0)
        {
            printf("Sorted array: ");
            FILE *fp=fopen("temp.dat","r");
            char * line=NULL;
            size_t len=0;
            getline(&line, &len, fp);
            printf("%s\n", line);
            fclose(fp);
            exit(0);
        }
    return 0;
}