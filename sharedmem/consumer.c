#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main()
{
	const int SIZE 4096;
	const char *name = "OS";
	int shm fd;
	void *ptr;
	shm fd = shm open(name, O RDONLY, 0666);
	ptr = mmap(0, SIZE, PROT READ, MAP SHARED, shm fd, 0);
	printf("%s",(char *)ptr);
	shm unlink(name);
	return 0;
}