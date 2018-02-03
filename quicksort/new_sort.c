#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
	int count = 1;
	char first[1024], current[1024], cmdline[1024];
	FILE *lesser = NULL, *greater = NULL;
	snprintf( cmdline, sizeof(cmdline), "\"%s\"", argv[0] );
	if( NULL == fgets( first, sizeof(first), stdin ) ) return 0;
	while( NULL != fgets( current, sizeof(current), stdin ) ) {
		int cmp = strcmp( current, first );
		if( cmp == 0 ) ++count;
		else if( cmp < 0 ) {
			if( NULL == lesser ) lesser = popen( cmdline, "w" );
			fputs( current, lesser );
		} else {
			if( NULL == greater ) greater = popen( cmdline, "w" );
			fputs( current, greater );
		}
	}
	if( NULL != lesser ) pclose( lesser );
	for( ; count; --count ) fputs( first, stdout );
	fflush( stdout );
	if( NULL != greater ) pclose( greater );
	return 0;
}