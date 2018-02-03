#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with \0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&  *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          


          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          
          FILE *fp;
          fp=fopen("shell_history.dat","a");
          char **original=argv;
            while(*argv!=NULL)
               {
                    fprintf(fp, "%s ", *argv);
                    argv++;
               }
               fprintf(fp, "\n" );
          fclose(fp); 
          argv=original;
          if (strcmp(*original,"getme")==0)
          {
               const size_t line_size = 300;
               char* line = malloc(line_size);
               *original++;
               system("tac shell_history.dat >> shell_history.txt");
               if (*original!=NULL)
               {
                    int num=atoi(*original);
                    printf("shell history upto %d records\n", num);
                    printf("\n\n\n");
                    FILE *fh=fopen("shell_history.txt","r");
                    for (int i = -1; i < num; ++i)
                    {

                         if (fgets(line, line_size, fh) != NULL)
                              if(i>-1)
                                   printf("%d.%s", i+1,line);
                    }
                    printf("\n\n\n");
                    fclose(fh);
               }
               else
               {
                    printf("All records of shell history\n");
                    printf("\n\n\n");
                    FILE *fh=fopen("shell_history.txt","r");
                    int i=-1;
                    while (fgets(line, line_size, fh) != NULL)
                    {
                         if(i>-1)
                             printf("%d.%s", i+1,line);
                         i++;
                    }
                    printf("\n\n\n");
                    fclose(fh);
               }
               system("rm shell_history.txt");
               exit(1);
          }
          else
          {
               if (execvp(*argv, argv) < 0) {     /* execute the command  */
                    printf("*** ERROR: exec failed\n");
                    exit(1);
               }
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

void  main(void)
{
     system("clear");
     char  line[1024];             /* the input line                 */
     char  *argv[64];              /* the command line argument      */

     while (1) {                   /* repeat until done ....         */
          printf("Shell -> ");     /*   display a prompt             */
          gets(line);              /*   read in the command line     */
          printf("\n");            /*   parse the line               */
          parse(line, argv);      
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit if it is                */
          execute(argv);           /* otherwise, execute the command */
     }
}