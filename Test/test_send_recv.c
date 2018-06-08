#include "flip.h"
#include <stdio.h>
#include <stdlib.h>

meta_header metaHdr;
flip_header flipHdr;

int main(int argc, char *argv[])
{	
	metaHdr.continuation1 = false;
	metaHdr.version = true;
	metaHdr.destination1 = true;
	metaHdr.flow = true;


	char *bitmap = FLIP_construct_bitmap();
	
	int i = 0, j, k;
	read_bitmap(bitmap, &i, &j, &k); 
	
	char read_string[20];
	get_bitmap_str(bitmap, read_string, 20);
	printf("bitmap is: %s\n", read_string);
	
}