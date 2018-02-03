#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char * reverseStr(char str[])
{
    int n = strlen(str);
 
    for (int i=0; i<n/2; i++){
        char temp=str[i];
        str[i]=str[n-i-1];
        str[n-i-1]=temp;
    }
    return str;
}

int main(void)
{
        int     fd[2], nbytes;
        pid_t   pid;
        char    string[1024];
        char    readbuffer[1024];
        printf("Enter the string for STRING REVERSAL: ");
        scanf("%99[^\n]",string);
        pipe(fd);
        
        if((pid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(pid == 0)
        {
                close(fd[0]);
                write(fd[1], string, (strlen(string)+1));
                sleep(2);
                exit(0);
        }
        else
        {
                close(fd[1]);
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s\n", readbuffer);
                
                printf("Reversed string: %s\n", reverseStr(readbuffer));
        }
        
        return(0);
}