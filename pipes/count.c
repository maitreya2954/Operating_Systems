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
        
        pipe(fd);
        
        if((pid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(pid == 0)
        {
        	printf("Enter the string\n");
        	scanf("%99[^#]",string);
            close(fd[0]);
            write(fd[1], string, (strlen(string)+1));
            sleep(2);
            exit(0);
        }
        else
        {
            close(fd[1]);
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            printf("\n\nReceived string: %s\n", readbuffer);
            
            printf("\nThe total number of characters(a..z|A...Z) in the given text are:");
	 
	        int CharCount = 0;
	        int WordCount = 0;
	        int prev=0;
	        for (int i = 0; i < nbytes; ++i)
	            if(isalpha(readbuffer[i])){
	                CharCount = CharCount + 1;
	                prev=1;
	            }
	            else
	            	if(prev!=0){
	            		prev=0;
	            		WordCount++;
	            	}

	        printf("%d\n",CharCount);

	        printf("\nThe total number of words in the given text are:");
	        printf("%d\n",WordCount);

	        printf("\nThe total number of lines in the given text are:");
	        int LineCount = 1;

	        for (int i = 0; i < nbytes; ++i)
	            if(readbuffer[i] == '\n')
	                LineCount = LineCount + 1;

	        printf("%d\n",LineCount);

	        printf("\nThe total number of sentences in the given text are:");
	        int SentenceCount = 0;

	        for (int i = 0; i < nbytes; ++i)
	            if(readbuffer[i] == '.')
	                SentenceCount = SentenceCount + 1;

	        printf("%d\n",SentenceCount);
        }
        
        return(0);
}