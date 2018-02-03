#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp;
	char string[1000],string1[1200];
	fp= fopen("phil.txt","r");
	while(fgets(string, 1000, fp))
	{
		sprintf(string1, "figlet %s >> output.txt", string);
		system(string1);
	}
	fclose(fp);
	return 0;
}