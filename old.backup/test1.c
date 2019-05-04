#include "flip.h"
#include <stdio.h>
#include <stdlib.h>


meta_header metaHdr;
flip_header flipHdr;

int main(int argc, char *argv[])
{	
	metaHdr.continuation1 = true;
	metaHdr.version = true;
	metaHdr.destination1 = true;
	metaHdr.source2 = true;
	metaHdr.flow = true;
	metaHdr.protocol = true;
	metaHdr.checksum = true;

	flipHdr.version = 10;
	flipHdr.destination_addr = 65535;
	flipHdr.source_addr = 255;
	flipHdr.protocol = 4;
	flipHdr.checksum = 8;
	flipHdr.flow = 1234568;
	
	char *bitmaps = FLIP_construct_bitmap();
	printf("returned string is: %s\n\n", bitmaps);
	
	FLIP_construct_header();
	
}