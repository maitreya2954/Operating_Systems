#include <stdio.h>
#include <stdlib.h>
 
#define NO_OF_PROCESS 5
#define NO_OF_TYPES 3

void needCalc(int need[NO_OF_PROCESS][NO_OF_TYPES], int maximum[NO_OF_PROCESS][NO_OF_TYPES],
                   int allocation[NO_OF_PROCESS][NO_OF_TYPES])
{
    // Calculating Need of each NO_OF_PROCESS
    for (int i = 0 ; i < NO_OF_PROCESS ; i++)
        for (int j = 0 ; j < NO_OF_TYPES ; j++)
 
            // Need of instance = maximum instance -
            //                    allocated instance
            need[i][j] = maximum[i][j] - allocation[i][j];
}
 
// Function to find the system is in safe state or not
bool isSafe(int processes[], int available[], int maximum[][NO_OF_TYPES],
            int allocation[][NO_OF_TYPES])
{
    int need[NO_OF_PROCESS][NO_OF_TYPES];
 
    // Function to calculate need matrix
    needCalc(need, maximum, allocation);
 
    // Mark all processes as infinish
    bool finish[NO_OF_PROCESS] = {0};
 
    // To store safe sequence
    int safeSeq[NO_OF_PROCESS];
 
    // Make a copy of available resources
    int work[NO_OF_TYPES];
    for (int i = 0; i < NO_OF_TYPES ; i++)
        work[i] = available[i];
 
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < NO_OF_PROCESS)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < NO_OF_PROCESS; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current NO_OF_PROCESS need is less
                // than work
                int j;
                for (j = 0; j < NO_OF_TYPES; j++)
                    if (need[p][j] > work[j])
                        break;
 
                // If all needs of p were satisfied.
                if (j == NO_OF_TYPES)
                {
                    // Add the allocated resources of
                    // current NO_OF_PROCESS to the available/work
                    // resources i.e.free the resources
                    for (int k = 0 ; k < NO_OF_TYPES ; k++)
                        work[k] += allocation[p][k];
 
                    // Add this process to safe sequence.
                    safeSeq[count++] = p;
 
                    // Mark this p as finished
                    finish[p] = 1;
 
                    found = true;
                }
            }
        }
 
        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
        	printf("System is not in sage state\n");
            return (false);
        }
    }
 
    // If system is in safe state then
    // safe sequence will be as below
    printf("\n***Safe state***\nSequence: ");
    for (int i = 0; i < NO_OF_PROCESS ; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}
 
// Driver code
int main()
{
    int processes[] = {0, 1, 2, 3, 4};
 
    // Available instances of resources
    int available[] = {2, 3, 0};
 
    // Maximum NO_OF_TYPES that can be allocated
    // to processes
    int maximum[][NO_OF_TYPES] = {{7, 4, 3}, {0, 2, 0}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};
 
    // Resources allocated to processes
    int allocation[][NO_OF_TYPES] = {{0, 1, 0}, {6, 6, 2}, {3, 0, 2}, {2, 1, 1}, {4, 3, 1}};
 
    // Check system is in safe state or not
    isSafe(processes, available, maximum, allocation);
    return 0;
}