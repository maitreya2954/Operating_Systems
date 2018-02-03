#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



char string_of_characters[200];
int character_frequency_counter;
int counter;
int print_histogram_counter, stringlength;
int output_counter;
char frequency_array[26][2]={'a',0,'b',0,'c',0,'d',0,'e',0,'f',0,'g',0,'h',0,'i',0,'j',0,'k',0,'l',0,'m',0,'n',0,'o',0,'p',0,'q',0,'r',0,'s',0,'t',0,'u',0,'v',0,'w',0,'x',0,'y',0,'z',0};

void  frequency_of_characters (char string_of_characters[50])
{
    stringlength=strlen(string_of_characters);
    for(counter=0; counter<=strlen(string_of_characters); counter++) 
    {
          for (character_frequency_counter=0;character_frequency_counter<=25;character_frequency_counter++) 
            {
               if (frequency_array[character_frequency_counter][0]==string_of_characters[counter]) 
                {
                 frequency_array[character_frequency_counter][1]=(frequency_array[character_frequency_counter][1])+1;
                }
            }

    }


}

int printout_of_character_frequencies(char frequency_array[26][2]) 
{
    system("clear");
    printf("\n\n%-10s%-8s%15s\n","Letter","Frequency","Histogram");
    for(output_counter=0;output_counter<=25;output_counter++)  
    {
     printf("%3c%12d             ", frequency_array[output_counter][0], frequency_array[output_counter][1]);

        for (print_histogram_counter= 1; print_histogram_counter<= frequency_array[output_counter][1]; print_histogram_counter++ ) 
        { printf( "%c",'*'); }

     printf("\n");          
    }
    printf("Total%11d            ", stringlength);
    for (print_histogram_counter= 1; print_histogram_counter<= stringlength; print_histogram_counter++ ) 
        { printf( "%c",'*'); }
    printf("\n"); 
    return 0;               
}

int main(void)
{
    printf("Enter the string without spaces\n");
    scanf("%s",string_of_characters); 
    pid_t pid=vfork();
    if (pid==0){
        frequency_of_characters (string_of_characters);     
        exit(0);
    }
    else if(pid>0){
        printout_of_character_frequencies(frequency_array); 
        exit(0);
    }
    return 0;                                          
}   








