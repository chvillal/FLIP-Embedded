#include "flip.h"
#include <stdio.h>
#include <stdlib.h>

meta_header metaHdr;

int main(int argc, char *argv[])
{	
	metaHdr.continuation1 = true;
	metaHdr.version = true;
	metaHdr.destination2 = true;
	metaHdr.source2 = true;
	metaHdr.protocol = true;
	
	char *bitmaps = FLIP_construct_bitmap();
	
	printf("returned string is: %s\n", bitmaps);
}