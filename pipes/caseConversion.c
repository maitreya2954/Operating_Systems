#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>


int main(void)
{
        int     fd[2], nbytes;
        pid_t   pid;
        char    string[1024];
        char    readbuffer[1024];
        printf("Enter the string for CASE CONVERSION: ");
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
                for (int i = 0; i < strlen(readbuffer); ++i)
                {
                        //printf("%c - \n", readbuffer[i]);
                        if(isalpha(readbuffer[i]))
                        {
                                if (isupper(readbuffer[i]))
                                {
                                        readbuffer[i]=tolower(readbuffer[i]);
                                }
                                else
                                {
                                        readbuffer[i]=toupper(readbuffer[i]);
                                }
                        }
                }
                printf("CASE CONVERTED: %s\n", readbuffer);
        }
        
        return(0);
}